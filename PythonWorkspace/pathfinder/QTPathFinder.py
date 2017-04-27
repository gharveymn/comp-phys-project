import Plotting
import DataParser
import PathOptimization
import HelperMethods as Helper

import matplotlib.pyplot as plt
import matplotlib.path as mpath
import matplotlib.patches as patches
import matplotlib.animation as animation
import matplotlib.lines as lines
import numpy as np
import threading as th
import ThreadedPartition
import sys

import time
import random


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
		plt.show()
	pass

	line = lines.Line2D([], [], lw=2, c='red')
	ax = pack[2]
	ax.add_line(line)

	#In Python an asterisk (*) unpacks a tuple or list, so like: function(*[1,2,3]) <=> function(1,2,3)
	findPath(*pack, startPoint, endPoint, line, 'a')

	plt.show()

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

	sys.setrecursionlimit(1500)

	try:
		t1 = time.time()
		if (type.lower().startswith('a')):
			sp = PathOptimization.AStar(gdict, r1, r2)
		elif (type.lower().startswith('d')):
			sp = PathOptimization.dijkstra(gdict, r1, r2)
		pass
		t2 = time.time()

		print(sp[1])
		print(r1)
		print(r2)

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


def findAllPaths(pack=[]):
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
	sys.setrecursionlimit(1500)
	t1 = time.time()
	if not pack:
		pack = initData()
	pass

	gdict = pack[0]
	numNodes = len(gdict)
	dynamicPaths= {}

	threads = []

	lock = th.Lock()

	fig = pack[1]
	ax = pack[2]
	limits = pack[3]

	# path dictionary
	pdict = {}

	allPoints = list(gdict.keys())
	endPoints = allPoints #We just filter this later
	numThreads = 4 #+-1
	stride = int(len(allPoints)/numThreads)

	for i in range(0, len(allPoints), stride):
		startPoints = allPoints[i:i+stride]

		#ThreadedPartition.findPaths(pack, pdict, lock, dynamicPaths, startPoints, endPoints)
		t = th.Thread(target = ThreadedPartition.findPaths, args = (pack, pdict, lock, dynamicPaths, startPoints, endPoints))
		t.start()
		threads.append(t)
	pass

	totalPaths = len(allPoints)**2 - len(allPoints)
	reportStatus(pdict,totalPaths,threads[len(threads)-1])

	for t in threads:
		t.join()
	pass
	t2 = time.time()
	print("Time taken: {0}s".format(t2 - t1))
	plt.show()

	print(len(pdict))
	print(len(dynamicPaths))

	with lock:
		for p in pdict:
			if len(pdict[p]) != len(dynamicPaths[p]):
				print("len(pdict[{0}])={1}".format(p,len(pdict[p])))
				print("len(dynamicPaths[{0}])={1}".format(p,len(dynamicPaths[p])))
				for k,v in pdict[p].items():
					if k not in dynamicPaths[p]:
						print("{0}:{1}".format(k,v))
						print("\n")
					pass
				pass
			pass
		pass
	pass

	return pack, pdict
pass


def plotPathWithResults(pack,pdict,startPoint,endPoint):

	r1 = Helper.findClosestNode(list(zip(*zip(*pdict.keys()))), startPoint)
	r2 = Helper.findClosestNode(list(zip(*zip(*pdict.keys()))), endPoint)

	foundPath = pdict[r1][r2]
	foundPath.insert(0,startPoint)
	foundPath.append(endPoint)

	Plotting.plotPath(pack[2],foundPath,ec='r')

pass


def reportStatus(pdict,total,sentinel):
	if(sentinel.isAlive()):
		numFound = 0
		for v in pdict.values():
			numFound += len(v)
		pass

		print("pdict has acquired pathing for {0} of {1} total paths".format(numFound,total))
		t = th.Timer(5,reportStatus,[pdict,total,sentinel])
		t.start()
	pass
pass


if __name__ == "__main__":
	findAllPaths()
	#findShortestPath((10, 0), (7, 7))
pass