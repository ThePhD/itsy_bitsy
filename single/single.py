#!/usr/bin/env python

# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

import argparse
import os, sys
import re
import datetime as dt
from io import StringIO

description = "Converts itsy.bitsy to a single file for convenience."

# command line parser
parser = argparse.ArgumentParser(
    usage='%(prog)s [options...]', description=description)
parser.add_argument(
    '--output',
    '-o',
    nargs='+',
    help=
    'name and location of where to place file (and forward declaration file)',
    metavar='file',
    default=['single/include/itsy/bitsy.hpp', 'single/include/itsy/forward.hpp'])
parser.add_argument(
    '--input',
    '-i',
    help='the path to use to get to the itsy.bitsy files',
    metavar='path',
    default=os.path.normpath(
        os.path.dirname(os.path.realpath(__file__)) + '/../include'))
parser.add_argument('--quiet', help='suppress all output', action='store_true')
args = parser.parse_args()

single_file = ''
forward_single_file = ''
single_file = os.path.normpath(args.output[0])

if len(args.output) > 1:
	forward_single_file = args.output[1]
else:
	a, b = os.path.splitext(single_file)
	a = os.path.dirname(single_file)
	forward_single_file = os.path.normpath(
	    os.path.join(a + '/', 'forward' + b))

single_file_dir = os.path.dirname(single_file)
forward_single_file_dir = os.path.dirname(forward_single_file)

project_path = args.input
working_dir = os.getcwd()
os.chdir(project_path)

# If the user didn't provide absolute paths then construct them based on the current working dir.
if not os.path.isabs(single_file):
	single_file = os.path.join(working_dir, single_file)
	single_file_dir = os.path.join(working_dir, single_file_dir)

if not os.path.isabs(forward_single_file):
	forward_single_file = os.path.join(working_dir, forward_single_file)
	forward_single_file_dir = os.path.join(working_dir,
	                                       forward_single_file_dir)

intro = """// =============================================================================
//
// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.
//
// =============================================================================

/* This is an automatically generated header file.
*  Generated from the itsy.bitsy repository at {time},
*  Version {version} (Revision {revision}).
*/

#ifndef {guard}
#define {guard}

"""

includes = set([])
standard_include = re.compile(r'#include <(.*?)>')
local_include = re.compile(r'#(\s*?)include "(.*?)"')
project_include = re.compile(r'#(\s*?)include <(itsy/.*?)>')
pragma_once_cpp = re.compile(r'(\s*)#(\s*)pragma(\s+)once')
ifndef_cpp = re.compile(r'#ifndef ITSY_BITSY_.*?_HPP')
define_cpp = re.compile(r'#define ITSY_BITSY_.*?_HPP')
endif_cpp = re.compile(r'#endif // ITSY_BITSY_.*?_HPP')
forward_cpp = re.compile(r'ITSY_BITSY_FORWARD_HPP')
forward_detail_cpp = re.compile(r'ITSY_BITSY_FORWARD_DETAIL_HPP')


def get_include(line, base_path):
	local_match = local_include.match(line)
	if local_match:
		# local include found
		full_path = os.path.normpath(
		    os.path.join(base_path, local_match.group(2))).replace(
		        '\\', '/')
		return full_path
	project_match = project_include.match(line)
	if project_match:
		# project include found
		full_path = os.path.normpath(
		    os.path.join(project_path, project_match.group(2))).replace(
		        '\\', '/')
		return full_path
	return None


def is_include_guard(line):
	is_regular_guard = ifndef_cpp.match(line) or define_cpp.match(
	    line) or endif_cpp.match(line) or pragma_once_cpp.match(line)
	if is_regular_guard:
		return not forward_cpp.search(line) and not forward_detail_cpp.search(line)
	return is_regular_guard


def get_revision():
	return os.popen('git rev-parse --short HEAD').read().strip()


def get_version():
	return os.popen('git describe --tags --abbrev=0').read().strip()


def process_file(filename, out):
	global includes
	filename = os.path.normpath(filename)
	relativefilename = filename.replace(project_path + os.sep, "").replace(
	    "\\", "/")

	if filename in includes:
		return

	includes.add(filename)

	if not args.quiet:
		print('processing {}'.format(filename))
		
	out.write('// beginning of {}\n\n'.format(relativefilename))
	empty_line_state = True

	with open(filename, 'r', encoding='utf-8') as f:
		for line in f:
			# skip comments
			if line.startswith('//'):
				continue

			# skip include guard non-sense
			if is_include_guard(line):
				continue

			# get relative directory
			base_path = os.path.dirname(filename)

			# check if it's a standard file
			std = standard_include.search(line)
			if std:
				std_file = os.path.join('std', std.group(0))
				#if std_file in includes:
				#	continue
				includes.add(std_file)

			# see if it's an include file
			name = get_include(line, base_path)

			if name:
				process_file(name, out)
				continue

			empty_line = len(line.strip()) == 0

			if empty_line and empty_line_state:
				continue

			empty_line_state = empty_line

			# line is fine
			out.write(line)

	out.write('// end of {}\n\n'.format(relativefilename))


version = get_version()
revision = get_revision()
if not version:
	version = "Tip"
include_guard = 'ITSY_BITSY_SINGLE_INCLUDE_HPP'
forward_include_guard = 'ITSY_BITSY_SINGLE_INCLUDE_FORWARD_HPP'

processed_files = [os.path.join(project_path, x) for x in ['itsy/bitsy.hpp']]
forward_processed_files = [
    os.path.join(project_path, x) for x in ['itsy/forward.hpp']
]
result = ''
forward_result = ''

if not args.quiet:
	print('Current version: {version} (revision {revision})'.format(
	    version=version, revision=revision))
	print('Project path: {}\n'.format(project_path))
	print('Creating single header for itsy.bitsy ({})'.format(processed_files[0]))

ss = StringIO()
ss.write(
    intro.format(
        time=dt.datetime.utcnow(),
        revision=revision,
        version=version,
        guard=include_guard))
for processed_file in processed_files:
	process_file(processed_file, ss)

ss.write('#endif // {}\n'.format(include_guard))
result = ss.getvalue()
ss.close()

if not args.quiet:
	print('finished creating single header for itsy.bitsy\n')

if not args.quiet:
	print('Creating single forward declaration header for itsy.bitsy ({})'.format(forward_processed_files[0]))

forward_ss = StringIO()
forward_ss.write(
    intro.format(
        time=dt.datetime.utcnow(),
        revision=revision,
        version=version,
        guard=forward_include_guard))
for forward_processed_file in forward_processed_files:
	process_file(forward_processed_file, forward_ss)

forward_ss.write('#endif // {}\n'.format(forward_include_guard))
forward_result = forward_ss.getvalue()
forward_ss.close()

if not args.quiet:
	print('finished creating single forward declaration header for itsy.bitsy\n')

# Create the output directories if they don't already exist.
os.makedirs(single_file_dir, exist_ok=True)
os.makedirs(forward_single_file_dir, exist_ok=True)

with open(single_file, 'w', encoding='utf-8') as f:
	if not args.quiet:
		print('writing {}...'.format(single_file))
	f.write(result)

with open(forward_single_file, 'w', encoding='utf-8') as f:
	if not args.quiet:
		print('writing {}...'.format(forward_single_file))
	f.write(forward_result)
