# HW1 _ 131044009

import sys,math

def fx_test1(x):
	return math.pow(x,3)+4*pow(x,2)-10

def fx_test2(x):
	return x

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




def getAbsError(pn,pn1):
	return 1

def getRelativeError(pn,pn1):
	return 1

def bisection(func,a,b,e,errorFunc):

	fa = func(a)
	fb = func(b)

	print("A:","{0:.6f}".format(a)," B:","{0:.6f}".format(b),sep="",end=" ")
	print("fa:", "{0:.6f}".format(fa), " fb:", "{0:.6f}".format(fb), sep="", end=" ")

	if fa*fb > 0:
		return False

	pn = (a+b)/2.0

	print("pn:","{0:.6f}".format(pn),sep="",end=" ")

	fpn = func(pn)

	print("f(pn):","{0:.6f}".format(fpn),sep="",end="\n")


	if fpn ==0:
		return pn

	if (fpn<0 and fa<0 ) or (fpn>0 and fa>0):
		return bisection(func,pn,b,e,errorFunc)
	else: return bisection(func,a,pn,e,errorFunc)


def main(args):

	if checkArgs(args) == False:
		print("Please check arguments")


	"""print(fx_test1(1))"""

	bisection(fx_test1,1,2,0,2)




if __name__=="__main__":
	main(sys.argv[1:])