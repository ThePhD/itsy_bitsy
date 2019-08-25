import source_info
import os
from typing import Optional


def parse_json_info(info: source_info.source_info, input_name: str,
                    j) -> source_info:
	input_relative_path = os.path.dirname(input_name)
	if info is None:
		info = source_info.source_info()
	info.name = j["name"]
	jdefault_scale = j.get("scale")
	if jdefault_scale:
		jtype = jdefault_scale["type"]
		if jtype == "relative":
			jto = jdefault_scale["to"]
			info.default_scale = source_info.scaling_info(
			    source_info.graph_scaling.relative, jto)
		else:
			info.default_scale = source_info.scaling_info(
			    source_info.graph_scaling.absolute, "")
	jcategories = j.get("categories")
	if jcategories:
		for jcategory in jcategories:
			name = jcategory["name"]
			jcatprefix: str = jcategory.get("prefix")
			jcatsuffix: str = jcategory.get("suffix")
			jcatscale = jcategory.get("scale")
			scale: Optional[source_info.scaling_info] = None
			if jscale is not None:
				jtype = jscale.get("type")
				if jtype == "relative":
					jto = jscale["to"]
					scale = source_info.scaling_info(
					    source_info.graph_scaling.relative, jto)
				else:
					scale = source_info.scaling_info(
					    source_info.graph_scaling.absolute, "")
			else:
				scale = info.default_scale

			info.categories.append(
			    source_info.category_info(name, scale, jprefix, jsuffix))

	jdata_labels = j.get("data_labels")
	if jdata_labels:
		info.data_labels.clear()
		for jdata_label in jdata_labels:
			dli: source_info.data_label_info = source_info.data_label_info()
			dli.name = jdata_label["name"]
			jascending = jdata_label.get("ascending")
			if jascending is bool and jascending:
				dli.order = source_info.data_label_order.ascending
			jformat = jdata_label.get("format")
			if jformat is None or jformat == "clock":
				dli.format = source_info.data_label_format.clock
				dli.format_list = source_info.data_label_info.clock_time_scales
			else:
				dli.format = source_info.data_label_format.custom
				dli.format_list = source_info.data_label_info.unknown_time_scales

			info.data_labels.append(dli)

	jsources = j["sources"]
	for jsource in jsources:
		jreq: bool = jsource.get("required")
		jprefix: str = jsource.get("prefix")
		jfile: str = jsource["file_name"]
		if not os.path.isabs(jfile):
			jfile = os.path.normpath(
			    os.path.join(input_relative_path, jfile))
		info.sources.append(
		    source_info(jfile, jprefix,
		                jreq if isinstance(jreq, bool) else False))

	return info
