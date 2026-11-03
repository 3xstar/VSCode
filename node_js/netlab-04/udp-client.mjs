import dgram from 'node:dgram';

const HOST = '127.0.0.1';
const PORT = 3011;

const MESSAGE = 'TIME'; 

const client = dgram.createSocket('udp4');
let completed = false;
let startTime;

let attempts = 0;      
const MAX_ATTEMPTS = 3;
const RETRY_INTERVAL = 1500;
let retryTimer = null;

function sendRequest() {
    if (completed) return;

    attempts++;
    console.log(`Отправка запроса... Попытка №${attempts} из ${MAX_ATTEMPTS}`);
    
    if (attempts === 1) {
        startTime = performance.now();
    }

    client.send(MESSAGE, PORT, HOST, (error) => {
        if (error) {
            console.error('Ошибка отправки датаграммы:', error.message);
        }
    });

    retryTimer = setTimeout(() => {
        if (completed) return;

        if (attempts < MAX_ATTEMPTS) {
            console.log(`⚠️  Ответ не получен за ${RETRY_INTERVAL / 1000} сек.`);
            sendRequest();
        } else {
            completed = true;
            console.log('Все попытки исчерпаны. Ответ от сервера не получен.');
            client.close();
        }
    }, RETRY_INTERVAL);
}

client.on('message', (data, sender) => {
    if (completed) return;
    completed = true;
    clearTimeout(retryTimer);

    const duration = performance.now() - startTime;

    console.log('UDP ответ: ' + data.toString('utf8'));
    console.log('Отправитель: ' + sender.address + ':' + sender.port);
    console.log(`UDP время выполнения: ${duration.toFixed(3)} мс`);
    client.close();
});

client.on('error', (error) => {
    console.error('UDP ошибка:', error.message);
    if (!completed) {
        completed = true;
        clearTimeout(retryTimer);
    }
    client.close();
});

sendRequest();
