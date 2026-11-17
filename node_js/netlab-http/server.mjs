import http from 'node:http';

const HOST = '127.0.0.1';
const PORT = 3041;
const MAX_BYTES = 4096;

const events = [];
let nextId = 1;

let requestCount = 0;


function json(res, status, data) {
  res.writeHead(status, {
    'Content-Type': 'application/json; charset=utf-8',
    'Cache-Control': 'no-store'
  });
  res.end(JSON.stringify(data));
}

async function readJson(req) {
  const chunks = [];
  let total = 0;

  for await (const chunk of req) {
    total += chunk.length;
    if (total <= MAX_BYTES) {
      chunks.push(chunk);
    }
  }

  if (total > MAX_BYTES) {
    const error = new Error('BODY_TOO_LARGE');
    error.status = 413;
    throw error;
  }

  try {
    return JSON.parse(Buffer.concat(chunks).toString('utf-8'));
  } catch {
    const error = new Error('INVALID_JSON');
    error.status = 400;
    throw error;
  }
}

const server = http.createServer(async (req, res) => {
  const url = new URL(req.url, 'http://localhost');
  const path = url.pathname;
  const method = req.method;

  res.on('finish', () => {
    console.log(method, path, '->', res.statusCode);
  });

  if (path === '/' && method === 'GET') {
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    res.end(
      '<!doctype html><html lang="ru">' +
      '<meta charset="utf-8"><title>NetLab</title>' +
      '<h1>NetLab HTTP</h1>' +
      '<p><a href="/api/status">Статус</a></p>' +
      '<p><a href="/api/events">События</a></p>' +
      '<p><a href="/api/about">О программе</a></p>' +
      '<p><a href="/api/stations">Станции</a></p>' +
      '</html>'
    );
    return;
  }

  if (path === '/api/status' && method === 'GET') {
    requestCount += 1;
    json(res, 200, {
      service: 'NetLab',
      status: 'online',
      request_count: requestCount,
      eventsCount: events.length,
      time: new Date().toISOString()
    });
    return;
  }

  if (path === '/api/events') {
    if (method === 'GET') {
      json(res, 200, { events });
      return;
    }

    if (method === 'POST') {
      const type = req.headers['content-type'] ?? '';
      if (!type.toLowerCase().startsWith('application/json')) {
        json(res, 415, { error: 'JSON_REQUIRED' });
        return;
      }

      let body;
      try {
        body = await readJson(req);
      } catch (error) {
        json(res, error.status ?? 400, { error: error.message });
        return;
      }

      const valid =
        body &&
        typeof body === 'object' &&
        !Array.isArray(body) &&
        typeof body.station === 'string' &&
        typeof body.message === 'string' &&
        body.station.trim().length > 0 &&
        body.station.trim().length <= 40 &&
        body.message.trim().length > 0 &&
        body.message.trim().length <= 120;

      if (!valid) {
        json(res, 400, { error: 'INVALID_EVENT' });
        return;
      }

      const event = {
        id: nextId++,
        station: body.station.trim(),
        message: body.message.trim(),
        createdAt: new Date().toISOString()
      };

      events.push(event);
      json(res, 201, event);
      return;
    }

    res.setHeader('Allow', 'GET, POST');
    json(res, 405, { error: 'METHOD_NOT_ALLOWED' });
    return;
  }

  if (path.startsWith('/api/events/') && method === 'GET') {
    const idStr = path.slice('/api/events/'.length);
    const id = Number(idStr);

    if (!Number.isInteger(id) || id <= 0) {
      json(res, 400, { error: 'INVALID_ID' });
      return;
    }

    const event = events.find(e => e.id === id);
    if (!event) {
      json(res, 404, { error: 'EVENT_NOT_FOUND' });
      return;
    }

    json(res, 200, event);
    return;
  }

  if (path === '/api/about' && method === 'GET') {
    json(res, 200, {
      name: 'NetLab',
      version: '1.0.0'
    });
    return;
  }

  if (path === '/api/stations' && method === 'GET') {
    json(res, 200, {
      stations: [
        { id: 1, name: 'PC-01', os: 'Windows 11', status: 'online' },
        { id: 2, name: 'PC-02', os: 'Ubuntu 24.04', status: 'online' },
        { id: 3, name: 'PC-03', os: 'macOS', status: 'offline' }
      ]
    });
    return;
  }

  if (path.startsWith('/api/events/') && method === 'DELETE') {
    const id = Number(path.slice('/api/events/'.length));

    if (!Number.isInteger(id) || id <= 0) {
      json(res, 400, { error: 'INVALID_ID' });
      return;
    }

    const index = events.findIndex(e => e.id === id);
    if (index === -1) {
      json(res, 404, { error: 'EVENT_NOT_FOUND' });
      return;
    }

    events.splice(index, 1);

    res.writeHead(204);
    res.end();
    return;
  }

  if (path === '/api/slow' && method === 'GET') {
    const ms = Number(url.searchParams.get('ms') ?? 3000);
    const delay = Number.isFinite(ms) ? Math.max(0, Math.min(ms, 5000)) : 3000;
    setTimeout(() => json(res, 200, { delayedMs: delay }), delay);
    return;
  }

  if (path === '/api/error' && method === 'GET') {
    json(res, 503, { error: 'SERVICE_UNAVAILABLE' });
    return;
  }

  const known = ['/', '/api/status', '/api/about', '/api/stations',
    '/api/events', '/api/slow', '/api/error'];
  if (known.includes(path)) {
    res.setHeader('Allow', 'GET');
    json(res, 405, { error: 'METHOD_NOT_ALLOWED' });
    return;
  }

  json(res, 404, { error: 'NOT_FOUND' });
});

server.on('error', (error) => {
  console.error('Ошибка сервера:', error.message);
});

server.listen(PORT, HOST, () => {
  console.log('NetLab HTTP: http://' + HOST + ':' + PORT);
});