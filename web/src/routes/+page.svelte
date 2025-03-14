<script lang="ts">
	import ChartWidget from '$lib/components/chart-widget.svelte';
	import DashboardWidget from '$lib/components/dashboard-widget.svelte';
	import { weatherData } from '$lib/states/weater-data.svelte';
	import dayjs from 'dayjs';
	import { Timestamp } from 'firebase/firestore';
</script>

{#snippet latestReadings()}
	<div class="grid grid-cols-2 gap-4">
		<div class="flex flex-col items-center">
			{#if weatherData.latestData != undefined}
				<p class="text-2xl font-bold text-red-500">{weatherData.latestData.temp} °C</p>
			{:else}
				<p class="text-2xl font-bold text-red-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Temperature</p>
		</div>
		<div class="flex flex-col items-center">
			{#if weatherData.latestData != undefined}
				<p class="text-2xl font-bold text-cyan-500">{weatherData.latestData.humid} %</p>
			{:else}
				<p class="text-2xl font-bold text-cyan-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Humdity</p>
		</div>
		<!-- </div>
	<div class="flex h-full items-center justify-evenly gap-4"> -->
		<div class="flex flex-col items-center">
			{#if weatherData.latestData != undefined && weatherData.latestData.pressure != undefined}
				<p class="text-2xl font-bold text-purple-500">
					{weatherData.latestData.pressure}
					{weatherData.latestData.pressureUnit}
				</p>
			{:else}
				<p class="text-2xl font-bold text-purple-500">N/A</p>
			{/if}
			<p class="text-base-content/50 text-sm italic">Pressure</p>
		</div>
		<div class="flex flex-col items-center">
			{#if weatherData.latestData != undefined && weatherData.latestData.rain != undefined}
				<p class="text-2xl font-bold text-blue-500">{weatherData.latestData.rain} mm</p>
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
		{#if value != undefined}
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
	<div class="grid grid-cols-2 gap-4">
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
		<!-- </div>
	<div class="flex h-full items-center justify-evenly gap-4"> -->
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
		<!-- </div>
	<div class="flex h-full items-center justify-evenly gap-4"> -->
		{#if weatherData.extremeRecordedData?.lowestPressureData}
			{@render extremeReading({
				label: 'Lowest Pressure',
				timestamp: weatherData.extremeRecordedData.lowestPressureData.timestamp,
				value: weatherData.extremeRecordedData.lowestPressureData.pressure,
				unit: weatherData.extremeRecordedData.lowestPressureData.pressureUnit,
				color: 'text-purple-300'
			})}
		{/if}
		{#if weatherData.extremeRecordedData?.highestPressureData != undefined}
			{@render extremeReading({
				label: 'Highest Pressure',
				timestamp: weatherData.extremeRecordedData.highestPressureData.timestamp,
				value: weatherData.extremeRecordedData.highestPressureData.pressure,
				unit: weatherData.extremeRecordedData.highestPressureData.pressureUnit,
				color: 'text-purple-600'
			})}
		{/if}
		<!-- </div>
		 
	<div class="flex h-full items-center justify-evenly gap-4"> -->
		{#if weatherData.extremeRecordedData?.lowestRainData}
			{@render extremeReading({
				label: 'Lowest Rain',
				timestamp: weatherData.extremeRecordedData.lowestRainData.timestamp,
				value: weatherData.extremeRecordedData.lowestRainData.rain,
				unit: 'mm',
				color: 'text-blue-300'
			})}
		{/if}
		{#if weatherData.extremeRecordedData?.highestRainData != undefined}
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
{#snippet dailyReadings()}
	<div class="flex flex-col gap-4">
		<div class="flex items-center justify-center">
			<p>{dayjs().format('dddd - MMMM DD, YYYY')}</p>
		</div>

		<ChartWidget
			data={{
				labels: weatherData.dataToday.map((td) =>
					dayjs.unix(td.timestamp.seconds).format('hh:mm:ss A')
				),
				datasets: [
					{
						label: 'Temp',
						data: weatherData.dataToday.map((td) => td.temp),
						borderColor: 'red',
						backgroundColor: 'rgba(255, 0, 0, 0.2)',
						borderWidth: 2
						// fill: true
					},
					{
						label: 'Humdity',
						data: weatherData.dataToday.map((td) => td.humid),
						borderColor: 'cyan',
						backgroundColor: 'rgba(0, 255, 255, 0.2)',
						borderWidth: 2
						// fill: true
					},
					{
						label: 'Pressure',
						data: weatherData.dataToday.map((td) => td.pressure),
						borderColor: 'purple',
						backgroundColor: 'rgba(128, 0, 128, 0.2)',
						borderWidth: 2
						// fill: true
					},
					{
						label: 'Rain',
						data: weatherData.dataByDay.map((td) => td.rain),
						borderColor: 'blue',
						backgroundColor: 'rgba(0, 0, 255, 0.2)',
						borderWidth: 2
						// fill: true
					}
				]
			}}
			chartType="line"
		/>
	</div>
{/snippet}
<div class="flex h-full w-full">
	<div
		class="grid h-full w-full gap-6 overflow-y-auto p-6 md:grid-cols-2 md:items-start lg:grid-cols-3"
	>
		<DashboardWidget link="/data" title="Latest Readings" content={latestReadings} />
		<DashboardWidget link="/extreme" title="Extreme Data Readings" content={extremeDataReadings} />
		<DashboardWidget link="/data" title="Today's Readings" content={dailyReadings} />
	</div>
</div>
