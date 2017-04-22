import PathOptimization as po

# TODO:
# input:
# 	pack
# 	startpoints
#	endpoints
#
# get:
#	path for each startpoint and endpoint
#
# return:
#	dictionary of paths in form 
# {(startpoint1):{(endpoint1):[(pathpoint1),(pathpoint2),...], (endpoint2):{...}}, (startpoint2):{...}}

def findPaths(pack, pdict, lock, dynamicPaths, startPoints, endPoints):
    gdict = pack[0]

    for i in range (0, len(startPoints)):
        pdict[startPoints[i]] = {}
        for j in range (0, len(endPoints)):
            sp = po.dynamicDijkstra(gdict, lock, startPoints[i], endPoints[j], dynamicPaths)
            path = sp[1]
            pdict[startPoints[i]] = {endPoints[j]: path}
        pass
    pass
pass
	