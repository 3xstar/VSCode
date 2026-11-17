import http from 'node:http';
import { readFile } from 'node:fs/promises';
import { WebSocketServer, WebSocket } from 'ws';

const HOST = '127.0.0.1';
const PORT = 3060;
const MAX_CLIENTS = 20;
const clients = new Map();

let messageCount = 0;

function send(ws, data) {
  if (ws.readyState === WebSocket.OPEN) {
    ws.send(JSON.stringify(data));
  }
}

function broadcast(data) {
  for (const ws of clients.keys()) {
    send(ws, data);
  }
}

function online() {
  return [...clients.values()]
    .filter((client) => client.name !== null)
    .map((client) => client.name);
}

function error(ws, code, message) {
  send(ws, { type: 'error', code, message });
}

const server = http.createServer(async (req, res) => {
  if (req.method !== 'GET' || req.url !== '/') {
    res.writeHead(404, {
      'Content-Type': 'text/plain; charset=utf-8'
    });
    res.end('Не найдено');
    return;
  }

  try {
    const html = await readFile(
      new URL('./index.html', import.meta.url)
    );
    res.writeHead(200, {
      'Content-Type': 'text/html; charset=utf-8',
      'Cache-Control': 'no-store'
    });
    res.end(html);
  } catch (e) {
    console.error('Ошибка HTML:', e.message);
    res.writeHead(500);
    res.end('Ошибка сервера');
  }
});

const wss = new WebSocketServer({
  server,
  path: '/ws',
  maxPayload: 2048
});

wss.on('connection', (ws, req) => {
  ws.on('error', (e) => {
    console.error('[WS ERROR]', e.message);
  });

  if (clients.size >= MAX_CLIENTS) {
    ws.close(1013, 'Server busy');
    return;
  }

  send(ws, { type: 'stats', count: messageCount });

  const state = { name: null, timestamps: [] };
  clients.set(ws, state);

  console.log('[CONNECT]', req.socket.remoteAddress);
  send(ws, { type: 'info', text: 'Подключение установлено' });

  ws.on('message', (raw, isBinary) => {
    if (isBinary) {
      error(ws, 'TEXT_ONLY', 'Ожидается текстовый JSON');
      return;
    }

    let packet;
    try {
      packet = JSON.parse(raw.toString('utf8'));
    } catch {
      error(ws, 'INVALID_JSON', 'Неверный JSON');
      return;
    }

    if (!packet || typeof packet !== 'object' || Array.isArray(packet)) {
      error(ws, 'INVALID_PACKET', 'Ожидается объект');
      return;
    }

    if (packet.type === 'join') {
      if (state.name !== null) {
        error(ws, 'ALREADY_JOINED', 'Имя уже задано');
        return;
      }

      const name = packet.name;
      if (
        typeof name !== 'string' ||
        name.trim().length < 1 ||
        name.trim().length > 20
      ) {
        error(ws, 'INVALID_NAME', 'Имя: 1–20 символов');
        return;
      }

      const cleanName = name.trim();
      if (online().includes(cleanName)) {
        error(ws, 'NAME_TAKEN', 'Имя уже занято');
        return;
      }

      const time = new Date().toLocaleTimeString('ru-RU');
      state.name = cleanName;
      send(ws, { type: 'system', text: 'WELCOME, ' + cleanName + '!' });
      broadcast({
        type: 'system',
        text: '[' + time + '] ' + cleanName + ' подключился'
      });
      broadcast({ type: 'online', users: online() });
      console.log('[JOIN]', cleanName);
      return;
    }

    if (state.name === null) {
      error(ws, 'JOIN_REQUIRED', 'Сначала отправьте join');
      return;
    }

    if (packet.type === 'chat') {
      const text = packet.text;
      if (
        typeof text !== 'string' ||
        text.trim().length < 1 ||
        text.trim().length > 200
      ) {
        error(ws, 'INVALID_TEXT', 'Текст: 1–200 символов');
        return;
      }

      const now = Date.now();
      state.timestamps = state.timestamps.filter((t) => now - t < 10000);

      if (state.timestamps.length >= 5) {
        error(ws, 'RATE_LIMIT', 'Слишком много сообщений. Подождите 10 секунд.');
        return;
      }
      state.timestamps.push(now);

      const cleanText = text.trim();

      if (cleanText === '/who') {
        send(ws, {
          type: 'system',
          text: 'В сети сейчас: ' + online().join(', ')
        });
        return;
      }

      if (cleanText.startsWith('/w ')) {
        const parts = cleanText.split(' ');
        const targetName = parts[1];
        const privateText = parts.slice(2).join(' ').trim();

        if (!targetName || !privateText) {
          error(ws, 'INVALID_PM', 'Используйте формат: /w Имя сообщение');
          return;
        }

        let targetWs = null;
        for (const [clientWs, clientState] of clients.entries()) {
          if (clientState.name === targetName) {
            targetWs = clientWs;
            break;
          }
        }

        if (!targetWs) {
          error(ws, 'USER_NOT_FOUND', 'Пользователь ' + targetName + ' не в сети');
          return;
        }

        const time = new Date().toLocaleTimeString('ru-RU');
        send(targetWs, {
          type: 'system',
          text: `[${time}] [ЛС от ${state.name}]: ${privateText}`
        });
        send(ws, {
          type: 'system',
          text: `[${time}] [ЛС для ${targetName}]: ${privateText}`
        });

        messageCount += 1;
        broadcast({ type: 'stats', count: messageCount });
        return;
      }

      broadcast({
        type: 'chat',
        name: state.name,
        text: cleanText,
        time: new Date().toLocaleTimeString('ru-RU')
      });
      console.log('[MESSAGE]', state.name, cleanText.slice(0, 50));
      messageCount += 1;
      broadcast({ type: 'stats', count: messageCount });
      return;
    }

    error(ws, 'UNKNOWN_TYPE', 'Неизвестный тип команды');
  });

  ws.on('close', (code) => {
    clients.delete(ws);
    console.log('[CLOSE]', state.name ?? 'guest', code);
    if (state.name !== null) {
      broadcast({
        type: 'system',
        text: state.name + ' отключился'
      });
      broadcast({ type: 'online', users: online() });
    }
  });
});

wss.on('error', (error) => {
  console.error('[WSS ERROR]', error.message);
});

server.on('error', (error) => {
  console.error('[HTTP ERROR]', error.message);
});

server.listen(PORT, HOST, () => {
  console.log('NetLab Chat: http://' + HOST + ':' + PORT);
});
