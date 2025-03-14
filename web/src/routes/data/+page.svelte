<script lang="ts">
	import ChartWidget from '$lib/components/chart-widget.svelte';
	import { weatherData } from '$lib/states/weater-data.svelte';
	import dayjs from 'dayjs';
	import { ChevronLeft, ChevronRight } from 'lucide-svelte';
</script>

<div class="flex h-full w-full flex-col md:flex-row">
	<div class="flex w-full flex-col md:w-1/2">
		<div class="flex h-[110px] p-4">
			<fieldset class="fieldset w-full">
				<legend class="fieldset-legend">Weather Data for:</legend>
				<div class="flex gap-2">
					<button class="btn"><ChevronLeft class="h-5 w-5" onclick={weatherData.prevDay} /></button>
					<input type="date" class="input" bind:value={weatherData.day} />
					<button class="btn"><ChevronRight class="h-5 w-5" onclick={weatherData.nextDay} /></button
					>
				</div>
			</fieldset>
		</div>
		<div class="flex h-80 w-full p-4 pt-0">
			<div class="border-base-content/20 rounded-box flex h-full w-full border p-4">
				<ChartWidget
					data={{
						labels: weatherData.dataByDay.map((td) =>
							dayjs.unix(td.timestamp.seconds).format('hh:mm:ss A')
						),
						datasets: [
							{
								label: 'Temperature',
								data: weatherData.dataByDay.map((td) => td.temp),
								borderColor: 'red',
								backgroundColor: 'rgba(255, 0, 0, 0.2)',
								borderWidth: 2
								// fill: true
							},
							{
								label: 'Humdity',
								data: weatherData.dataByDay.map((td) => td.humid),
								borderColor: 'cyan',
								backgroundColor: 'rgba(0, 255, 255, 0.2)',
								borderWidth: 2
								// fill: true
							},
							{
								label: 'Pressure',
								data: weatherData.dataByDay.map((td) => td.pressure),
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
		</div>
	</div>
	<div
		class="border-base-content/20 flex h-[calc(100%-110px-20rem)] w-full p-4 md:h-full md:w-1/2 md:border-l"
	>
		<div class="w-full overflow-auto">
			<table class="table-xs table-pin-rows table-pin-cols table">
				<thead>
					<tr>
						<th>Timestamp</th>
						<th>Temp</th>
						<th>Humidity</th>
						<th>Pressure</th>
						<th>Rain</th>
					</tr>
				</thead>
				<tbody>
					{#each weatherData.dataByDay as wd}
						<tr>
							<th>{dayjs.unix(wd.timestamp.seconds).format('MMM-D hh:mm:ss A')}</th>
							<td>{wd.temp} °C</td>
							<td>{wd.humid} %</td>
							<td>{wd.pressure} {wd.pressureUnit}</td>
							<td>{wd.rain} mm</td>
						</tr>
					{/each}
				</tbody>
			</table>
		</div>
	</div>
</div>
