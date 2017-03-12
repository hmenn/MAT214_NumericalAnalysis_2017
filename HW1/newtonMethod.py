import math
def fx_a(x):
	return math.pow(x,3)-2*math.pow(x,2)-5

def fxx_a(x):
	return 3*math.pow(x,2)-4*x

def fx_b(x):
	return math.pow(x, 3) + 3 * math.pow(x, 2) -1

def fxx_b(x):
	return 3*math.pow(x,2)+6*x

def fx_c(x):
	return x- math.cos(x)

def fxx_c(x):
	return 1+math.sin(x)

def fx_d(x):
	return x-0.8-0.2*math.sin(x)

def fxx_d(x):
	return 1-0.2*math.cos(x)


def newtonMethod(step,f,fxx,pn_1,e):
	pn = pn_1 - f(pn_1)/fxx(pn_1)

	diff = math.fabs(pn_1-pn)
	print("Step: ", step, "pn:",format(pn,"0.7f"), "pn-1:",format(pn_1,"0.7f"),"|pn-pn_1|",format(diff,"0.7f"))
	if diff <e:
		return pn
	else:
		return newtonMethod(step+1,f,fxx,pn,e)

if __name__=="__main__":
	print(newtonMethod(1,fx_d,fxx_d,0,0.01))





