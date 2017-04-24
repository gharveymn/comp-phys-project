import numpy as np
from scipy import interpolate
import Plotting as pl
import matplotlib.pyplot as plt


def densityGrid(numx, numy, plotGrid=True):
	# Provides x and y coordinates associated with one random z coordinate
	x = np.linspace(0, 1, 5)
	y = np.linspace(0, 1, 5)
	#x = np.random.rand(5)
	#y = np.random.rand(5)
	x, y = np.meshgrid(x, y)
	z = np.random.rand(x.size).reshape(x.shape)
	z /= z.sum()

	if plotGrid:
		fig1 = plt.figure(1)
		pl.plot2dHeatMap(fig1, x, y, z)
		pl.setGeo(1)
	pass

	f = interpolate.interp2d(x, y, z, 'cubic')
	x2 = np.linspace(0, 1, numx)
	y2 = np.linspace(0, 1, numy)
	z2 = f(x2, y2)
	z2 /= z2.sum()

	avgDensity = z2.sum() / (numx * numy)  # Per length, used for A* heuristic.

	# Uncomment this to test using smooth extremes
	#z2 = np.max(z2)/(1 + np.exp(-5000 * (z2 - np.max(z2)/2)))
	x2, y2 = np.meshgrid(x2, y2)

	# zero out negative indices from interpolation
	z2[z2 < 0] = 0

	return x2, y2, z2, avgDensity


pass


def createGraphDict(x, y, z):
	"""Creates a dictionary of adjacent indices and associated density.
        Since x,y should be a linspace, we let each density be found
        with the average between the points times the arclength."""

	def D(x1, y1, x2, y2):
		return (z[x2, y2] + z[x1, y1]) * np.sqrt((x2 - x1)**2 + (y2 - y1)**2) / 2.

	xsz = x[0].size
	ysz = y[0].size

	# We maintain two lists---one for the actual values, the other for
	# indices. This is so we can access z easily.
	xinds = range(xsz)
	yinds = range(ysz)
	allInds = [[(i, j) for j in yinds] for i in xinds]

	xlist = x[:1].flatten().tolist()
	ylist = y.T[:1].flatten().tolist()

	# The matrix flipping and such things (magic) require that the
	# indices are flipped here.
	allPoints = [[(j, i) for j in ylist] for i in xlist]
	gdict = {j: {} for i in allPoints for j in i}

	#This is bijective
	indsPtsMap = dict(
		zip([i for j in allInds for i in j], [i for j in allPoints for i in j]))
	ptsIndsMap = dict(
		zip([i for j in allPoints for i in j], [i for j in allInds for i in j]))

	# fill adjacent nodes in x direction
	#{(x_i,y_j):{(x_{i+1},y_j):D(x_{i+1},y_j,x_i,y_j)},...}
	for i in xinds:

		# looks like [[((0, 0), (0, 1)),((0, 1), (0, 2)),((0, 2), (0, 3)),...]
		compInds = list(zip(allInds[i][:-1], allInds[i][1:]))
		for p in compInds:
			gdict[indsPtsMap[p[0]]][indsPtsMap[p[1]]] = D(*p[0], *p[1])
			gdict[indsPtsMap[p[1]]][indsPtsMap[p[0]]] = D(*p[1], *p[0])
		pass
	pass

	# Just transpose so we can do the same thing for y
	allIndsT = [list(a) for a in zip(*allInds)]

	for j in yinds:

		# looks like [[((0, 0), (1, 0)),((1, 0), (2, 0)),((2, 0), (3, 0)),...]
		compInds = list(zip(allIndsT[j][:-1], allIndsT[j][1:]))
		for p in compInds:
			gdict[indsPtsMap[p[0]]][indsPtsMap[p[1]]] = D(*p[0], *p[1])
			gdict[indsPtsMap[p[1]]][indsPtsMap[p[0]]] = D(*p[1], *p[0])
		pass
	pass

	return gdict, allPoints, indsPtsMap, ptsIndsMap


pass
