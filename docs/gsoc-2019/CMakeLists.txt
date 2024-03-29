# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# # Mimum required
cmake_minimum_required(VERSION 3.20.0)

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(itsy.bitsy.docs.gsoc-2019 VERSION 1.0.0 DESCRIPTION "Standard bit utilities to supplement the C and C++ standard libraries.")

# # Summer of Code, with Google Proposals / Writeups
find_program (LATEXMK_EXECUTABLE NAMES latexmk latexmk.exe DOC "pdflatex executable for converting documentation from latex to pdf")

if (ITSY_BITSY_DOCS_GSOC)
	set(itsy.bitsy.docs.gsoc.proposal.sources.dir "${CMAKE_CURRENT_SOURCE_DIR}/gsoc/proposal/source")
	set(itsy.bitsy.docs.gsoc.proposal.sources
		"${itsy.bitsy.docs.gsoc.proposal.sources.dir}/thephd-gsoc-2019.tex"
		"${itsy.bitsy.docs.gsoc.proposal.sources.dir}/thephd-gsoc-2019.bib"
		"${itsy.bitsy.docs.gsoc.proposal.sources.dir}/wg21.cls"
	)

	set(itsy.bitsy.docs.gsoc.proposal.input "${CMAKE_CURRENT_SOURCE_DIR}/gsoc/proposal/source/thephd-gsoc-2019.tex")
	set(itsy.bitsy.docs.gsoc.proposal.intermediate.dir "${CMAKE_CURRENT_BINARY_DIR}/gsoc/proposal")
	set(itsy.bitsy.docs.gsoc.proposal.intermediate "${itsy.bitsy.docs.gsoc.proposal.intermediate.dir}/thephd-gsoc-2019.pdf")
	set(itsy.bitsy.docs.gsoc.proposal.output.dir "${CMAKE_CURRENT_SOURCE_DIR}/gsoc/proposal")
	set(itsy.bitsy.docs.gsoc.proposal.output "${itsy.bitsy.docs.gsoc.proposal.output.dir}/2019.08.17 - ThePhD - Summer of Code Proposal - bit.pdf")
	set(itsy.bitsy.docs.gsoc.proposal.latex_command COMMAND ${LATEXMK_EXECUTABLE} -aux-directory=${itsy.bitsy.docs.gsoc.proposal.intermediate.dir} -output-directory=${itsy.bitsy.docs.gsoc.proposal.intermediate.dir} -bibtex -pdf -latexoption="-interaction=nonstopmode" -latexoption="-shell-escape" ${itsy.bitsy.docs.gsoc.proposal.input})
	add_custom_command(OUTPUT ${itsy.bitsy.docs.gsoc.proposal.output}
		COMMAND echo %PATH%
		COMMAND ${itsy.bitsy.docs.gsoc.proposal.latex_command}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${itsy.bitsy.docs.gsoc.proposal.intermediate} ${itsy.bitsy.docs.gsoc.proposal.output}
		MAIN_DEPENDENCY ${itsy.bitsy.sources.main_dependency}
		DEPENDS ${itsy.bitsy.docs.gsoc.proposal.sources}
		WORKING_DIRECTORY ${itsy.bitsy.docs.gsoc.proposal.sources.dir}
		USES_TERMINAL VERBATIM
	)
	add_custom_target(itsy.bitsy.docs.gsoc.proposal
		DEPENDS ${itsy.bitsy.docs.gsoc.proposal.output}
		SOURCES ${itsy.bitsy.docs.gsoc.proposal.sources}
	)
endif()
