import net from 'node:net';
import { createInterface } from 'node:readline';

const HOST = '127.0.0.1';
const PORT = 3001;
const socket = net.createConnection({ host: HOST, port: PORT
});

const terminal = createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: 'NetLab> '
});

socket.setEncoding('utf8');
let pending = '';

socket.on('connect', () => {
    console.log('Подключение установлено');
    terminal.prompt();
});

socket.on('data', (chunk) => {
    pending += chunk;
    let index;

    while ((index = pending.indexOf('\n')) !== -1) {
        const answer = pending.slice(0, index).trim();
        pending = pending.slice(index + 1);
        
        console.log('\nСервер: ' + answer);
        if (answer === 'BYE') {
            terminal.close();
            return;
        }
        terminal.prompt();
    }
});

terminal.on('line', (line) => {
    const command = line.trim();
    if (!command) return terminal.prompt();
    if (!socket.destroyed) socket.write(command + '\n');
});

socket.on('error', (e) => {
    console.error('Ошибка: ' + e.message);
    terminal.close();
});
socket.on('close', () => {
    console.log('TCP-соединение закрыто');
    terminal.close();
});
terminal.on('close', () => {
    if (!socket.destroyed) socket.end();
});
