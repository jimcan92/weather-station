<script lang="ts">
	import type { Snippet } from 'svelte';

	type Props = {
		title: string;
		content: Snippet;
		link: string;
	};

	let { title, content, link }: Props = $props();
</script>

<a
	href={link}
	class="rounded-box border-base-content/20 flex cursor-pointer flex-col gap-4 border p-4 hover:border-blue-200 hover:bg-blue-900/50"
>
	<h6 class="text-xl font-bold text-teal-700">{title}</h6>
	<input type="date" name="d" id="d" class="hidden" />
	{@render content()}
</a>
