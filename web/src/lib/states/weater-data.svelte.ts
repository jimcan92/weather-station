import type { WeatherData } from '$lib/types/weather-data';
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
const _dataByDay = $derived(
	[..._weatherData].filter((wd) => {
		return dayjs.unix(wd.timestamp.seconds).isSame(_day, 'day');
	})
);
const _dataToday = $derived(
	[..._weatherData].filter((wd) => {
		return dayjs.unix(wd.timestamp.seconds).isSame(dayjs(), 'day');
	})
);
const _extremeRecordedData = $derived.by(() => {
	if (_weatherData.length === 0) return null;

	let minTempData: WeatherData | undefined;
	let maxTempData: WeatherData | undefined;
	let minHumidData: WeatherData | undefined;
	let maxHumidData: WeatherData | undefined;
	let minPressureData: WeatherData | undefined;
	let maxPressureData: WeatherData | undefined;
	let minRainData: WeatherData | undefined;
	let maxRainData: WeatherData | undefined;

	for (const wd of [..._weatherData]) {
		if (minTempData?.temp === undefined || wd.temp < minTempData.temp) minTempData = wd;
		if (maxTempData?.temp === undefined || wd.temp > maxTempData.temp) maxTempData = wd;
		if (minHumidData?.humid === undefined || wd.humid < minHumidData.humid) minHumidData = wd;
		if (maxHumidData?.humid === undefined || wd.humid > maxHumidData.humid) maxHumidData = wd;
		if (minPressureData?.pressure === undefined || wd.pressure < minPressureData.pressure)
			minPressureData = wd;
		if (maxPressureData?.pressure === undefined || wd.pressure > maxPressureData.pressure)
			maxPressureData = wd;
		if (minRainData?.rain === undefined || wd.rain < minRainData.rain) minRainData = wd;
		if (maxRainData?.rain === undefined || wd.rain > maxRainData.rain) maxRainData = wd;
		console.log($state.snapshot(maxRainData));

		console.log($state.snapshot(wd));
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

const _latestData = $derived(_weatherData.at(-1) ?? null);

export const weatherData = {
	get day() {
		return _day;
	},
	get all() {
		return _weatherData;
	},
	get dataByDay() {
		return _dataByDay;
	},
	get dataToday() {
		return _dataToday;
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
			orderBy('timestamp', 'asc')
		);
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
