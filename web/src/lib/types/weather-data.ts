import type { Timestamp } from 'firebase/firestore';

export interface WeatherData {
	id: string;
	temp: number;
	humid: number;
	rain: number;
	pressure: number;
	pressureUnit: string;
	timestamp: Timestamp;
}

export interface TempData {
	timestamp: Timestamp;
	value: number;
}

export interface HumidData {
	timestamp: Timestamp;
	value: number;
}

export interface PressureData {
	timestamp: Timestamp;
	value: number;
	unit: string;
}

export interface RainData {
	timestamp: Timestamp;
	value: number;
}
