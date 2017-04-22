import sys
import numpy as np
from HelperMethods import *
import Plotting as pl
import matplotlib.pyplot as plt
import collections
import threading as th

def AStar(graph, startPoint, endPoint, hScalar=1.0):
	return AStarEval(graph, startPoint, endPoint, hScalar, visited=[], distances={}, predecessors={})
pass


def AStarEval(graph, current, end, h, visited=[], distances={}, predecessors={}):
	
	"""Find the shortest path between start and end nodes in a graph using a modified Dijkstra Algorithm"""
	# we've found our end node, now find the path to it, and return
	if current == end:
		pathShortest = []
		while end != None:
			pathShortest.append(end)
			end = predecessors.get(end, None)
		pass
		return distances[current], pathShortest[::-1]
	pass
	
	# detect if it's the first time through, set current distance to zero
	if not visited: distances[current] = 0
	# process neighbors as per algorithm, keep track of predecessors
	for adjacent in graph[current]:
		if adjacent not in visited:
			adjDist = distances.get(adjacent, sys.maxsize)
			
			#We'll try using the Euclidean dist to our destination.
			curDist = distances[current] + graph[current][adjacent] + h*distancesq(adjacent, end)
			if curDist < adjDist:
				distances[adjacent] = curDist
				predecessors[adjacent] = current
			pass
		pass
	pass
	
	# neighbors processed, now mark the current node as visited
	visited.append(current)
	# finds the closest unvisited node to the start
	notVisited = dict((k, distances.get(k, sys.maxsize)) for k in graph if k not in visited)
	closest = min(notVisited, key=notVisited.get)
	# now we can take the closest node and recurse, making it current
	return AStarEval(graph, closest, end, h, visited, distances, predecessors)

pass

def dijkstra(graph, current, end, visited=[], distances={}, predecessors={}):
	
	"""Find the shortest path between start and end nodes in a graph using Dijkstra's Algorithm"""
	# we've found our end node, now find the path to it, and return
	if current == end:
		pathShortest = []
		while end != None:
			pathShortest.append(end)
			end = predecessors.get(end, None)
		pass
		return distances[current], pathShortest[::-1]
	pass
	
	# detect if it's the first time through, set current distance to zero
	if not visited: distances[current] = 0
	# process neighbors as per algorithm, keep track of predecessors
	for adjacent in graph[current]:
		if adjacent not in visited:
			adjDist = distances.get(adjacent, sys.maxsize)
			curDist = distances[current] + graph[current][adjacent]
			if curDist < adjDist:
				distances[adjacent] = curDist
				predecessors[adjacent] = current
			pass
		pass
	pass
	
	# neighbors processed, now mark the current node as visited
	visited.append(current)
	# finds the closest unvisited node to the start
	notVisited = dict((k, distances.get(k, sys.maxsize)) for k in graph if k not in visited)
	closest = min(notVisited, key=notVisited.get)

	# now we can take the closest node and recurse, making it current
	return dijkstra(graph, closest, end, visited, distances, predecessors)
pass

def dynamicDijkstra(graph, lock, current, end, dynamicPaths, visited=[], distances={}, predecessors={}):
	if current in dynamicPaths:
		if end in dynamicPaths[current]:
			pathShortest = []
			while end != None:
				pathShortest.append(end)
				end = predecessors.get(end, None)
			pass
			return distances[current], pathShortest[::-1]  # add to distance and shortest path!!!!!
		pass
	elif end in dynamicPaths:
		if current in dynamicPaths[end]:
			pathShortest = []
			while end != None:
				pathShortest.append(end)
				end = predecessors.get(end, None)
			pass
			return distances[current], pathShortest[::-1]  # add to distance and shortest path!!!!! and reverse it!!!
		pass
	pass

	"""Find the shortest path between start and end nodes in a graph using Dijkstra's Algorithm"""
	# we've found our end node, now find the path to it, and return
	if current == end:
		pathShortest = []
		while end != None:
			pathShortest.append(end)
			end = predecessors.get(end, None)
		pass

		# update dynamicPaths
		for i in range(0, len(pathShortest)):
			s = pathShortest[i]
			pathPiece = []
			pathPiece.append(s)
			if s not in dynamicPaths:
				dynamicPaths[s] = {}
			pass
			for j in range(i + 1, len(pathShortest)):
				e = pathShortest[j]
				pathPiece.append(e)
				lock.acquire()
				if e not in dynamicPaths[s]:
					dynamicPaths[s] = {e: pathPiece}
				else:
					dynamicPaths[s][e] = pathPiece
				pass
				lock.release()
			pass
		pass

		return distances[current], pathShortest[::-1]
	pass

	# detect if it's the first time through, set current distance to zero
	if not visited: distances[current] = 0
	# process neighbors as per algorithm, keep track of predecessors
	for adjacent in graph[current]:
		if adjacent not in visited:
			adjDist = distances.get(adjacent, sys.maxsize)
			curDist = distances[current] + graph[current][adjacent] + distancesq(adjacent, end)
			if curDist < adjDist:
				distances[adjacent] = curDist
				predecessors[adjacent] = current
			pass
		pass
	pass

	# neighbors processed, now mark the current node as visited
	visited.append(current)
	# finds the closest unvisited node to the start
	notVisited = dict((k, distances.get(k, sys.maxsize)) for k in graph if k not in visited)
	closest = min(notVisited, key=notVisited.get)
	# now we can take the closest node and recurse, making it current
	return dynamicDijkstra(graph, lock, closest, end, dynamicPaths, visited, distances, predecessors)
pass
