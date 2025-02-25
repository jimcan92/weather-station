import { type WeatherData } from '$lib/types/weather-data';
import { collection, deleteDoc, doc, getFirestore, onSnapshot } from 'firebase/firestore';

let _weatherData = $state<WeatherData[]>([]);

export const weatherData = {
	get all() {
		return _weatherData;
	},
	init() {
		onSnapshot(collection(getFirestore(), 'weather-data'), (snapshot) => {
			_weatherData = snapshot.docs.map((doc) => {
				const data = doc.data();
				return {
					id: doc.id,
					temp: data.temperature,
					humid: data.humidity,
					timestamp: data.timestamp
				};
			});
		});
	},
	clear() {
		for (const wd of _weatherData) {
			deleteDoc(doc(getFirestore(), 'weather-data', wd.id));
		}
	}
};
