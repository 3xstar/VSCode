import net from 'node:net';

const socket = net.createConnection({
    host: '127.0.0.1',
    port: 3010
});

const MESSAGE = 'TIME'; 

socket.setEncoding('utf8');

const startTime = performance.now();

socket.on('connect', () => {
    console.log('TCP: соединение установлено');
    socket.write(MESSAGE + '\n');
});

socket.on('data', (chunk) => {
    const duration = performance.now() - startTime;
    console.log('TCP ответ: ' + chunk.trim());
    console.log(`TCP время выполнения: ${duration.toFixed(3)} мс`);
});

socket.on('close', () => {
    console.log('TCP: соединение закрыто');
});

socket.on('error', (error) => {
    console.error('TCP ошибка:', error.code, error.message);
});
