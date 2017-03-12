import math
def getPn(f,pn_1,pn_2):
	return pn_1 - (f(pn_1)*(pn_1-pn_2))/(f(pn_1)-f(pn_2))

def secantMethod(f,pn):
	if pn == 0:
		return -1
	elif pn == 1:
		return 0
	if pn == 2:
		return getPn(f,0,-1)
	else:
		pn_1 = secantMethod(f,pn-1)
		print("p2:",pn_1)
		pn_2 = secantMethod(f,pn-2)
		return getPn(f,pn_1,pn_2)


def f(x):
	return -math.pow(x,3)- math.cos(x);

if __name__=="__main__":
	print(secantMethod(f,3))

