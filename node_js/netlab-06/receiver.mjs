import dgram from 'node:dgram';
import readline from 'node:readline';

const PORT = 3030;
const GROUP_1 = '239.255.10.10';
const GROUP_2 = '239.255.10.11'; 

const IFACE = process.env.MULTICAST_IFACE; // При необходимости укажите IPv4-адрес интерфейса

const socket = dgram.createSocket({ type: 'udp4', reuseAddr: true });

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.on('line', (line) => {
  if (line.trim().toUpperCase() === 'STOP') {
    console.log('Получена локальная команда STOP. Закрываем сокет...');
    rl.close();
    socket.close();
  }
});

socket.on('message', (buffer, sender) => {
  const timestamp = new Date().toISOString(); 
  console.log(
    `[${timestamp}] [RECEIVED] ${buffer.toString('utf8')} FROM ${sender.address}:${sender.port}`
  );
});

socket.on('error', (error) => {
  console.error('[RECEIVER ERROR]', error.message);
  socket.close();
});

socket.on('close', () => {
  console.log('Приёмник остановлен');
});

socket.bind(PORT, '0.0.0.0', () => {
  console.log('UDP приёмник: порт ' + PORT);
  console.log('Введите "STOP" для завершения работы приемника');
  try {
    socket.addMembership(GROUP_1, IFACE);
    console.log('Подписка на группу 1: ' + GROUP_1);
  } catch (error) {
    console.log('Multicast недоступен:', error.message);
    console.log('Unicast по-прежнему можно проверить');
  }

  try {
    socket.addMembership(GROUP_2, IFACE);
    console.log('Подписка на группу 2: ' + GROUP_2);
  } catch (error) {
    console.log(`Группа 2 (${GROUP_2}) недоступна:`, error.message);
  }
});
