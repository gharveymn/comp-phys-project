import Plotting
import DataParser
import PathOptimization
import HelperMethods as Helper

import matplotlib.pyplot as plt
import matplotlib.path as mpath
import matplotlib.patches as patches
import matplotlib.animation as animation
import matplotlib.lines as lines

import time


def findShortestPath(startPoint, endPoint, pack=[]):
	'''findShortestPath
		This is the entry point for a single calculation

		Calls:
			initData():
				-calls data parsers and rolls the data up into a dictionary (hashmap/hashtable, whatever)
				-plots that data
			findPathDijstra(args):
				-Calls the path optimizer
		
		Returns:
			pack
				Contains:
					gdict
						-data as a graph dictionary with structure {(x1,y1):{(x1',y1'):d(r,r'),...},...}
							-this can be very large! This is why pack exists, keep it on return and input it on the next go
					fig
						-the current figure, so we can keep figure consistent
					ax
						-same idea

	'''

	if not pack:
		pack = initData()
	pass

	line = lines.Line2D([], [], lw=2, c='red')
	ax = pack[2]
	ax.add_line(line)

	#In Python an asterisk (*) unpacks a tuple or list, so like: function(*[1,2,3]) <=> function(1,2,3)
	findPath(*pack, startPoint, endPoint, line, 'a')

	plt.draw()

	return pack


pass


def initData():

	plt.clf()

	#ion is interactive mode on. This makes it so the window doesn't close after processing
	plt.ion()

	#parse the rectangles
	limits, rectVects = DataParser.parseMap()

	#Get data from the quadtree file
	gdict = DataParser.parseQT(limits, rectVects)

	fig, ax = Plotting.plotBox(gdict, limits, rectVects)

	####this is pack
	return [gdict, fig, ax, limits]


pass


def findPath(gdict, fig, ax, limits, startPoint, endPoint, line, type):
	'''findPath

		Finds the shortest path with the algorithm specified by 'type'.

		calls:
			Helper.findClosestNode()	finds the valid node closest to specified start/end points
			PathOptimizer.*()		path optimization algorithm

		args:
			gdict 		 		edge graph with distances
			fig					a figure
			ax					an axis
			limits				the limits of the bounding box
			startPoint			starting point of the path
			endPoint				end point of the path
			line					2d matplotlib line object
			type					algorithm type, accepts 'd[ijkstra]' or 'a[star]'
		return:
			None

	'''

	#The big ugly function gets the keys into a list of tuples [(1,2),(3,4),...]
	r1 = Helper.findClosestNode(list(zip(*zip(*gdict.keys()))), startPoint)
	r2 = Helper.findClosestNode(list(zip(*zip(*gdict.keys()))), endPoint)

	try:
		t1 = time.time()
		if (type.lower().startswith('a')):
			sp = PathOptimization.AStar(gdict, r1, r2)
		elif (type.lower().startswith('d')):
			sp = PathOptimization.dijkstra(gdict, r1, r2)
		pass
		t2 = time.time()

		pathlength = sp[0]
		foundPath = sp[1]
		foundPath.insert(0,startPoint)
		foundPath.append(endPoint)

		print(foundPath)

		print("Time taken: {0}s".format(t2 - t1))

		# sp contains sp[0] - the path length, sp[1] the nodes taken; we set line data to the nodes
		line.set_xdata([p[0] for p in foundPath])
		line.set_ydata([p[1] for p in foundPath])
	except Exception as e:
		print("Not a valid path optimizer!")
		print("We will still return though.")
		print(str(e))
	pass


pass


def findPathBoth(gdict, fig, ax, limits, startPoint, endPoint, line):
	'''findPathBoth
		Finds the path using both algorithms.

		calls:
			findPath()		finds the shortest path with the algorithm specified by 'type'
		args:
			same as findPath
		return:
			None
	'''

	findPath(gdict, fig, ax, limits, startPoint, endPoint, line, 'a')
	findPath(gdict, fig, ax, limits, startPoint, endPoint, line, 'd')


pass


def findAllPaths(pack=[], needsFigure=False):
	'''
		Finds all paths between nodes from the quadtree

		Also tries to to live plotting, but only sometimes works.
		
		calls:
			initData()		initializes gdict, calls the data parser
			plotBox()			plots the main box
			findPath()		finds the shortest path with specified algorithm
		args:
			pack				pack includes gdict,fig,ax,limits, used to speed up repeated calls
			needsFigure		if we closed the figure set this to true to get a new one
		return:
			pack
			
	'''
	#TODO Find all paths!

	if not pack:
		pack = initData()
	pass

	if needsFigure:
		limits, rectVects = parseMap()
		fig, ax = Plotting.plotBox(pack[0], limits, rectVects)
		pack = [pack[0], fig, ax, limits]
	pass

	fig = pack[1]
	ax = pack[2]
	limits = pack[3]

	line = lines.Line2D([], [], lw=2, c='red')
	ax.add_line(line)

	numPaths = 15
	for i in range(numPaths):
		k = limits[1] * i / numPaths
		findPath(*pack, (k, 0), (8, 7.8), line, 'dijkstra')

		#Sometimes this works, sometimes it doesn't... idk.
		#Calculations are good though.
		fig.canvas.draw()
		fig.canvas.flush_events()
	pass

	return pack


pass

if __name__ == "__main__":
	#findAllPaths()
	findShortestPath((10, 0), (8, 7.8))
pass