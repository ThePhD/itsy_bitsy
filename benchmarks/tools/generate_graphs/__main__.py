def main():
	parser = argparse.ArgumentParser(
	    description=
	    'Generate graphs from a Google-Benchmark compatible json/csv listing of data'
	)
	parser.add_argument('-i',
	                    '--input',
	                    nargs='?',
	                    default='../sources.json',
	                    type=argparse.FileType('r'))
	parser.add_argument('-o', '--output_dir', nargs='?')

	args = parser.parse_args()

	if not args.output_dir:
		directoryname, filename = os.path.split(args.input)
		args.output_dir = directoryname


if __name__ == '__main__':
	main()
