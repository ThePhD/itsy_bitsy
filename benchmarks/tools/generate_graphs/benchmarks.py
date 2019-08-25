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
