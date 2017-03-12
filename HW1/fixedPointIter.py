import math

def fixedPoint(g,p0,no,tol):
	i=1
	while i<= no:
		p = g(p0)

		val = abs(p-p0)

		print("Step: ", i, "P0:",format(p0,"0.7f"),"P: ", format(p,"0.7f")," |p-p0|:",format(val,"0.7f"))
		if val < tol:
			return i
		i=i+1
		p0 = p
def g_2_2_5(x):
	return math.pow(3*(pow(x,2))+3,1/4)

def g_2_2_6(x):
	return math.pow(x+1,1/3)




if __name__== "__main__":
	print("Section 2.2 Question5")
	fixedPoint(g_2_2_5,1,50,0.01)

	#print("Section 2.2 Question6")
	#fixedPoint(g_2_2_6, 1, 50, 0.01)
