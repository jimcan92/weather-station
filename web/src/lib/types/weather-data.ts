import type { Timestamp } from 'firebase/firestore';

export interface WeatherData {
	id: string;
	temp: number;
	humid: number;
	timestamp: Timestamp;
}
