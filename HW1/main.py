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




def checkAbsoluteError(pn,pn_1,e):
	return abs(pn-pn_1)<e

def checkRelativeError(pn,pn_1,e):
	return (abs(pn-pn_1)/abs(pn))<e



def bisection(step,func,a,b,e,stopCriteria,pn_1):

	print("Step:",step,end=" ")

	fa = func(a)
	fb = func(b)

	print("A:",format(a,"0.7f")," B:",format(b,"0.7f"),sep="",end=" ")
	print("fa:", format(fa,"0.7f"), " fb:", format(fb,"0.7f"), sep="", end=" ")

	if fa*fb > 0:
		return False

	pn = (a+b)/2.0

	print("pn:",format(pn,"0.7f"),sep="",end=" ")

	fpn = func(pn)

	print("f(pn):",format(fpn,"0.7f"),sep="",end="\n")


	if stopCriteria == "ABSOLUTE_ERROR" and checkAbsoluteError(pn,pn_1,e):
		return pn
	elif stopCriteria =="RELATIVE_ERROR" and checkRelativeError(pn,pn_1,e):
		return pn
	elif stopCriteria == "DISTANCE_ERROR" and (fpn<e):
		return pn

	if (fpn<0 and fa<0 ) or (fpn>0 and fa>0):
		return bisection(step+1,func,pn,b,e,stopCriteria,pn)
	else: return bisection(step+1,func,a,pn,e,stopCriteria,pn)


def main(args):

	if checkArgs(args) == False:
		print("Please check arguments")

	"""print(fx_test1(1))"""

	bisection(1,fx_test1,1,2,args[3],args[2],0)




if __name__=="__main__":
	main(sys.argv[1:])