import dgram from 'node:dgram';

const HOST = '127.0.0.1';
const PORT = 3011;

const server = dgram.createSocket('udp4');

server.on('message', (data, sender) => {
    const command = data.toString('utf8').trim();
    console.log('UDP от ' + sender.address + ':' + sender.port + ': ' + command);
    
    let answer = 'UNKNOWN';

    if (command === 'PING') {
        answer = 'PONG';
    }
    else if (command === 'TIME') {
        answer = new Date().toISOString();
    }

    server.send(answer, sender.port, sender.address, (error) => {
        if (error) {
            console.error('Ошибка отправки:', error.message);
        }
    });
});

server.on('error', (error) => {
    console.error('UDP сервер:', error.message);
    server.close();
});

server.bind(PORT, HOST, () => {
    console.log('UDP сервер: ' + HOST + ':' + PORT);
});
