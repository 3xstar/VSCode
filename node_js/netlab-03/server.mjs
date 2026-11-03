import net from 'node:net';

const HOST = '127.0.0.1';
const PORT = 3003;
const clients = new Map();
let nextId = 1;

function send(socket, text) {
    if (!socket.destroyed && !socket.writableEnded) {
        socket.write(text + '\n');
    }
}

function broadcast(text, except = null) {
    for (const socket of clients.keys()) {
        if (socket !== except) {
            send(socket, text);
        }
    }
}

const server = net.createServer((socket) => {
    const name = 'user-' + nextId++;
    clients.set(socket, name);
    socket.setEncoding('utf8');
    
    let pending = '';
    
    console.log(name + ' подключился');
    console.log(`IP=${socket.remoteAddress} PORT=${socket.remotePort}`)
    
    send(socket, 'WELCOME ' + name);
    send(socket, 'Команды: /say текст, /list, /online, /name новое_имя, /me действие, /to имя текст, /quit');
    broadcast('[SYSTEM] ' + name + ' вошёл в чат', socket);

    socket.on('data', (chunk) => {
        pending += chunk;
        let index;
        
        while ((index = pending.indexOf('\n')) !== -1) {
            const command = pending.slice(0, index).trim();
            pending = pending.slice(index + 1);
            
            if (!command) continue;

            if (command === '/list') {
                send(socket, 'Онлайн: ' + [...clients.values()].join(', '));
                continue;
            }
            
            else if (command.startsWith('/say ')) {
                const message = command.slice(5).trim();
                if (!message) {
                    send(socket, 'ERROR: пустое сообщение');
                    continue;
                }
                const currentName = clients.get(socket);
                broadcast('[' + currentName + '] ' + message, socket);
                send(socket, 'SENT: ' + message);
                continue;
            }
            
            else if (command.startsWith('/name ')) {
                const newName = command.slice(6).trim();
                const oldName = clients.get(socket);

                if (!newName) {
                    send(socket, 'ERROR: пустое имя');
                    continue;
                }

                const isUnique = ![...clients.values()].includes(newName);
                if (!isUnique) {
                    send(socket, 'ERROR: имя уже занято');
                    continue;
                }

                clients.set(socket, newName);
                send(socket, `Имя изменено на: ${newName}`);
                broadcast(`[SYSTEM] ${oldName} изменил имя на ${newName}`, socket);
                continue;
            }

            else if (command === '/online') {
                send(socket, `Количество активных клиентов: ${clients.size}`);
                continue;
            }

            else if (command.startsWith('/me ')) {
                const action = command.slice(4).trim();
                if (!action) {
                    send(socket, 'ERROR: пустое действие');
                    continue;
                }
                const currentName = clients.get(socket);
                broadcast(`* ${currentName} ${action}`);
                continue;
            }

            else if (command.startsWith('/to ')) {
                const rawParams = command.slice(4).trim();
                const firstSpaceIndex = rawParams.indexOf(' ');

                if (firstSpaceIndex === -1) {
                    send(socket, 'ERROR: неверный формат. Используйте: /to Имя Сообщение');
                    continue;
                }

                const targetName = rawParams.slice(0, firstSpaceIndex).trim();
                const privateMsg = rawParams.slice(firstSpaceIndex + 1).trim();

                if (!privateMsg) {
                    send(socket, 'ERROR: пустое личное сообщение');
                    continue;
                }

                let targetSocket = null;
                for (const [s, n] of clients.entries()) {
                    if (n === targetName) {
                        targetSocket = s;
                        break;
                    }
                }

                if (!targetSocket) {
                    send(socket, `ERROR: пользователь ${targetName} не найден в сети`);
                    continue;
                }

                const currentName = clients.get(socket);
                send(targetSocket, `[PM от ${currentName}] ${privateMsg}`);
                send(socket, `[PM для ${targetName}] ${privateMsg}`);
                continue;
            }

            else if (command === '/quit') {
                socket.end('BYE\n');
                return;
            }
            
            else {
                send(socket, 'ERROR: неизвестная команда');
            }
        }

        if (pending.length > 2048) {
            socket.end('ERROR: строка слишком длинная\n');
        }
    });

    socket.on('close', () => {
        const currentName = clients.get(socket) || name;
        clients.delete(socket);
        broadcast('[SYSTEM] ' + currentName + ' вышел из чата');
        console.log(currentName + ' отключился. Онлайн: ' + clients.size);
    });

    socket.on('error', (error) => {
        const currentName = clients.get(socket) || 'Неизвестный';
        console.error(currentName + ': ' + error.message);
    });
});

server.on('error', (error) => {
    console.error('Ошибка сервера:', error.message);
});

server.listen(PORT, HOST, () => {
    console.log('NetLab Chat: ' + HOST + ':' + PORT);
});
