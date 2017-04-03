from CreateGrid import *
from Plotting import *
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import matplotlib.ticker as mt

def main():
	
	fig1 = plt.figure(1)
	#ax = fig1.gca(projection='3d')
	
	setGeo(1)
	
	#This holds all line weight information on this grid.
	
	#GRID CREATION
	x,y,z = densityGrid()
	
	# surf = ax.plot_surface(x, y, z, cmap=cm.coolwarm, linewidth=0, antialiased=True)
	# ax.set_zlim(0, 2 * z.max())
	# ax.zaxis.set_major_locator(mt.LinearLocator(10))
	# ax.zaxis.set_major_formatter(mt.NullFormatter())
	#
	# cbar = fig1.colorbar(surf, shrink=0.5, aspect=5)
	# plt.setp(cbar.ax.get_yticklabels(), visible=False)
	
	
	plot2dHeatMap(fig1, z)
	
	#DICTIONARY CREATION
	gdict, allPoints = createGraphDict(x,y,z)
	
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
	plot2dHeatMap(fig2, z)
	
	setGeo(2)
	
	plt.show()
	
	
pass

if __name__ == '__main__':
	main()
