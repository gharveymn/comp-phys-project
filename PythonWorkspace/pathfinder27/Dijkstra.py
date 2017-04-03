import random
from igraph import *


def main(gdict):
	g, edges, numKeyMap = makeGraph(gdict)
	sp = shortestpath(gdict, 'a', 'b')
	plotGraph(g,sp,edges,numKeyMap)
pass

def makeGraph(gdict):
	gNumVerts = len(gdict)
	numKeyMap = dict(zip(gdict.keys(), range(gNumVerts)))
	edges = []
	for firstVertex in gdict:
		for secondVertex in gdict[firstVertex]:
			edges.append((numKeyMap[firstVertex], numKeyMap[secondVertex]))
		pass
	pass
	
	g = Graph()
	g.add_vertices(gNumVerts)
	g.add_edges(edges)
	g.vs["name"] = gdict.keys()
	g.vs["label"] = g.vs["name"]
	g.es["label"] = [gdict[key1][key2] for key1 in gdict.keys() for key2 in gdict[key1].keys()]
	
	return g, edges, numKeyMap
pass


def plotGraph(g, sp, edges, numKeyMap):
	spnodes = sp[1]
	spedges = [None] * (len(spnodes) - 1)
	for i in range(len(spnodes) - 1):
		spedges[i] = (numKeyMap[spnodes[i]], numKeyMap[spnodes[i + 1]])
	pass
	
	spedgecolors = ["blue"] * len(edges)
	for e in edges:
		if e in spedges:
			spedgecolors[g.get_eid(e[0], e[1])] = "red"
		pass
	pass
	
	visual_style = {"vertex_label": g.vs["name"], "edge_color": spedgecolors, "edge_curved": False}
	
	plot(g, **visual_style)
pass

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
			adjDist = distances.get(adjacent, sys.maxint)
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
	notVisited = dict((k, distances.get(k, sys.maxint)) for k in graph if k not in visited)
	closest = min(notVisited, key=notVisited.get)
	# now we can take the closest node and recurse, making it current
	return shortestpath(graph, closest, end, visited, distances, predecessors)
pass


def rmList(lst, rmel):
	
	return lst[:lst.index(rmel)] + lst[lst.index(rmel)+1:]
	

if __name__ == "__main__":
	#gdict should be a second order nested dictionary of size n = number of nodes, second order vals are distances
	# gdict = {'a': {'w': 14, 'x': 7, 'y': 9},
	# 	    'b': {'w': 9, 'z': 6},
	# 	    'w': {'a': 14, 'b': 9, 'y': 2},
	# 	    'x': {'a': 7, 'y': 10, 'z': 15},
	# 	    'y': {'a': 9, 'w': 2, 'x': 10, 'z': 11},
	# 	    'z': {'b': 6, 'x': 15, 'y': 11}}
	
	numNodes = 26
	nodes = list(map(chr, range(97, 97+numNodes)))
	gdict = dict(zip(nodes, [None]*numNodes))
	
	#Fast and sloppy graph creation, still some collisions, but minimized
	#TODO create graph in a recursive way to prevent collisions
	for n in gdict:
		gdict[n] = {}
		chooseFrom = range(nodes.index(n)) + range(nodes.index(n) + 1, numNodes)
		for i in range(random.randint(1, 6)):
			rng = random.choice(chooseFrom)
			gdict[n][nodes[rng]] = random.randint(1, 20)
			rmList(chooseFrom, rng)
		pass
	pass
	
	
	main(gdict)
pass
