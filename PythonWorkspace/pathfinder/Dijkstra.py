import sys

def shortestpath(graph, current, end, visited=[], distances={}, predecessors={}):
	
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
	return shortestpath(graph, closest, end, visited, distances, predecessors)

pass
