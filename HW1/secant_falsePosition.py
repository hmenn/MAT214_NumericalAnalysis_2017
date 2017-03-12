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

# pn=1 pn_1=0
def falsePosition(f,p0,p1):
	i=2

	q0 = f(p0)
	q1 = f(p1)

	while i<4:
		p = p1-q1*(p1-p0)/(q1-q0)

		print("P:",p)

		i =i+1
		q = f(p)

		if q*q1 <0.0:
			p0=p1
			q0=q1
		p1=p
		q1=q

	return p


def f(x):
	return -math.pow(x,3)- math.cos(x);

if __name__=="__main__":
	#print(secantMethod(f,3))

	print(falsePosition(f,-1,0))

