import sys
import numpy as np


def AStar(graph, startPoint, endPoint, distance, heuristic=1.0):
	#def distance(x): return np.sqrt((endPoint[0]-x[0])**2 + (endPoint[1]-x[1])**2)/2
	return AStarEval(graph, startPoint, endPoint, heuristic, distance)
pass


def AStarEval(graph, current, end, h, distance, visited=[], distances={}, predecessors={}):
	
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
			
			#Trying to figure our the heuristic. Maybe has to do with instantaneous density?
			curDist = distances[current] + graph[current][adjacent] + distance*h
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
	return AStarEval(graph, closest, end, h, distance, visited, distances, predecessors)

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
