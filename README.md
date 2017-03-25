# comp-phys-project
PHYS 4250 project repository

Getting started:

There are two different versions here. The older one is referenced in Numerical 
Simulation in Fluid Dynamics (the book we talked about), and the newer one is 
a bit more capable, but also more difficult to figure out.

--
NaSt2D

We'll start with the old version. Sources are located in the /NaSt2D/sources/ 
folder and the entry point is main.c. 

**Compilation** The project is compiled using MinGW. If you 
don't have that, download it and add it to your PATH.

Open up CMD and cd into the the source folder and simply use the command

make -f makefile

to compile the project. This creates the file run.exe. 


**Data Collection** The program uses various .par files to define its input parameters. 
So to collect data we just input a .par file as an argument. For example, to get 
data for the driven cavity use the command 

run.exe ../examples/dcavity.par

After this runs, the source folder should contain a file called dcav.out (which 
is not expected to be readable). Using other .par files as arguments will work in 
the same way, and you can modify those files to get results that you want.

**Data Visualization** To visualize this data, navigate to the NaSt2D/examples/matlab 
folder and open the showData.m file in MATLAB. Use of this is rather straightforward 
in that you can display the data with the command 

showData('./../../source/dcav.out');

in the MATLAB console.

--
NaSt2D-2.0

I'm having more difficulty using the new version since most of it is in German, and 
the English documentation located at http://nast2d-2.de/nast/Manual/Manual.html is 
written in somewhat broken English.

Sources are located in the /NaSt2D-2.0/Program/ folder, and main.c is the entry point.

**Compilation** This is similar to before---just cd into the folder where if on Windows 
use the command 

make -f Makefile_W

otherwise just substitute with either Makefile_L or Makefile (it shouldn't make a 
difference).

**Data Collection** Same procedure as before where we can get the data by using the 
command 

run.exe ../Par/dcavity.par

Unfortunately the new .par files are written in German, but we have Google Translate 
so nbd. The main data is written to dcav.out as previously, and you can get different 
outputs by changing the .par file as before (note: kein means none).

**Data Visualization** I'm having difficulty figuring out this new paradigm, but at 
least the data isn't written to binary anymore. However, we can plot the gradient 
over time using the zeit (meaning time) files. Each data run should output a zeit.dat 
file as well. To use this, we're going to have to download GNUPLOT 
(http://www.gnuplot.info/download.html make sure you check the option to add it to 
your PATH during install). Once you have that, go to your command window and cd to 
the Program folder. Then we're going to use the command 

gnuplot

to start the program. After that all you need to do is use the command 

load 'zeit.gnu'

which is like a parameter file for GNUPLOT. This should bring up a new window which 
will display the data.

Other stuff we can do involves the datgen.c file in the Tools folder, but I'm not 
totally sure how to use it yet. You guys can figure that out.

That's all for now!