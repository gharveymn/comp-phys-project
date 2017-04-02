import numpy as np
import random
from scipy import interpolate
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from scipy import interpolate

def main():
	
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	
	#Provides random number of x and y coordinates associated with one random z coordinate
	#x = np.random.rand(random.randint(15, 100))
	#y = np.random.rand(random.randint(15, 100))
	x = np.random.rand(10)
	y = np.random.rand(10)
	x,y = np.meshgrid(x,y)
	
	z = np.random.rand(x.size).reshape(x.shape)
	z /= z.sum()
	
	f = interpolate.interp2d(x, y, z)
	x2 = np.linspace(0,1,1000)
	y2 = np.linspace(0,1,1000)
	z2 = f(x2,y2)
	x2, y2 = np.meshgrid(x2, y2)
	
	#Normalize
	#z /= z.sum()
	
	surf = ax.plot_surface(x2, y2, z2, cmap=cm.coolwarm,linewidth=0, antialiased=True)
	ax.set_zlim(-.5,.5)
	ax.zaxis.set_major_locator(LinearLocator(10))
	ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
	
	fig.colorbar(surf, shrink=0.5, aspect=5)
	plt.show()
	
	#interpolate y values across x dimension
	
	
pass



if __name__ == "__main__":
	main()
pass