import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.ticker as mticker
import csv
import json
import math
import random
import bisect
import os
import argparse
import fnmatch
import sys
import statistics
from enum import Enum
from typing import *


class graph_scaling(Enum):
	absolute = 0
	relative = 1


class data_label_order(Enum):
	ascending = 0,
	descending = 1


class data_label_format(Enum):
	clock = 1
	custom = 256


class scaling_info():
	def __init__(self, scaling: graph_scaling, to: str = "") -> None:
		self.type = scaling
		self.to = to


class category_info():
	def __init__(self,
	             name: str,
	             scale: scaling_info,
	             prefix: Optional[str] = None,
	             suffix: Optional[str] = None) -> None:
		self.name = name
		self.prefix = prefix if prefix else name + "_"
		self.suffix = suffix if suffix else ""
		self.scale = scale


class data_label_info():
	clock_time_scales = [
	    ("fs", "femtoseconds", 1e-15, 1e+15),
	    ("ps", "picoseconds", 1e-12, 1e+12),
	    ("ns", "nanoseconds", 1e-9, 1e+9),
	    ("µs", "microseconds", .00001, 1000000),
	    ("us", "microseconds", .00001, 1000000),
	    ("ms", "milliseconds", .001, 1000),
	    ("s", "seconds", 1, 1),
	    ("m", "minutes", 60, 1 / 60),
	    ("h", "hours", 60 * 60, (1 / 60) / 60),
	]

	unknown_time_scales = [("", "", 1, 1)]

	def __init__(self,
	             name: str = "real_time",
	             order=data_label_order.ascending,
	             format=data_label_format.clock) -> None:
		self.name = "real_time"
		self.order = order
		self.format = format
		self.format_list = data_label_info.clock_time_scales if self.format == data_label_format.clock else data_label_info.unknown_time_scales


class source_info():
	def __init__(self,
	             file_name: str,
	             prefix: str = "",
	             required: bool = False) -> None:
		self.file_name: str = file_name
		self.prefix: str = prefix
		self.required: bool = required


class analysis_info():
	def __init__(self):
		self.name = ""
		self.default_scale: scaling_info = scaling_info(
		    graph_scaling.relative, "base")
		self.categories: List[category_info] = [
		    category_info("find", self.default_scale),
		    category_info("count", self.default_scale),
		    category_info("fill", self.default_scale),
		    category_info("copy", self.default_scale),
		    category_info("swap_ranges", self.default_scale),
		    category_info("rotate", self.default_scale),
		    category_info("equal", self.default_scale)
		]
		self.data_labels = [
		    data_label_info("real_time"),
		    data_label_info("cpu_time")
		]
		self.sources: List[source_info] = [
		    source_info(
		        "libc++_bit_benchmarks.json",
		        "libc++",
		        False,
		    ),
		    source_info(
		        "libstdc++_bit_benchmarks.json",
		        "libstdc++",
		        False,
		    ),
		    source_info(
		        "vc++_bit_benchmarks.json",
		        "vc++",
		        False,
		    )
		]


class stats():
	def __init__(self, data: List[float]) -> None:
		if len(data) < 1:
			self.min = 0.0
			self.max = 0.0
			self.stddev = 0.0
			self.mean = 0.0
			self.median = 0.0
			self.mode = 0.0
			self.index_of_dispersion = 0.0
		else:
			self.min = min(data)
			self.max = max(data)
			self.mean = statistics.mean(data)
			self.stddev = statistics.stdev(data, self.mean)
			self.median = statistics.median(data)
			self.mode = statistics.mode(data)
			self.index_of_dispersion = 0
			if (self.mean == 0):
				self.index_of_dispersion = statistics.variance(
				    data) / self.mean


class label_data():
	def __init__(self, info: analysis_info, data: List[float]) -> None:
		self.label = ""
		self.name = ""
		self.base_name = ""
		self.category = ""
		self.is_noop_category = ""
		self.data = data
		self.heuristics = stats(self.data)
		self.stats = stats(self.data)
		self.name_index = 0,
		self.color_index = 0,
		self.error: Optional[str] = None


class benchmark():
	def __init__(self, data: object) -> None:
		self.labels: Dict[str, label_data] = {}
		self.stats: Dict[str, stats] = {}


class benchmark_category():
	def __init__(self):
		self.benchmarks: List[benchmark] = []
		self.stats: Dict[str, stats] = {}


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


