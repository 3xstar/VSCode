import net from 'node:net';
import { createInterface } from 'node:readline';

const socket = net.createConnection({
    host: '127.0.0.1',
    port: 3003
});

const terminal = createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: 'NetLab> '
});

socket.setEncoding('utf8');
let pending = '';

socket.on('connect', () => {
    console.log('Подключено к NetLab Chat');
    terminal.prompt();
});

socket.on('data', (chunk) => {
    pending += chunk;
    let index;
    
    while ((index = pending.indexOf('\n')) !== -1) {
        const text = pending.slice(0, index).trim();
        pending = pending.slice(index + 1);
        
        console.log('\n' + text);
        terminal.prompt();
    }
});

terminal.on('line', (line) => {
    if (!socket.destroyed && !socket.writableEnded) {
        socket.write(line + '\n');
    }
});

socket.on('error', (error) => {
    console.error('Ошибка подключения: ' + error.message);
    terminal.close();
});

socket.on('close', () => {
    console.log('Соединение закрыто');
    terminal.close();
});

terminal.on('close', () => {
    if (!socket.destroyed && !socket.writableEnded) {
        socket.end();
    }
});
