import dayjs from 'dayjs';
import timezone from 'dayjs/plugin/timezone';
import utc from 'dayjs/plugin/utc';

dayjs.extend(utc);
dayjs.extend(timezone);

export function formatFirestoreTimestamp(
	timestamp: { seconds: number; nanoseconds: number },
	tz = 'Asia/Manila'
) {
	return dayjs.unix(timestamp.seconds).tz(tz).format('MMM DD, YYYY hh:mm:ss A');
}

export function timestampToDayjs(
	timestamp: { seconds: number; nanoseconds: number },
	tz = 'Asia/Manila'
) {
	return dayjs.unix(timestamp.seconds).tz(tz);
}