def parse_json_info(info: analysis_info, input_name: str, j) -> analysis_info:
	input_relative_path = os.path.dirname(input_name)
	if info is None:
		info = analysis_info()
	info.name = j["name"]
	jdefault_scale = j.get("scale")
	if jdefault_scale:
		jtype = jdefault_scale["type"]
		if jtype == "relative":
			jto = jdefault_scale["to"]
			info.default_scale = scaling_info(graph_scaling.relative, jto)
		else:
			info.default_scale = scaling_info(graph_scaling.absolute, "")
	jcategories = j.get("categories")
	if jcategories:
		for jcategory in jcategories:
			name = jcategory["name"]
			jprefix = jcategory.get("prefix")
			jsuffix = jcategory.get("suffix")
			jscale = jcategory.get("scale")
			scale: Optional[scaling_info] = None
			if jscale is not None:
				jtype = jscale.get("type")
				if jtype == "relative":
					jto = jscale["to"]
					scale = scaling_info(graph_scaling.relative, jto)
				else:
					scale = scaling_info(graph_scaling.absolute, "")
			else:
				scale = info.default_scale

			info.categories.append(
			    category_info(name, scale, jprefix, jsuffix))

	jdata_labels = j.get("data_labels")
	if jdata_labels:
		info.data_labels.clear()
		for jdata_label in jdata_labels:
			dli: data_label_info = data_label_info()
			dli.name = jdata_label["name"]
			jascending = jdata_label.get("ascending")
			if jascending is bool and jascending:
				dli.order = data_label_order.ascending
			jformat = jdata_label.get("format")
			if jformat is None or jformat == "clock":
				dli.format = data_label_format.clock
				dli.format_list = data_label_info.clock_time_scales
			else:
				dli.format = data_label_format.custom
				dli.format_list = data_label_info.unknown_time_scales

			info.data_labels.append(dli)

	jsources = j["sources"]
	for jsource in jsources:
		jreq = jsource.get("required")
		jprefix = jsource.get("prefix")
		jfile = jsource["file_name"]
		if not os.path.isabs(jfile):
			jfile = os.path.normpath(
			    os.path.join(input_relative_path, jfile))
		info.sources.append(
		    source_info(jfile, jprefix,
		                jreq if isinstance(jreq, bool) else False))

	return info


def parse_json(all_benchmarks: List[benchmark], j, info: analysis_info):

	j_benchmarks_array = j["benchmarks"]
	for j_benchmark in j_benchmarks_array:
		name = j_benchmark['name']
		base_name = j_benchmark['base_name']
		benchmark = None
		potential_targets = [
		    b for b in all_benchmarks if b.base_name == base_name
		]
		potential_categories = None if info.categories == None else [
		    c for c in info.categories if c in base_name
		]

		category = ""
		benchmark_name = base_name
		point_scalar = 1
		if (len(potential_categories) > 1):
			potential_categories.sort(key=len_sorter, reverse=True)
		if len(potential_categories) > 0:
			category = potential_categories[0]
			if category in scale_categories:
				point_scalar = 1 / scale

		if (len(potential_targets) < 1):
			benchmark_name = base_name.replace(category, "").strip("_")
			for chunk in name_removals:
				benchmark_name = benchmark_name.replace(chunk, "")
			all_benchmarks.append({
			    "category": category,
			    "name": benchmark_name,
			    "base_name": base_name,
			    "data": {},
			    "statistics": {},
			    "heuristics": {
			        "max": sys.float_info.min,
			        "min": sys.float_info.max,
			    },
			    "name_index": {},
			    "color_index": {},
			    "error": None
			})
			benchmark = all_benchmarks[-1]
		else:
			benchmark = potential_targets[-1]
		data = benchmark["data"]
		statistics = benchmark["statistics"]
		heuristics = benchmark["heuristics"]
		# check for errors
		benchmark_error = j_benchmark.get('error_occurred')
		if benchmark_error != None and benchmark_error:
			benchmark["error"] = j_benchmark['error_message']
			continue
		# populate data
		for point_name_lower in data_point_names:
			point_name = point_name_lower[0]
			if point_name not in data:
				data[point_name] = []
		time_unit = j_benchmark['time_unit']
		unit_index = timescale_units.index(time_unit)
		time_scale = time_scales[unit_index]
		to_seconds_multiplier = time_scale[2]
		if name == base_name:
			# is a data point
			for point_name_lower in data_point_names:
				point_name = point_name_lower[0]
				point_list = data[point_name]
				point = j_benchmark[point_name]
				point_adjusted = point * to_seconds_multiplier * point_scalar
				point_list.append(point_adjusted)
				heuristics["min"] = min(heuristics["min"], point_adjusted)
				heuristics["max"] = max(heuristics["max"], point_adjusted)
		else:
			# is a statistic
			statistic_name = name.replace(base_name, "").strip("_")
			if statistic_name not in statistics:
				statistics[statistic_name] = {}
			statistic = statistics[statistic_name]
			for point_name_lower in data_point_names:
				point_name = point_name_lower[0]
				point = j_benchmark[point_name]
				point_adjusted = point * to_seconds_multiplier * point_scalar
				statistic[point_name] = point_adjusted

	return aggregate_categories(all_benchmarks, data_point_names)


