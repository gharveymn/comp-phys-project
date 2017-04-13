import Plotting as pl
import CreateGrid as cgrid
import PathOpt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import time
import random
import numpy as np
from HelperMethods import *

def main():
	
	numx = 30
	numy = 30
	startPoint = (0.5,0.0)
	endPoint = (0.5,1.0)

	x,y,z,avgDensity,gdict,allPoints,indsPtsMap,ptsIndsMap = makeGrid(numx,numy)
	print("Grid created.")
	calculatePaths(x,y,z,avgDensity,gdict,allPoints,indsPtsMap,ptsIndsMap, startPoint, endPoint)
	plt.show()
	
pass

def makeGrid(numx,numy):

	#GRID CREATION
	x,y,z,avgDensity = cgrid.densityGrid(numx,numy)
	
	#DICTIONARY CREATION
	gdict, allPoints, indsPtsMap, ptsIndsMap = cgrid.createGraphDict(x,y,z)
	#for key in sorted(gdict):print("%s: %s" % (key, gdict[key]))

	return x,y,z,avgDensity,gdict,allPoints,indsPtsMap,ptsIndsMap

pass


def calculatePaths(x,y,z,avgDensity,gdict,allPoints,indsPtsMap,ptsIndsMap,startPoint,endPoint):

	r1 = min(gdict.keys(), key=lambda x: distancesq(x, startPoint))
	r2 = min(gdict.keys(), key=lambda x: distancesq(x, endPoint))
	
	start = time.time()
	sp = PathOpt.AStar(gdict,r1,r2,avgDensity, x[0][1] - x[0][0])
	end = time.time()
	print("Best path found (A*) in {0} seconds.".format(end-start))
	
	fig2 = plt.figure(2)
	pl.setGeo(2)
	ax = pl.plot2dHeatMap(fig2, x, y, z)
	pl.plotPath(ax,sp[1])
	ax.set_xlim(0, 1)
	ax.set_ylim(0, 1)
	
	fig3 = plt.figure(3)
	ax2 = pl.plot3dHeatMap(fig3, x, y, z)
	xp = [i[0] for i in sp[1]]
	yp = [j[1] for j in sp[1]]
	zp = [z[ptsIndsMap[p][0]][ptsIndsMap[p][1]] for p in sp[1]]
	ax2.plot(xp,yp,zp,'k',lw=2)
	pl.setGeo(3)
	
	plt.draw()

	start = time.time()
	sp = PathOpt.dijkstra(gdict,r1,r2)
	end = time.time()
	print("Best path found (Dijkstra) in {0} seconds.".format(end-start))
	
	fig2 = plt.figure(4)
	pl.setGeo(2)
	ax = pl.plot2dHeatMap(fig2, x, y, z)
	pl.plotPath(ax,sp[1])
	
	fig3 = plt.figure(5)
	ax2 = pl.plot3dHeatMap(fig3, x, y, z)
	xp = [i[0] for i in sp[1]]
	yp = [j[1] for j in sp[1]]
	zp = [z[ptsIndsMap[p][0]][ptsIndsMap[p][1]] for p in sp[1]]
	ax2.plot(xp,yp,zp,'k',lw=2)
	pl.setGeo(3)
	
pass


def test1(x, y, z, allPoints, gdict):
	fig1 = plt.figure(1)
	pl.setGeo(1)
	pl.plot3dHeatMap(fig1, x, y, z)
	
	zn = allPoints.copy()
	
	for subDicts in gdict.values():
		for keys in subDicts.keys():
			try:
				zn[zn.index(keys)] = subDicts[keys]
			except ValueError:
				pass
			pass
		pass
	pass
	
	fig2 = plt.figure(2)
	pl.plot2dHeatMap(fig2, x, y, z)
	
	pl.setGeo(2)
	
	plt.show()
pass

def test2(x,y,z,allPoints, gdict):
	
	zn = allPoints.copy()
	
	for subDicts in gdict.values():
		for keys in subDicts.keys():
			try:
				zn[zn.index(keys)] = subDicts[keys]
			except ValueError:
				pass
			pass
		pass
	pass
	
	fig3 = plt.figure(3)
	pl.plot3dHeatMap(fig3, x, y, z)
	
	pl.setGeo(3)
pass

def speedTest(startPoint,endPoint,avgDensity,numx,numy):
	astartimes = []
	dijktimes = []
	distance = lambda r1,r2:(r2[0]-r1[0])**2 + (r2[1]-r1[1])**2

	for i in range(100):

		x,y,z,avgDensity,gdict,allPoints,indsPtsMap,ptsIndsMap = makeGrid(numx,numy)

		r1 = min(gdict.keys(), key=lambda x: distance(x, startPoint))
		r2 = min(gdict.keys(), key=lambda x: distance(x, endPoint))	

		if(random.randint(0,1)):
			start = time.time()
			sp = PathOpt.AStar(gdict,r1,r2,avgDensity)
			end = time.time()
			astartimes += [end-start]
		else:
			start = time.time()
			sp = PathOpt.dijkstra(gdict,r1,r2)
			end = time.time()
			dijktimes += [end-start]
		pass
		
		if(np.mod(i+1,10) == 0):
			print(i+1)
		pass
	pass

	print("Average A* time: {0} seconds".format(np.average(astartimes)))
	print("Average Dijkstra time: {0} seconds".format(np.average(dijktimes)))

pass

if __name__ == '__main__':
	main()
