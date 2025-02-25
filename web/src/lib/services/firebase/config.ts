// Import Firebase modules
import { initializeApp } from 'firebase/app';
import { getAuth, signInWithEmailAndPassword } from 'firebase/auth';

const firebaseConfig = {
	apiKey: 'AIzaSyDjLE4xfLweve2O3Pc5ILByDaMkWEX6AIA',
	authDomain: 'esp-min-weather-station.firebaseapp.com',
	projectId: 'esp-min-weather-station',
	storageBucket: 'esp-min-weather-station.firebasestorage.app',
	messagingSenderId: '274881104256',
	appId: '1:274881104256:web:badf56bdaf533cd23b1965',
	measurementId: 'G-8C6WBJ133W'
};

// Initialize Firebase

const ADMIN_EMAIL = 'admin@esp.weather.com';
const ADMIN_PASS = 'admin007';

export async function init() {
	const app = initializeApp(firebaseConfig);

	await signInWithEmailAndPassword(getAuth(app), ADMIN_EMAIL, ADMIN_PASS);
}
