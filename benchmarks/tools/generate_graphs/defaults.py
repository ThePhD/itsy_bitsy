import source_info
from typing import List

default_input_file: str = '../sources.json'

default_sources: List[source_info] = [
    source_info(
        "libc++.itsy.bitsy.benchmarks.json",
        "libc++",
        False,
    ),
    source_info(
        "libstdc++.itsy.bitsy.benchmarks.json",
        "libstdc++",
        False,
    ),
    source_info(
        "vc++.itsy.bitsy.benchmarks.json",
        "vc++",
        False,
    )
]
