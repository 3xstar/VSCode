import dgram from 'node:dgram';

const PORT = 3030;
const GROUP = '239.255.10.10';
const mode = (process.argv[2] || 'unicast').toLowerCase();
const customAddress = process.argv[3];

const customText = process.argv[4] || `${mode.toUpperCase()}: NetLab announcement`;

const addresses = {
  unicast: customAddress || '127.0.0.1',
  broadcast: customAddress,
  multicast: customAddress || GROUP // Позволяет отправить на любой мультикаст адрес
};

if (!Object.hasOwn(addresses, mode) || !addresses[mode]) {
  console.log('Использование:');
  console.log('node sender.mjs unicast [IP]');
  console.log('node sender.mjs broadcast <broadcast-IP>');
  console.log('node sender.mjs multicast');
  process.exit(1);
}

const socket = dgram.createSocket('udp4');
const target = addresses[mode];

socket.on('error', (error) => {
  console.error('[SENDER ERROR]', error.message);
  socket.close();
});

socket.bind(0, '0.0.0.0', () => {
  try {
    if (mode === 'broadcast') {
      socket.setBroadcast(true);
    }
    if (mode === 'multicast') {
      socket.setMulticastTTL(1);
      socket.setMulticastLoopback(true);
      if (process.env.MULTICAST_IFACE) {
        socket.setMulticastInterface(process.env.MULTICAST_IFACE);
      }
    }
    
    socket.send(customText, PORT, target, (error) => {
      if (error) {
        console.error('Отправка не удалась:', error.message);
      } else {
        console.log('Датаграмма передана ОС:', customText);
        console.log('Назначение:', target + ':' + PORT);
      }
      socket.close();
    });
  } catch (error) {
    console.error('Настройка сокета:', error.message);
    socket.close();
  }
});
