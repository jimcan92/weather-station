<script lang="ts">
	import ChartWidget from '$lib/components/chart-widget.svelte';
	import DashboardWidget from '$lib/components/dashboard-widget.svelte';
	import { weatherData } from '$lib/states/weater-data.svelte';
	import dayjs from 'dayjs';
	import { Timestamp } from 'firebase/firestore';
</script>

{#snippet latestReadings()}
	<div class="flex h-full items-center justify-evenly gap-4">
		<div class="flex flex-col items-center">
			{#if weatherData.latestData}
				<p class="text-2xl font-bold text-blue-500">{weatherData.latestData.temp} °C</p>
			{:else}
				<p class="text-2xl font-bold text-blue-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Temperature</p>
		</div>
		<div class="flex flex-col items-center">
			{#if weatherData.latestData}
				<p class="text-2xl font-bold text-red-500">{weatherData.latestData.humid} %</p>
			{:else}
				<p class="text-2xl font-bold text-blue-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Humdity</p>
		</div>
	</div>
	<div class="flex h-full items-center justify-evenly gap-4">
		<div class="flex flex-col items-center">
			{#if weatherData.latestData && weatherData.latestData.pressure}
				<p class="text-2xl font-bold text-blue-500">
					{weatherData.latestData.pressure}
					{weatherData.latestData.pressureUnit}
				</p>
			{:else}
				<p class="text-2xl font-bold text-blue-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Pressure</p>
		</div>
		<div class="flex flex-col items-center">
			{#if weatherData.latestData && weatherData.latestData.rain}
				<p class="text-2xl font-bold text-red-500">{weatherData.latestData.rain} mm</p>
			{:else}
				<p class="text-2xl font-bold text-blue-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Rain</p>
		</div>
	</div>
	<p class="text-base-content/50">
		Last updated: <span class="font-bold">
			{weatherData.latestData
				? dayjs
						.unix(weatherData.latestData.timestamp.seconds)
						.format('ddd MMM DD, YYYY @hh:mm:ss A')
				: 'N/A'}
		</span>
	</p>
{/snippet}
{#snippet extremeReading({
	value,
	unit,
	timestamp,
	label,
	color
}: {
	value?: number;
	unit: string;
	timestamp: Timestamp;
	label: string;
	color: string;
})}
	<div class="flex flex-col items-center">
		{#if value}
			<p class="text-2xl font-bold {color}">{value} {unit}</p>
			<p class="text-base-content/50 text-xs italic">
				{dayjs.unix(timestamp.seconds).format('ddd MMM DD, YYYY')}
			</p>
			<p class="text-base-content/50 text-xs italic">
				@{dayjs.unix(timestamp.seconds).format('hh:mm:ss A')}
			</p>
		{:else}
			<p class="text-2xl font-bold text-blue-500">N/A</p>
		{/if}
		<p class="text-base-content/80 text-sm">{label}</p>
	</div>
{/snippet}
{#snippet extremeDataReadings()}
	<div class="flex h-full items-center justify-evenly gap-4">
		{#if weatherData.extremeRecordedData?.lowestTempData}
			{@render extremeReading({
				label: 'Lowest Temperature',
				timestamp: weatherData.extremeRecordedData.lowestTempData.timestamp,
				value: weatherData.extremeRecordedData.lowestTempData.temp,
				unit: '°C',
				color: 'text-blue-500'
			})}
		{/if}
		{#if weatherData.extremeRecordedData?.highestTempData}
			{@render extremeReading({
				label: 'Highest Temperature',
				timestamp: weatherData.extremeRecordedData.highestTempData.timestamp,
				value: weatherData.extremeRecordedData.highestTempData.temp,
				unit: '°C',
				color: 'text-red-500'
			})}
		{/if}
	</div>
	<div class="flex h-full items-center justify-evenly gap-4">
		{#if weatherData.extremeRecordedData?.lowestHumidData}
			{@render extremeReading({
				label: 'Lowest Humidity',
				timestamp: weatherData.extremeRecordedData.lowestHumidData.timestamp,
				value: weatherData.extremeRecordedData.lowestHumidData.humid,
				unit: '%',
				color: 'text-teal-500'
			})}
		{/if}
		{#if weatherData.extremeRecordedData?.highestHumidData}
			{@render extremeReading({
				label: 'Highest Humidity',
				timestamp: weatherData.extremeRecordedData.highestHumidData.timestamp,
				value: weatherData.extremeRecordedData.highestHumidData.humid,
				unit: '%',
				color: 'text-teal-100'
			})}
		{/if}
	</div>
	<div class="flex h-full items-center justify-evenly gap-4">
		{#if weatherData.extremeRecordedData?.lowestPressureData}
			{@render extremeReading({
				label: 'Lowest Pressure',
				timestamp: weatherData.extremeRecordedData.lowestPressureData.timestamp,
				value: weatherData.extremeRecordedData.lowestPressureData.pressure,
				unit: weatherData.extremeRecordedData.lowestPressureData.pressureUnit,
				color: 'text-purple-300'
			})}
		{/if}
		{#if weatherData.extremeRecordedData?.highestPressureData}
			{@render extremeReading({
				label: 'Highest Pressure',
				timestamp: weatherData.extremeRecordedData.highestPressureData.timestamp,
				value: weatherData.extremeRecordedData.highestPressureData.pressure,
				unit: weatherData.extremeRecordedData.highestPressureData.pressureUnit,
				color: 'text-purple-600'
			})}
		{/if}
	</div>
	<div class="flex h-full items-center justify-evenly gap-4">
		{#if weatherData.extremeRecordedData?.lowestRainData}
			{@render extremeReading({
				label: 'Lowest Rain',
				timestamp: weatherData.extremeRecordedData.lowestRainData.timestamp,
				value: weatherData.extremeRecordedData.lowestRainData.rain,
				unit: 'mm',
				color: 'text-blue-300'
			})}
		{/if}
		{#if weatherData.extremeRecordedData?.highestRainData}
			{@render extremeReading({
				label: 'Highest Rain',
				timestamp: weatherData.extremeRecordedData.highestRainData.timestamp,
				value: weatherData.extremeRecordedData.highestRainData.rain,
				unit: 'mm',
				color: 'text-blue-500'
			})}
		{/if}
	</div>
{/snippet}
<div class="grid w-full gap-6 p-6 md:grid-cols-2 md:items-start lg:grid-cols-3">
	<DashboardWidget title="Latest Readings" content={latestReadings} />
	<DashboardWidget title="Extreme Data Readings" content={extremeDataReadings} />
	<div class="flex gap-4">
		<button class="btn btn-ghost" onclick={weatherData.prevDay}>-</button>
		<input type="date" class="input" name="day" id="day" bind:value={weatherData.day} />
		<button class="btn btn-ghost" onclick={weatherData.nextDay}>+</button>
	</div>
	<ChartWidget
		data={{
			labels: weatherData.tempData.map((td) =>
				dayjs.unix(td.timestamp.seconds).format('YYYY-MM-DD')
			),
			datasets: [
				{
					label: 'Temperature',
					data: weatherData.tempData.map((td) => td.value),
					borderColor: 'blue',
					backgroundColor: 'rgba(0, 0, 255, 0.2)',
					borderWidth: 2
					// fill: true
				},
				{
					label: 'Humdity',
					data: weatherData.humidData.map((td) => td.value),
					borderColor: 'teal',
					backgroundColor: 'rgba(0, 255, 0, 0.2)',
					borderWidth: 2
					// fill: true
				}
			]
		}}
		chartType="line"
	/>
	<ChartWidget
		data={{
			labels: ['10AM', '11AM', '12PM', '1PM', 'tr'],
			datasets: [
				{
					label: 'Temperature',
					data: [32, 23, 24, 25],
					borderColor: 'blue',
					backgroundColor: 'rgba(0, 0, 255, 0.2)',
					borderWidth: 2,
					fill: true
				},
				{
					label: 'Temperature',
					data: [62, 63, 54, 65],
					borderColor: 'teal',
					backgroundColor: 'rgba(0, 255, 0, 0.2)',
					borderWidth: 2,
					fill: true
				}
			]
		}}
		chartType="bar"
	/>
	<ChartWidget
		data={{
			labels: ['10AM', '11AM', '12PM', '1PM', 'tr'],
			datasets: [
				{
					label: 'Temperature',
					data: [22, 41, 24, 25],
					borderColor: 'blue',
					backgroundColor: 'rgba(0, 0, 255, 0.2)',
					borderWidth: 2,
					fill: true
				},
				{
					label: 'Temperature',
					data: [62, 63, 54, 65],
					borderColor: 'teal',
					backgroundColor: 'rgba(0, 255, 0, 0.2)',
					borderWidth: 2,
					fill: true
				}
			]
		}}
		chartType="pie"
	/>
</div>
