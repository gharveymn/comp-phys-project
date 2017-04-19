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
	findPath(*pack, startPoint, endPoint, line, 'dijkstra')

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

	#The big ugly function gets the keys into a list of tuples [(1,2),(3,4),...]
	r1 = Helper.findClosestNode(list(zip(*zip(*gdict.keys()))), startPoint)
	r2 = Helper.findClosestNode(list(zip(*zip(*gdict.keys()))), endPoint)

	print(gdict[(10,0)])
	sp = PathOptimization.dijkstra(gdict, r1, r2)
	try:
		t1 = time.time()
		if(type.lower().startswith('a')):
			sp = PathOptimization.AStar(gdict, r1, r2)
		elif(type.lower().startswith('d')):
			sp = PathOptimization.dijkstra(gdict, r1, r2)
		pass
		t2 = time.time()

		print(t2 - t1)

		line.set_xdata([p[0] for p in sp[1]])
		line.set_ydata([p[1] for p in sp[1]])
	except:
		print("Not a valid path optimizer!")
		print("We will still return though.")
	pass


pass


def findPathBoth(gdict, fig, ax, limits, startPoint, endPoint, line):

	findPath(gdict, fig, ax, limits, startPoint, endPoint, line,'a')
	findPath(gdict, fig, ax, limits, startPoint, endPoint, line,'d')

pass


def findAllPaths(pack=[], needsFigure=False):
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
	findPath(*pack, (0, 0), (8, 7.8), line, 'dijkstra')
	plt.draw()
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
	findShortestPath((0,0), (8,7.8))
pass