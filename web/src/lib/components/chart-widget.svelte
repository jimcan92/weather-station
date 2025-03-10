<script lang="ts">
	import type { ChartConfiguration, ChartType } from 'chart.js';
	import Chart from 'chart.js/auto';
	import { onMount } from 'svelte';

	let chartCanvas: HTMLCanvasElement | null = null;
	let chartInstance: Chart | null = null;

	type Props = {
		data: ChartConfiguration['data'];
		chartType?: ChartType;
	};

	let { data, chartType = 'line' }: Props = $props();

	onMount(() => {
		if (chartCanvas) {
			chartInstance = new Chart(chartCanvas, {
				type: chartType,
				data,
				options: {
					responsive: true,
					maintainAspectRatio: false
					// scales: {
					// 	y: { beginAtZero: true }
					// }
				}
			});
		}
	});

	$effect(() => {
		if (chartInstance) {
			chartInstance.data = data;
			chartInstance.update();
		}
	});
</script>

<div class="flex max-h-64">
	<canvas bind:this={chartCanvas}></canvas>
</div>
