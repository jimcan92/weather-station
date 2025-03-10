import type { HumidData, TempData, WeatherData } from '$lib/types/weather-data';
import dayjs from 'dayjs';
import {
	collection,
	deleteDoc,
	doc,
	getFirestore,
	onSnapshot,
	orderBy,
	query
} from 'firebase/firestore';

let _day = $state(dayjs().format('YYYY-MM-DD'));
let _weatherData = $state<WeatherData[]>([]);
const _tempData = $derived.by(() => {
	const dataOfDay = _weatherData.filter((wd) => {
		console.log(dayjs.unix(wd.timestamp.seconds).isSame(_day, 'day'));
		return dayjs.unix(wd.timestamp.seconds).isSame(_day, 'day');
	});
	return dataOfDay.map(({ timestamp, temp }) => ({ timestamp, value: temp }) as TempData);
});
const _humidData = $derived(
	_weatherData.map(({ timestamp, humid }) => ({ timestamp, value: humid }) as HumidData)
);
const _lowestTempData = $derived.by(() => {
	if (_weatherData.length === 0) return null; // Handle empty data case

	const minTemp = Math.min(..._weatherData.map((wd) => wd.temp));
	const wd = _weatherData.find((a) => a.temp === minTemp);

	return wd ? ({ timestamp: wd.timestamp, value: wd.temp } as TempData) : null;
});

const _highestTempData = $derived.by(() => {
	if (_weatherData.length === 0) return null;

	const maxTemp = Math.max(..._weatherData.map((wd) => wd.temp));
	const wd = _weatherData.find((a) => a.temp === maxTemp);

	return wd ? ({ timestamp: wd.timestamp, value: wd.temp } as TempData) : null;
});
const _extremeRecordedData = $derived.by(() => {
	if (_weatherData.length === 0) return null;

	let minTempData,
		maxTempData,
		minHumidData,
		maxHumidData,
		minPressureData,
		maxPressureData,
		minRainData,
		maxRainData;

	// Single loop to find min/max values
	for (const wd of _weatherData) {
		if (!minTempData || wd.temp < minTempData.temp) minTempData = wd;
		if (!maxTempData || wd.temp > maxTempData.temp) maxTempData = wd;

		if (!minHumidData || wd.humid < minHumidData.humid) minHumidData = wd;
		if (!maxHumidData || wd.humid > maxHumidData.humid) maxHumidData = wd;

		if (!minPressureData || wd.pressure < minPressureData.pressure) minPressureData = wd;
		if (!maxPressureData || wd.pressure > maxPressureData.pressure) maxPressureData = wd;

		if (!minRainData || wd.rain < minRainData.rain) minRainData = wd;
		if (!maxRainData || wd.rain > maxRainData.rain) maxRainData = wd;
	}

	return {
		lowestTempData: minTempData,
		highestTempData: maxTempData,
		lowestHumidData: minHumidData,
		highestHumidData: maxHumidData,
		lowestPressureData: minPressureData,
		highestPressureData: maxPressureData,
		lowestRainData: minRainData,
		highestRainData: maxRainData
	};
});

const _latestData = $derived(_weatherData.length > 0 ? _weatherData[0] : null);

export const weatherData = {
	get day() {
		return _day;
	},
	get all() {
		return _weatherData;
	},
	get lowestTempData() {
		return _lowestTempData;
	},
	get highestTempData() {
		return _highestTempData;
	},
	get tempData() {
		return _tempData;
	},
	get humidData() {
		return _humidData;
	},
	get latestData() {
		return _latestData;
	},
	set day(val: string) {
		_day = val;
	},
	get extremeRecordedData() {
		return _extremeRecordedData;
	},
	init() {
		const weatherDataQuery = query(
			collection(getFirestore(), 'weather-data'),
			orderBy('timestamp', 'desc')
		); // Change to 'asc' if needed

		onSnapshot(weatherDataQuery, (snapshot) => {
			_weatherData = snapshot.docs.map((doc) => {
				const data = doc.data();
				return {
					id: doc.id,
					temp: data.temperature,
					humid: data.humidity,
					rain: data.rain,
					pressure: data.pressure,
					pressureUnit: data.pressureUnit,
					timestamp: data.timestamp
				};
			});
		});
	},
	prevDay() {
		_day = dayjs(_day).add(-1, 'day').format('YYYY-MM-DD');
	},
	nextDay() {
		_day = dayjs(_day).add(1, 'day').format('YYYY-MM-DD');
	},
	clear() {
		for (const wd of _weatherData) {
			deleteDoc(doc(getFirestore(), 'weather-data', wd.id));
		}
	},
	async addRandomData() {}
};
