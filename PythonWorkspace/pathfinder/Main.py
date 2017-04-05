import Plotting as pl
import CreateGrid as cgrid
import Dijkstra as dijk
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import matplotlib.ticker as mt
import collections

def main():
	
	#GRID CREATION
	x,y,z = cgrid.densityGrid()
	
	
	#DICTIONARY CREATION
	gdict, allPoints, indsPtsMap, ptsIndsMap = cgrid.createGraphDict(x,y,z)
	print("Grid created.")
	#for key in sorted(gdict):print("%s: %s" % (key, gdict[key]))
	
	
	sp = dijk.shortestpath(gdict,(0.0,0.0),(1.0,1.0))
	print("Best path found.")
	
	fig2 = plt.figure(2)
	pl.setGeo(2)
	ax = pl.plot2dHeatMap(fig2, x, y, z)
	pl.plotPath(ax,sp[1])
	
	fig3 = plt.figure(3)
	ax2 = pl.plot3dHeatMap(fig3, x, y, z)
	xp = [i[0] for i in sp[1]]
	yp = [j[1] for j in sp[1]]
	zp = [z[ptsIndsMap[p][0]][ptsIndsMap[p][1]] for p in sp[1]]
	ax2.plot(xp,yp,zp,'k',lw=2)
	pl.setGeo(3)
	
	plt.show()
	
	
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



if __name__ == '__main__':
	main()
