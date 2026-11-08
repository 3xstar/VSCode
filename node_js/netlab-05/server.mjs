import net from 'node:net';

const HOST = '127.0.0.1';
const PORT = 3020;
const MAX_CLIENTS = 5;
const IDLE_MS = 20_000;
const WARNING_MS = 15_000;
const MAX_LINE_BYTES = 1024;

const clients = new Map();
let nextId = 1;

function getTimestamp() {
    return new Date().toLocaleTimeString('ru-RU', { hour12: false });
}

function send(socket, line) {
    if (!socket.destroyed && !socket.writableEnded) {
        socket.write(line + '\n');
    }
}

function broadcast(line, except = null) {
    for (const socket of clients.keys()) {
        if (socket !== except) {
            send(socket, line);
        }
    }
}

const server = net.createServer((socket) => {
    socket.setEncoding('utf8');

    socket.on('error', (error) => {
        console.error('[SOCKET ERROR]', error.code, error.message);
    });

    if (clients.size >= MAX_CLIENTS) {
        socket.end('ERROR SERVER_FULL\n');
        return;
    }

    const id = 'user-' + nextId++;
    const state = { id, pending: '', commands: 0, idleTimer: null };
    clients.set(socket, state);

    function clearDisconnectTimer() {
        if (state.idleTimer) {
            clearTimeout(state.idleTimer);
            state.idleTimer = null;
        }
    }

    socket.setTimeout(WARNING_MS);

    console.log(`[${getTimestamp()}] [CONNECT]`, id, socket.remoteAddress + ':' + socket.remotePort);
    
    send(socket, 'WELCOME ' + id);
    broadcast('[SYSTEM] ' + id + ' joined', socket);

    socket.on('data', (chunk) => {
        clearDisconnectTimer();
        socket.setTimeout(WARNING_MS);

        state.pending += chunk;
        let index;

        while ((index = state.pending.indexOf('\n')) !== -1) {
            const line = state.pending.slice(0, index).trim();
            state.pending = state.pending.slice(index + 1);

            if (Buffer.byteLength(line, 'utf8') > MAX_LINE_BYTES) {
                socket.end('ERROR LINE_TOO_LONG\n');
                return;
            }

            if (!line) continue;
            state.commands++;

            if (line === 'PING') {
                send(socket, 'PONG');
            }
            else if (line === 'STATS') {
                send(socket, 'STATS clients=' + clients.size + ' commands=' + state.commands);
            }
            else if (line.startsWith('SAY ')) {
                const text = line.slice(4).trim();
                if (!text) {
                    send(socket, 'ERROR EMPTY_MESSAGE');
                } else {
                    broadcast('[' + id + '] ' + text, socket);
                    send(socket, 'SENT');
                }
            }
            else if (line === 'QUIT') {
                socket.end('BYE\n');
                return;
            }
            else if (line === 'WHO') {
                let userList = 'ONLINE_USERS:\n';
                for (const [s, st] of clients.entries()) {
                    userList += `- ${st.id} (${s.remoteAddress}:${s.remotePort})\n`;
                }
                send(socket, userList.trim());
            }
            else if (line === 'HELP') {
                const helpText = 'AVAILABLE COMMANDS: PING, STATS, SAY <msg>, WHO, HELP, IDLE, QUIT';
                send(socket, helpText);
            } else if (line === 'IDLE') {
                const idleSeconds = IDLE_MS / 1000;
                send(socket, `IDLE_TIMEOUT ${idleSeconds} seconds`)
            }
            else {
                send(socket, 'ERROR UNKNOWN_COMMAND');
            }
        }

        if (Buffer.byteLength(state.pending, 'utf8') > MAX_LINE_BYTES) {
            socket.end('ERROR LINE_TOO_LONG\n');
        }
    });

    socket.on('timeout', () => {
        socket.setTimeout(0);

        send(socket, 'WARNING IDLE: You will be disconnected in 5 seconds if inactive.');
        console.log(`[${getTimestamp()}] [WARNING IDLE]`, id);

        clearDisconnectTimer();
        state.idleTimer = setTimeout(() => {
        console.log(`[${getTimestamp()}] [TIMEOUT DISCONNECT]`, id);
        socket.end('ERROR IDLE_TIMEOUT\n');
        }, IDLE_MS - WARNING_MS);
    });

    socket.on('close', () => {
        clearDisconnectTimer();
        if (!clients.delete(socket)) return;
        console.log(`[${getTimestamp()}] [CLOSE]`, id, 'active=' + clients.size);
        broadcast('[SYSTEM] ' + id + ' left');
    });
});

server.on('error', (error) => {
    console.error('[SERVER ERROR]', error.code, error.message);
});

server.listen(PORT, HOST, () => {
    console.log('NetLab 05: ' + HOST + ':' + PORT);
});
