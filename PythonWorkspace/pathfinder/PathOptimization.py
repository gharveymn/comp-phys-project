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
	# process adjacent nodes as per algorithm, keep track of predecessors
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
	
	# all adjacent nodes have been processed, now mark the current node as visited
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
			linkagePath = dynamicPaths[current][end]
			pathShortest = []
			for i in range(1, len(linkagePath)):
				currentLink = linkagePath[i-1]
				nextLink = linkagePath[i]
				predecessors[nextLink] = currentLink
				if not distances:
					distances[nextLink] = graph[currentLink][nextLink]
				else:
					distances[nextLink] = distances[currentLink] + graph[currentLink][nextLink]
				pass
			pass
			current = end
		pass
	elif end in dynamicPaths:
		if current in dynamicPaths[end]:
			linkagePath = dynamicPaths[end][current][::-1] #Easier just to reverse it and do the same as above
			pathShortest = []
			for i in range(1, len(linkagePath)):
				currentLink = linkagePath[i-1]
				nextLink = linkagePath[i]
				predecessors[nextLink] = currentLink
				if not distances:
					distances[nextLink] = graph[currentLink][nextLink]
				else:
					distances[nextLink] = distances[currentLink] + graph[currentLink][nextLink]
				pass
				# try:
				# 	distances[nextLink] = distances[currentLink] + graph[currentLink][nextLink]
				# except Exception as e:
				# 	distances[nextLink] = graph[currentLink][nextLink]
				# 	print(distances)
				# 	print(nextLink)
				# 	print(currentLink)
				# pass
			pass
			current = end
		pass
	pass

	"""Find the shortest path between start and end nodes in a graph using Dijkstra's Algorithm"""
	# we've found our end node, now find the path to it, and return
	if current == end:
		pathShortest = []
		while end != None:
			pathShortest.append(end) #{(f):None,(d):(e),(c):(d),(b):(c),(a):(b)}
			end = predecessors.get(end, None)
		pass

		# update dynamicPaths
		for i in range(len(pathShortest)):
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
	try:
		closest = min(notVisited, key=notVisited.get)
	except:
		plt.figure(1)
		plt.scatter(*list(zip(*visited)),c='y', zorder=2000)
		plt.scatter(*current,c='b',zorder=2000)
		if end in predecessors:
			plt.scatter(*end,c='k',zorder=2001)
		else:
			plt.scatter(*end,c='r',zorder=2000)
		pass
		curr = current
		prev = None
		while curr != None:
			prev = curr
			curr = predecessors.get(curr, None)
		pass
		start = prev
		plt.scatter(*start,c='g',zorder=2000)
		plt.show()
		raise Exception(graph[current])
	pass

	# now we can take the closest node and recurse, making it current
	return dynamicDijkstra(graph, lock, closest, end, dynamicPaths, visited, distances, predecessors)
pass
