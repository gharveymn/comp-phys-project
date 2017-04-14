from math import floor
import numpy as np
from numpy import random
import os

def desselect(mdict, order, point):

	if not order:
		return mdict[floor(point[0])][floor(point[1])]
	else:
		pxFrac,pxInt = math.modf(point[0])
		pyFrac,pyInt = math.modf(point[1])

		return desselect(mdict[pxInt][pyInt], order-1, (10.*pxFrac,10*pyFrac))
	pass

pass


def prepare(points, order, bounds):

	if not order:

		delx = (bounds[1]-bounds[0])/10.
		dely = (bounds[3]-bounds[2])/10.

		newmat = {}
		for i in range(10):
			for j in range(10):
				newmat[i] = {j:findClosestNode(points,(bounds[0]+(i+1./2)*delx,bounds[2]+(j+1./2)*dely))}
			pass
		pass

	else:

		newmat = decimate(bounds)
		return {prepare(points,order-1,newmat[i][j]) for i in newmat for j in newmat[i]}

	pass

pass

def decimate(bounds):

	delx = (bounds[1]-bounds[0])/10.
	dely = (bounds[3]-bounds[2])/10.

	newmat = {}
	for i in range(10):
		for j in range(10):
			newmat[i] = {j:(	bounds[0]+i*delx,	\
							bounds[1]+i*delx,	\
							bounds[2]+j*dely,	\
							bounds[3]+j*dely)	}
		pass
	pass

	return newmat
pass

def findClosestNode(points,p):
	return min(points, key=lambda x: distancesq(x, p))
pass

def distancesq(r1,r2): return (r2[0]-r1[0])**2 + (r2[1]-r1[1])**2

if __name__ == "__main__":
	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	mdict = prepare(list(zip(list(10.*random.random(20)),list(10.*random.random(20)))), 4, (0,10,0,10))
pass