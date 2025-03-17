<script lang="ts">
	import { browser } from '$app/environment';
	import { page } from '$app/state';
	import icon from '$lib/images/icon.png';
	import { init } from '$lib/services/firebase/config';
	import { weatherData } from '$lib/states/weater-data.svelte';
	import {
		ChevronRight,
		DatabaseZap,
		Github,
		LayoutDashboard,
		TrendingUpDown
	} from 'lucide-svelte';
	import { onMount, type Snippet } from 'svelte';
	import '../app.css';

	type MenuLink = {
		label: string;
		path: string;
		icon: Snippet;
	};

	let { children } = $props();

	let open = $state(false);
	const pageTitle = $derived.by(() => {
		switch (page.url.pathname) {
			case '/data':
				return 'All Data Readings';
			case '/extreme':
				return 'Extreme Readings';
			default:
			case '/':
				return 'Dashboard';
		}
	});

	const menuLinks: MenuLink[] = [
		{ label: 'Dashboard', path: '/', icon: dashboardIcon },
		{ label: 'Extreme Readings', path: '/extreme', icon: extremeIcon },
		{ label: 'Data', path: '/data', icon: dataIcon }
	];

	onMount(async () => {
		if (browser) {
			await init();

			weatherData.init();
		}
	});
</script>

{#snippet dashboardIcon()}
	<LayoutDashboard class="ml-auto h-5 w-5" />
{/snippet}
{#snippet extremeIcon()}
	<TrendingUpDown class="ml-auto h-5 w-5" />
{/snippet}
{#snippet dataIcon()}
	<DatabaseZap class="ml-auto h-5 w-5" />
{/snippet}
{#snippet githubIcon()}
	<Github class="ml-auto h-5 w-5" />
{/snippet}

{#snippet menuLink({ label, path, icon }: MenuLink)}
	<li>
		<a
			class:active={path === page.url.pathname}
			href={path}
			onclick={() => {
				open = false;
			}}
		>
			{@render icon()}
			{label}
			<ChevronRight class="ml-auto h-5 w-5" />
		</a>
	</li>
{/snippet}

<div class="drawer md:drawer-open h-svh">
	<input id="drawer" type="checkbox" class="drawer-toggle" bind:checked={open} />
	<div class="drawer-content flex h-svh flex-col">
		<div class="navbar bg-base-300 border-base-content/20 h-16 w-full border-b">
			<div class="flex-none md:hidden">
				<label for="drawer" aria-label="open sidebar" class="btn btn-square btn-ghost">
					<svg
						xmlns="http://www.w3.org/2000/svg"
						fill="none"
						viewBox="0 0 24 24"
						class="inline-block h-6 w-6 stroke-current"
					>
						<path
							stroke-linecap="round"
							stroke-linejoin="round"
							stroke-width="2"
							d="M4 6h16M4 12h16M4 18h16"
						>
						</path>
					</svg>
				</label>
			</div>
			<div class="mx-2 flex-1 px-2"><h5 class="text-xl">{pageTitle}</h5></div>
		</div>
		<div class="flex h-[calc(100%-4rem)]">
			{@render children()}
		</div>
	</div>
	<div class="drawer-side z-10">
		<label for="drawer" aria-label="close sidebar" class="drawer-overlay"></label>
		<div class="bg-base-300 border-base-content/20 h-svh w-64 border-r">
			<div class="flex h-48 bg-blue-500 p-4 pb-0">
				<div class="rounded-box flex flex-col items-center justify-center leading-tight">
					<img src={icon} alt="SmartSkies Logo" class="h-12 w-12" />
					<h6 class="text-center text-2xl font-semibold">SmartSkies</h6>
					<p class="text-base-content/60 text-center text-xs">
						A Sustainable IoT Weather Station for Community-Based Climate
					</p>
				</div>
			</div>
			<ul class="menu h-[calc(100%-12rem)] w-full flex-nowrap overflow-auto p-2">
				{@render menuLink({
					label: menuLinks[0].label,
					path: menuLinks[0].path,
					icon: menuLinks[0].icon
				})}
				<div class="bg-base-content/20 my-2 h-[1px] w-full"></div>
				{#each menuLinks.slice(1) as item}
					{@render menuLink({ label: item.label, path: item.path, icon: item.icon })}
				{/each}
				<div class="bg-base-content/20 my-2 mt-auto h-[1px] w-full"></div>
				{@render menuLink({
					label: 'Source Code',
					path: 'https://github.com/jimcan92/weather-station',
					icon: githubIcon
				})}
			</ul>
		</div>
	</div>
</div>

<style>
	@reference "../app.css";

	.active {
		@apply bg-base-content/10 text-blue-300;
	}
</style>
