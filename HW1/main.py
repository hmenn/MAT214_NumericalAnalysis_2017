# HW1 _ 131044009
import sys,math

def fx_test1(x):
	return math.pow(x,3)+4*pow(x,2)-10

def fx_6_a(x):
	return 3*x - pow(math.e,x);

def fx_6_b(x):
	return 2*x+3*math.cos(x)-pow(math.e,x);

def fx_6_c(x):
	return x*x - 4*x +4 -math.log(x,math.e);

def fx_6_d(x):
	return x+1-2*math.sin(math.pi*x);

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




def calcAbsErr(pn,pn_1):
	return abs(pn-pn_1)

def calcRelErr(pn,pn_1):
	return (abs(pn-pn_1)/abs(pn))



def bisection(step,func,a,b,e,stopCriteria,pn_1):

	if step==101:
		return None
	print("Step:",format(step,"3d"),end=" ")

	fa = func(a)
	fb = func(b)

	#print("A:",format(a,"0.7f")," B:",format(b,"0.7f"),sep="",end=" ")
	#print("fa:", format(fa,"0.7f"), " fb:", format(fb,"0.7f"), sep="", end=" ")

	if fa*fb > 0:
		print("f(a) and f(b) must have different signs")
		return None

	pn = (a+b)/2.0
	fpn = func(pn)

	#print("pn:",format(pn,"0.7f"),"f(pn):",format(fpn,"0.7f"),sep=" ",end=" ")

	absError = calcAbsErr(pn,pn_1)
	relError = calcRelErr(pn,pn_1)

	print("Absolute Error:",format(absError,"0.7f"),"Relative Error:",format(relError,"0.7f"),"E:",e,end="\n")


	if stopCriteria == "ABSOLUTE_ERROR" and absError<e:
		return pn
	elif stopCriteria =="RELATIVE_ERROR" and relError<e:
		return pn
	elif stopCriteria == "DISTANCE_ERROR" and abs(fpn)<e:
		return pn

	if (fpn<0 and fa<0 ) or (fpn>0 and fa>0):
		return bisection(step+1,func,pn,b,e,stopCriteria,pn)
	else: return bisection(step+1,func,a,pn,e,stopCriteria,pn)


def main(args):

	if checkArgs(args) == False:
		print("Please check arguments")

	# 5E-6 -> 5*10^6

	res = bisection(1,fx_6_b,args[0],args[1],args[3],args[2],0)

	if res == None:
		print("There is no Approximate root")
	else:
		print("Approximate root:",format(res,"0.8f"))

	#print(math.sin(90*math.pi/180))


if __name__=="__main__":
	main(sys.argv[1:])