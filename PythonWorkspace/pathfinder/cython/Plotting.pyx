import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import matplotlib.ticker as mt
import matplotlib.path as mpath
import matplotlib.patches as patches

def plot2dHeatMap(fig, x, y, z):
	'''z is a 2d grid; x and y are implicit linspaces'''
	
	from mpl_toolkits.axes_grid1 \
		import SubplotDivider, LocatableAxes, Size
	
	z = np.flipud(z)
	
	divider = SubplotDivider(fig, 1, 1, 1, aspect=True)
	
	# axes for image
	ax = LocatableAxes(fig, divider.get_position())
	
	# axes for colorbar
	ax_cb = LocatableAxes(fig, divider.get_position())
	
	h = [Size.AxesX(ax),  # main axes
		Size.Fixed(0.05),  # padding, 0.1 inch
		Size.Fixed(0.2),  # colorbar, 0.3 inch
		]
	
	v = [Size.AxesY(ax)]
	
	divider.set_horizontal(h)
	divider.set_vertical(v)
	
	ax.set_axes_locator(divider.new_locator(nx=0, ny=0))
	ax_cb.set_axes_locator(divider.new_locator(nx=2, ny=0))
	
	fig.add_axes(ax)
	fig.add_axes(ax_cb)
	
	ax_cb.axis["left"].toggle(all=False)
	ax_cb.axis["right"].toggle(ticks=True)
	
	im = ax.imshow(z, cmap=cm.coolwarm, extent=(0, 1, 0, 1), interpolation="nearest")
	plt.colorbar(im, cax=ax_cb)
	plt.setp(ax_cb.get_yticklabels(), visible=False)
	
	return ax
	
pass


def plot3dHeatMap(fig, x, y, z):
	
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(x, y, z, cmap=cm.coolwarm, linewidth=0, antialiased=True)
	ax.set_zlim(0, 2 * z.max())
	ax.zaxis.set_major_locator(mt.LinearLocator(10))
	ax.zaxis.set_major_formatter(mt.NullFormatter())
	
	cbar = fig.colorbar(surf, shrink=0.5, aspect=5)
	plt.setp(cbar.ax.get_yticklabels(), visible=False)
	
	return ax

pass

def plotPath(ax, pts, ec='black', linewidth = 2):
	
	codes = [mpath.Path.MOVETO] + [mpath.Path.LINETO]*(len(pts)-1)
	path = mpath.Path(pts,codes)
	
	patch = patches.PathPatch(path, facecolor='none', edgecolor=ec, lw=linewidth)
	ax.add_patch(patch)
	
pass


def setGeo(figNum):
	mngr = plt.get_current_fig_manager()
	geom = mngr.window.geometry()
	x, y, dx, dy = geom.getRect()
	mngr.window.setGeometry((figNum-1)*dx + 50, 100, dx, dy)
pass