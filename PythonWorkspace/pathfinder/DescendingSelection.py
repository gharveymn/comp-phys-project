from math import modf
import numpy as np
from numpy import random
import os
from matplotlib.pyplot import scatter, figure, show, plot
import matplotlib.lines as lines
import time


def desselect(mdict, order, point, bounds):
	delx = bounds[1] - bounds[0]
	dely = bounds[3] - bounds[2]
	
	newpoint = (10. * point[0] / delx, 10. * point[1] / dely)
	
	return evaldesselect(mdict, order, newpoint)
pass


def evaldesselect(mdict, order, point):
	if not order:
		return mdict[(int(point[0]), int(point[1]))]
	else:
		pxFrac, pxInt = modf(point[0])
		pyFrac, pyInt = modf(point[1])
		
		return evaldesselect(mdict[(int(pxInt), int(pyInt))], order - 1, (10. * pxFrac, 10 * pyFrac))
	pass


pass


def prepare(pointArray, order, bounds):
	if not order:
		# t = time.time()
		delx = (bounds[1] - bounds[0]) / 10.
		dely = (bounds[3] - bounds[2]) / 10.
		
		finalmat = {}
		for i in range(10):
			for j in range(10):
				# finalmat[(i,j)] = findClosestNode(pointArray,(bounds[0]+(i+1./2)*delx,bounds[2]+(j+1./2)*dely))
				finalmat[(i, j)] = findClosestNode2(pointArray,
											 (bounds[0] + (i + .5) * delx, bounds[2] + (j + .5) * dely))
			pass
		pass
		# print("1: {0}".format(time.time() - t))
		
		return finalmat
	
	else:
		# t = time.time()
		newmat = decimate(bounds)
		print("Order: {0}, Bounds: {1}".format(order, bounds))
		return {(i, j):prepare(pointArray, order - 1, newmat[i][j]) for i in newmat for j in newmat}
	pass


pass


def decimate(bounds):
	delx = (bounds[1] - bounds[0]) / 10.
	dely = (bounds[3] - bounds[2]) / 10.
	
	newmat = {}
	for i in range(10):
		newmat[i] = {}
		for j in range(10):
			newmat[i][j] = (bounds[0] + i * delx, \
						 bounds[0] + (i + 1) * delx, \
						 bounds[2] + j * dely, \
						 bounds[2] + (j + 1) * dely)
		pass
	pass
	
	return newmat


pass


def findClosestNode(pointArray, p):
	return min(pointArray, key=lambda x:distancesq(x, p))


pass


def distancesq(r1, r2): return (r2[0] - r1[0]) ** 2 + (r2[1] - r1[1]) ** 2


def findClosestNode2(pointArray, p):
	pointArray = np.asarray(pointArray)
	deltas = pointArray - p
	return pointArray[np.argmin(np.einsum('ij,ij->i', deltas, deltas))]


pass


def tester():
	testingPoint = (1, 1)
	
	bounds = (0., 5., 0., 10.)
	randArr = list(
		zip(list((bounds[1] - bounds[0]) * random.random(20)), list((bounds[3] - bounds[2]) * random.random(20))))
	order = 1
	
	clr = makeColorDict(randArr)
	
	mdict = prepare(randArr, order, bounds)
	closest = desselect(mdict, order, testingPoint, bounds)
	
	print(closest)
	print(True) if closest in randArr else print(False)
	
	package = getScatter(mdict, order, order, clr, bounds)
	xs, ys, clrs = zip(*package)
	
	# print(mdict)
	
	fig = figure(1)
	ax = fig.gca()
	scatter(xs, ys, c=clrs, s=1)
	scatter(*zip(*randArr), c='black')
	line = lines.Line2D(*zip(*[testingPoint, closest]), lw=2, c='red')
	ax.add_line(line)
	
	show()


pass


def makeRandomArray(numPoints, bounds):
	return list(zip(list((bounds[1] - bounds[0]) * random.random(numPoints)),
				 list((bounds[3] - bounds[2]) * random.random(numPoints))))


pass


def makeColorDict(pointArray):
	return {p:(0.1 + 0.9 * random.random(), 0.1 + 0.9 * random.random(), 0.1 + 0.9 * random.random()) for p in
		   pointArray}


pass


def drawBucketMap(mdict, order, clr, pointArray):
	package = getScatter(mdict, order, order, clr)
	xs, ys, clrs = zip(*package)
	scatter(xs, ys, c=clrs, s=1)
	scatter(*zip(*pointArray), c='black', s=2)


pass


def drawFind(mdict, order, point):
	closest = desselect(mdict, order, point)
	plot(*zip(*[point, closest]), lw=1, c='red')
	scatter(*point, c='blue', s=10)


pass


def getScatter(mdict, persistentorder, order, clr, bounds, absPosX=0, absPosY=0, ret=[]):
	if order == -1:
		# mdict since last access at mdict[p] will be the value
		# scatter(absPosX,absPosY,s=1,c=clr[mdict])
		return [(absPosX, absPosY, clr[mdict])]
	# print("({0},{1})".format(absPosX,absPosY))
	else:
		mltplrx = 10 ** (order - persistentorder - 1) * (bounds[1] - bounds[0])
		mltplry = 10 ** (order - persistentorder - 1) * (bounds[3] - bounds[2])
		# TODO make absPoX,Y in middle, just take half of length on order
		for p in mdict:
			ret = ret + getScatter(mdict[p], persistentorder, order - 1, clr, bounds, absPosX + (p[0]) * mltplrx,
							   absPosY + (p[1]) * mltplry)
		pass
		
		return ret
	
	pass


pass


def timeDS(mdict, order, points):
	t1 = time.time()
	for point in points:
		desselect(mdict, order, point)
	pass
	t2 = time.time()
	return t2 - t1


pass


def timeReg(pointArray, points):
	t1 = time.time()
	for point in points:
		findClosestNode2(points, point)
	pass
	t2 = time.time()
	return t2 - t1


pass

if __name__ == "__main__":
	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	tester()
pass
