import benchmarks


def len_sorter(x):
	return len(x)


def entry_name_sorter(b):
	return b["name"]


def is_noop_category(n):
	noop_names = ["noop", "no-op", "no op"]
	s = n.casefold()
	return s in noop_names


def aggregate_categories(all_benchmarks: List[Dict[str, object]],
                         info: analysis_info):

	benchmarks: Dict[str, benchmark_category] = {}

	def mean_sorter(b):
		if (b.get("error") != None):
			return sys.float_info.max
		mean_group = b["statistics"]["mean"]
		data_point_name = data_point_names[0][0]
		return mean_group[data_point_name]

	# find no-op category and use it in all benchmarks
	noop_benches: Optional[benchmark] = None
	for b in all_benchmarks:
		category = b["category"]
		if is_noop_category(category):
			noop_benches = benchmark(b)
			break

	for b in all_benchmarks:
		category = b["category"]
		if is_noop_category(category):
			continue

		if category not in benchmarks:
			target_category: benchmark_category = benchmark_category()
			if (noop_benches):
				target_category.benchmarks.append(noop_benches)

		target_category = benchmarks[category]
		target_entries = target_category["benchmarks"]
		target_heuristics = target_category["heuristics"]

		target_entries.append(b)
		target_heuristics["min"] = min(b["heuristics"]["min"],
		                               target_heuristics["min"])
		target_heuristics["max"] = max(b["heuristics"]["max"],
		                               target_heuristics["max"])

	for category_name in benchmarks:
		category_benchmarks = benchmarks[category_name]
		# first, sort by name so we can assign colors to each
		# benchmark appropriately (and make those
		# color assignments stable)
		entries = category_benchmarks["benchmarks"]
		entries.sort(key=entry_name_sorter)
		for bi, entry in enumerate(entries):
			entry["name_index"] = bi
			ci = entry["color_index"]
			if (len(data_point_names) < 2):
				dp = data_point_names[0]
				ci[dp[0]] = bi
			else:
				for dpi, dp in enumerate(data_point_names):
					ci[dp[0]] = dpi

		# then, sort by mean
		entries.sort(key=mean_sorter, reverse=lower_is_better)

	return benchmarks
