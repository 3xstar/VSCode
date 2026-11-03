import net from 'node:net';

const HOST = '127.0.0.1';
const PORT = 3010;

const server = net.createServer((socket) => {
    socket.setEncoding('utf8');
    let pending = '';
    console.log('TCP клиент подключился');

    socket.on('data', (chunk) => {
        pending += chunk;
        const newline = pending.indexOf('\n');

        if (newline === -1) {
            if (pending.length > 100) {
                socket.end('ERROR\n');
            }
            return;
        }

        const command = pending.slice(0, newline).trim();
        let answer = 'UNKNOWN';

        if (command === 'PING') {
            answer = 'PONG';
        }
        else if (command === 'TIME') {
            answer = new Date().toISOString();
        }

        socket.end(answer + '\n');
    });

    socket.on('error', (error) => {
        console.error('TCP сокет:', error.message);
    });
});

server.on('error', (error) => {
    console.error('TCP сервер:', error.message);
});

server.listen(PORT, HOST, () => {
    console.log('TCP сервер: ' + HOST + ':' + PORT);
});
