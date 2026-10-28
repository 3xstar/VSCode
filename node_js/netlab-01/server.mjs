import net from 'node:net';

const HOST = '127.0.0.1';
const PORT = 3000;

let connectionsCount = 0;

const server = net.createServer((socket) => {
  // console.log(
  //   'Подключился клиент: ' +
  //   socket.remoteAddress + ':' + socket.remotePort
  // );
  connectionsCount++;
  console.log(`Подключений с момента старта: ${connectionsCount}`)
  socket.setEncoding('utf8');

  socket.on('data', (chunk) => {
    // console.log('Получены данные: ' + chunk.trim());
    // socket.write('ACK: ' + chunk);
    const time = new Date().toLocaleTimeString('ru-RU');
    console.log(`[${time}] ${chunk.trim()}`);
  });

  socket.on('end', () => {
    console.log('Клиент завершил соединение');
  });

  socket.on('error', (error) => {
    console.error('Ошибка клиента: ' + error.message);
  });
});

server.on('error', (error) => {
  console.error('Ошибка сервера: ' + error.message);
});

// server.listen(PORT, HOST, () => {
//   console.log('NetLab ожидает подключения: ' + HOST + ':' + PORT);
// });
server.listen(PORT, HOST, () => {
   console.log('NetLab v1.0 — сервер запущен');
});