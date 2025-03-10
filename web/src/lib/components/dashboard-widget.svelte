<script lang="ts">
	import type { Snippet } from 'svelte';

	type Props = {
		title: string;
		content: Snippet;
	};

	let { title, content }: Props = $props();
</script>

<div
	class="rounded-box border-base-content/20 flex min-h-48 cursor-pointer flex-col gap-4 border p-4 hover:border-teal-200 hover:bg-teal-900/50"
>
	<h6 class="text-xl font-bold text-teal-700">{title}</h6>
	<input type="date" name="d" id="d" class="hidden" />
	{@render content()}
</div>
