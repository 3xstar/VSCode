import net from 'node:net';

const HOST = '127.0.0.1';
// const PORT = 9999; ERROR TEST - WRONG PORT
const PORT = 3000;

const DEFAULT_MESSAGE = 'EVENT: PC-07 REQUEST_HELP'
const MESSAGE = process.argv[2] || DEFAULT_MESSAGE;

const socket = net.createConnection(
  { host: HOST, port: PORT },
  () => {
    console.log('Соединение с NetLab установлено');;
    // socket.write('ALERT: Требуется помощь\n');
    // socket.write('STATUS: WORKSTATION-07 READY\n');
    socket.write(MESSAGE + '\n');
  }
);

socket.setEncoding('utf8');

socket.on('data', (chunk) => {
  // console.log('Ответ сервера: ' + chunk.trim());
  console.log(chunk.trim());
  socket.end();
});

socket.on('error', (error) => {
  console.error('Не удалось подключиться: ' + error.message);
});

socket.on('close', () => {
  console.log('Соединение закрыто');
});