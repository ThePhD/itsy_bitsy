import Enum
from typing import Optional
import defaults


class graph_scaling(Enum):
	absolute = 0
	relative = 1


class data_label_order(Enum):
	ascending = 0,
	descending = 1


class data_label_format(Enum):
	custom = -1
	clock = 0


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
		self.categories: List[category_info] = []
		self.data_labels = [
		    data_label_info("real_time"),
		    data_label_info("cpu_time")
		]
		self.sources: List[source_info] = defaults.default_sources
