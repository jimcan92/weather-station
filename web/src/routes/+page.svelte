<script lang="ts">
	import { weatherData } from '$lib/states/weater-data.svelte';
	import { formatFirestoreTimestamp } from '$lib/utils/time';
</script>

<div class="flex flex-col">
	<button class="btn" onclick={() => weatherData.clear()}>Clear</button>
	<table class="table">
		<thead>
			<tr>
				<th>Timestamp</th>
				<th>Temperature</th>
				<th>Humidity</th>
			</tr>
		</thead>
		<tbody>
			{#each weatherData.all.sort((a, b) => a.timestamp.toMillis() - b.timestamp.toMillis()) as d}
				<tr>
					<th>{formatFirestoreTimestamp(d.timestamp)}</th>
					<td>{d.temp}</td>
					<td>{d.humid}</td>
				</tr>
			{/each}
		</tbody>
	</table>
</div>
