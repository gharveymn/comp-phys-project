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

def findPaths(pack, lock, dynamicPaths, startPoints, endsPoints):
    gdict = pack[0]
    pdict = {}

    for i in range (0, len(startPoints) - 1):
        pdict[startPoints[i]] = {}
        for j in range (0, len(endsPoints) - 1):
            sp = po.dynamicDijkstra(gdict, startPoints[i], endsPoints[j], dynamicPaths)
            path = sp[1]
            pdict[startPoints[i]] = {endsPoints[j]: path}
        pass
    pass

    return pdict
pass
	