# HW1 _ 131044009

import sys


def checkArgs(args):

	try:
		if len(args) != 4:
			print("Invalid parameter num")
			return False

		args[0] = float(args[0]) # value of a -> start of root search
		args[1] = float(args[1]) # value of b -> end of root search

		if args[2] != "DISTANCE_TO_ROOT" and args[2] != "ABSOLUTE_ERROR" and args[2] != "RELATIVE_ERROR":
			print("Invalid type of stopping criterion")
			return False

	except ValueError:
		print("Invalid start/end of the root search interval value")
		return False

	try:
		args[3] = float(args[3])
	except ValueError:
		print("Invalid epsilon value")
		return False

	return True



def main(args):

	if checkArgs(args) == False:
		print("Please check arguments")









if __name__=="__main__":
	main(sys.argv[1:])