def draw_graph(name, category, benchmarks_heuristics, data_point_names,
               time_scales):
	# initialize figures
	figures, axes = plt.subplots()

	# set name we're going to use
	figure_name = name if name != None and len(
	    name) > 0 else category.replace("_", "")

	# get the values of the time scale to perform bisecting
	time_scale_values_from_seconds = [x[2] for x in time_scales]
	benchmarks = benchmarks_heuristics["benchmarks"]
	heuristics = benchmarks_heuristics["heuristics"]
	benchmarks_max = heuristics["max"]
	benchmarks_min = heuristics["min"]
	absolute_range = benchmarks_max - benchmarks_min

	# some pattern constants, to help us be pretty
	# some color constants, to help us be pretty!
	# and differentiate graphs
	# yapf: disable
	data_point_aesthetics = [
	('#a6cee3', '/'),
	('#f255bb', 'O'),
	('#00c9ab', '\\'),
	('#b15928', 'o'),
	('#33a02c', '.'),
	('#fb9a99', '*'),
	('#e31a1c', '+'),
	('#fdbf6f', 'x'),
	('#ff7f00', '|'),
	('#cab2d6', None),
	('#6a3d9a', '-'),
	('#ffff99', 'xx'),
	('#f5f5f5', '..'),
	('#1f78b4', '||'),
	('#b2df8a', '**'),
	('#cc33cc', '--')
	]
	#yapf: enable

	# transpose data into forms we need
	benchmark_names = [b["name"] for b in benchmarks]
	bars = []
	scatters = []
	num_data_points = len(data_point_names)
	bar_padding = 0.15
	bar_height = 0.35
	bar_all_sizes = bar_height * num_data_points + bar_padding
	quarter_bar_height = bar_height * 0.25
	bar_y_positions = []

	# draw mean-based bars with error indicators
	# and draw scatter-plot points
	for bi, benchmark in enumerate(benchmarks):
		statistics = benchmark["statistics"]
		for di, data_point_name_lower in enumerate(data_point_names):
			data_point_name = data_point_name_lower[0]
			bar_y = (bi * bar_all_sizes) + (di * bar_height) + (
			    bar_padding * 0.5)
			bar_y_positions.append(bar_y)
			err = benchmark.get('error')

			color_index = benchmark["color_index"][data_point_name]
			aesthetics = data_point_aesthetics[color_index]
			color = aesthetics[0]
			colorhsv = matplotlib.colors.rgb_to_hsv(
			    matplotlib.colors.hex2color(color))
			colorhsv[2] *= 0.6
			edgecolor = matplotlib.colors.hsv_to_rgb(colorhsv)

			if err != None:
				bars.append(
				    axes.text(
				        absolute_range * 0.02,
				        bar_y + (quarter_bar_height * 2),
				        err,
				        color=color,
				        style='italic',
				        horizontalalignment='left',
				        verticalalignment='center',
				        fontsize='small'))
				continue

			mean = statistics["mean"][data_point_name]
			stddev = statistics["stddev"][data_point_name]
			hatch = aesthetics[1]
			bar = axes.barh(
			    bar_y,
			    mean,
			    height=bar_height,
			    xerr=stddev,
			    linewidth=0.2,
			    edgecolor=edgecolor,
			    color=color,
			    hatch=hatch,
			    align='edge',
			    error_kw={
			        "capsize": 5.0,
			        "mew": 1.2,
			        "ecolor": 'black',
			    },
			    alpha=0.82)
			bars.append(bar)
			# the scatter plot should be semi-transparent in color...
			xscatter = benchmark["data"][data_point_name]
			xscatter_len = len(xscatter)
			yscatter = [
			    bar_y + random.uniform(quarter_bar_height,
			                           bar_height - quarter_bar_height)
			    for _ in xscatter
			]
			scatter_alpha = 0.20 if xscatter_len < 11 else 0.10 if xscatter_len < 101 else 0.05 if xscatter_len < 1001 else 0.002
			scatter = axes.scatter(
			    xscatter,
			    yscatter,
			    color=color,
			    edgecolor='#000000',
			    linewidth=0.5,
			    alpha=scatter_alpha)
			scatters.append(scatter)

	xscaleindex = bisect.bisect_left(time_scale_values_from_seconds,
	                                 benchmarks_max)
	xscale = time_scales[xscaleindex - 1]

	def time_axis_formatting(value, pos):
		if value == 0:
			return '0'
		if value.is_integer():
			return '{0:.0f}'.format(value * xscale[3])
		return '{0:.1f}'.format(value * xscale[3])

	axes.set_xlim([0, benchmarks_max + (absolute_range * 0.25)])
	axes.xaxis.set_major_formatter(
	    mticker.FuncFormatter(time_axis_formatting))

	# have ticks drawn from base of bar graph
	# to text labels
	y_ticks = [((y + 0.5) * bar_all_sizes)
	           for y in range(0, int(len(bar_y_positions) / num_data_points))]
	y_limits = [
	    bar_y_positions[0] - bar_padding,
	    bar_y_positions[-1] + bar_height + bar_padding
	]

	# set the tick spacing
	axes.set_yticks(y_ticks)
	# label each group (each cluster along the y axes)
	# with the names of the benchmarks we ran
	axes.set_yticklabels(benchmark_names)
	# set the visual limits so we have good spacing
	axes.set_ylim(y_limits)

	# if we have 2 or more data points,
	# a legend will help us label it all
	if (num_data_points > 1):
		# a proper legend for each name in data_point_names
		legend_texts = [
		    (data_point_name[0] +
		     ('- lower=good' if data_point_name[1] else 'higher=good')
		     for data_point_name in data_point_names)
		]
		# retrieve the color/shape of the bar as a reference so we can construct
		bar_style_references = [bar[0] for bar in bars]
		# make legend
		axes.legend(bar_style_references, legend_texts)
		axes.set_xlabel('measured in ' + xscale[1])
	else:
		# no need to put a legend, it's basically fine as-is
		data_point_name = data_point_names[0]
		legend_text = (data_point_name[0], 'lower is better'
		               if data_point_name[1] else 'higher is better')
		axes.set_xlabel(legend_text[0] + ' measured in ' + xscale[1] +
		                ' - ' + legend_text[1])

	# set the benchmark name, typically derived from the file name
	axes.set_title(figure_name)
	# get a nice, clean layout
	figures.tight_layout()

	# make sure to adjust top and bottoms
	figures.subplots_adjust(bottom=0.2)

	return figures, axes


