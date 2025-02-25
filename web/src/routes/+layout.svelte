<script lang="ts">
	import { browser } from '$app/environment';
	import { init } from '$lib/services/firebase/config';
	import { weatherData } from '$lib/states/weater-data.svelte';
	import { onMount } from 'svelte';
	import '../app.css';

	let { children } = $props();

	onMount(async () => {
		if (browser) {
			await init();

			weatherData.init();
		}
	});
</script>

<div class="flex min-h-svh w-full">
	{@render children()}
</div>
