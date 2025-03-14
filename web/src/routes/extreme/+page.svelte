<script lang="ts">
	import ChartWidget from '$lib/components/chart-widget.svelte';
	import { weatherData } from '$lib/states/weater-data.svelte';
	import { formatFirestoreTimestamp } from '$lib/utils/time';
</script>

<div class="flex h-full w-full">
	<div class="grid w-full items-center gap-4 overflow-y-auto p-4 md:grid-cols-2">
		{#if weatherData.extremeRecordedData}
			<div class="rounded-box border-base-content/20 flex h-max w-full border p-4">
				<ChartWidget
					chartType="bar"
					data={{
						labels: [
							formatFirestoreTimestamp(weatherData.extremeRecordedData.lowestTempData?.timestamp!),
							formatFirestoreTimestamp(weatherData.extremeRecordedData.highestTempData?.timestamp!)
						],
						datasets: [
							{
								label: 'Extreme Temperature Readings (°C)',
								data: [
									weatherData.extremeRecordedData?.lowestTempData?.temp ?? NaN,
									weatherData.extremeRecordedData?.highestTempData?.temp ?? NaN
								],
								borderColor: 'red',
								backgroundColor: 'rgba(255, 0, 0, 0.2)',
								borderWidth: 2
								// fill: true
							}
						]
					}}
				/>
			</div>
			<div class="rounded-box border-base-content/20 flex h-max w-full border p-4">
				<ChartWidget
					chartType="bar"
					data={{
						labels: [
							formatFirestoreTimestamp(weatherData.extremeRecordedData.lowestHumidData?.timestamp!),
							formatFirestoreTimestamp(weatherData.extremeRecordedData.highestHumidData?.timestamp!)
						],
						datasets: [
							{
								label: 'Extreme Humidity Readings (%)',
								data: [
									weatherData.extremeRecordedData?.lowestHumidData?.humid ?? NaN,
									weatherData.extremeRecordedData?.highestHumidData?.humid ?? NaN
								],
								borderColor: 'cyan',
								backgroundColor: 'rgba(0, 255, 255, 0.2)',
								borderWidth: 2
								// fill: true
							}
						]
					}}
				/>
			</div>
			<div class="rounded-box border-base-content/20 flex h-max w-full border p-4">
				<ChartWidget
					chartType="bar"
					data={{
						labels: [
							formatFirestoreTimestamp(
								weatherData.extremeRecordedData.lowestPressureData?.timestamp!
							),
							formatFirestoreTimestamp(
								weatherData.extremeRecordedData.highestPressureData?.timestamp!
							)
						],
						datasets: [
							{
								label: `Extreme Pressure Readings (${weatherData.extremeRecordedData.lowestPressureData?.pressureUnit})`,
								data: [
									weatherData.extremeRecordedData?.lowestPressureData?.pressure ?? NaN,
									weatherData.extremeRecordedData?.highestPressureData?.pressure ?? NaN
								],
								borderColor: 'purple',
								backgroundColor: 'rgba(128, 0, 128, 0.2)',
								borderWidth: 2
								// fill: true
							}
						]
					}}
				/>
			</div>
			<div class="rounded-box border-base-content/20 flex h-max w-full border p-4">
				<ChartWidget
					chartType="bar"
					data={{
						labels: [
							formatFirestoreTimestamp(weatherData.extremeRecordedData.lowestRainData?.timestamp!),
							formatFirestoreTimestamp(weatherData.extremeRecordedData.highestRainData?.timestamp!)
						],
						datasets: [
							{
								label: 'Extreme Rain Readings (mm)',
								data: [
									weatherData.extremeRecordedData?.lowestRainData?.rain ?? NaN,
									weatherData.extremeRecordedData?.highestRainData?.rain ?? NaN
								],
								borderColor: 'blue',
								backgroundColor: 'rgba(0, 0, 255, 0.2)',
								borderWidth: 2
								// fill: true
							}
						]
					}}
				/>
			</div>
		{/if}
	</div>
</div>