def main():
	parser = argparse.ArgumentParser(
	    description=
	    'Generate graphs from a Google-Benchmark compatible json/csv listing of data'
	)
	parser.add_argument(
	    '-i',
	    '--input',
	    nargs='?',
	    default='../results/fresh/bit_benchmarks_sources.json',
	    type=argparse.FileType('r'))
	parser.add_argument('-o', '--output_dir', nargs='?')

	args = parser.parse_args()

	if not args.output_dir:
		directoryname, filename = os.path.split(args.input)
		args.output_dir = directoryname

	random.seed(1782905257495843795)

	jinfo = json.load(args.input)
	info: analysis_info = parse_json_info(None, args.input.name, jinfo)

	for fname in [s.file_name for s in info.sources]:
		with open(fname, "r") as source_json_file:
			j = json.load(source_json_file)
			benchmarks = parse_json(benchmarks, j, info)

	# we are okay to draw
	# draw for each category
	for benchmarks_key in benchmarks:
		b = benchmarks[benchmarks_key]
		category = benchmarks_key
		if category == None or len(category) < 1:
			category = name
		benchmark_name = category.replace("_measure",
		                                  "").replace("_", " ").strip()
		figures, axes = draw_graph(benchmark_name, category, b,
		                           data_point_names, clock_time_scales)
		# save drawn figures
		save_name = benchmark_name
		savetarget = os.path.join(args.output_dir, save_name + '.png')
		print("Saving graph: {} (to '{}')".format(save_name, savetarget))
		plt.savefig(savetarget, format='png')
		plt.close(figures)
