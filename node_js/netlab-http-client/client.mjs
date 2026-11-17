const BASE_URL = 'http://127.0.0.1:3041';

function delay(ms) {
	return new Promise((resolve) => setTimeout(resolve, ms));
}

async function request(path, options = {}) {
	const {
		method = 'GET',
		body,
		timeout = 1500,
		headers = {}
	} = options;

	const started = performance.now();
	const requestHeaders = body === undefined
		? { ...headers }
		: { 'Content-Type': 'application/json', ...headers };

	try {
		const response = await fetch(BASE_URL + path, {
			method,
			headers: requestHeaders,
			body: body === undefined
				? undefined
				: JSON.stringify(body),
			signal: AbortSignal.timeout(timeout)
		});

		const elapsed = Math.round(performance.now() - started);
		const contentType = response.headers.get('content-type');
        console.log('Cache-Control:',
            response.headers.get('cache-control'));
		const raw = await response.text();

		let data;
		try {
			data = JSON.parse(raw);
		} catch {
			data = raw;
		}

		console.log('\n' + method + ' ' + path);
		console.log('HTTP status:', response.status);
		console.log('response.ok:', response.ok);
		console.log('Content-Type:', contentType);
		console.log('Time:', elapsed + ' ms');
		console.log('Body:', data);

		return { status: response.status, ok: response.ok, data };
	} catch (error) {
		const elapsed = Math.round(performance.now() - started);

		console.log('\n' + method + ' ' + path);
		console.log('Нет полного HTTP-ответа');

		if (error.cause?.code === 'ECONNREFUSED') {
			console.error('Ошибка: Сервер NetLab не запущен или недоступен по адресу ' + BASE_URL);
		} else if (error.name === 'TimeoutError') {
			console.error('Ошибка: Превышено время ожидания ответа (' + timeout + ' мс)');
		} else {
			console.log('Error:', error.name);
			console.log('Message:', error.message);
		}

        console.log('Time:', elapsed + ' ms');
		return null;
	}
}

async function getStatus() {
	let result = await request('/api/status');

	// Если первый запрос не удался (вернулся null из-за сетевой ошибки/тайм-аута)
	if (!result) {
		console.log('\nПовторная попытка запроса статуса через 1 секунду...');
		await delay(1000);
		result = await request('/api/status');
	}

	return result?.data ?? null;
}

async function getEvents() {
	const result = await request('/api/events');
	return result?.data?.events ?? null;
}

async function createEvent(station, message) {
	const result = await request('/api/events', {
		method: 'POST',
		body: { station, message }
	});
	return result?.data ?? null;
}

const command = process.argv[2];

if (command === 'status') {
	const status = await getStatus();
	console.log('\nИтоговый статус:', status);
} else if (command === 'events') {
	const events = await getEvents();
	console.log('\nСписок событий:', events);
} else if (command === 'send') {
	const station = process.argv[3] || 'PC-07';
	const message = process.argv[4] || 'REQUEST_HELP';
	const created = await createEvent(station, message);
	console.log('\nСозданное событие:', created);
} else if (command === 'slow') {
	await request('/api/slow?ms=3000', {
		timeout: 4000
	});
} else {
	console.log('Использование:');
	console.log('  node client.mjs status');
	console.log('  node client.mjs events');
	console.log('  node client.mjs send [станция] [сообщение]');
	console.log('  node client.mjs slow');
}