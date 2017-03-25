reset
TITLE = "..."
set title TITLE offset char -1, char 0
set terminal windows
#set terminal windows color 'helvetica' 16 
#
#set terminal postscript color 'helvetica' 16
#set output "zeit.ps"
#
#set terminal fig color
#set output "zeit.fig"
#
set border 31
set grid
set nokey
#set logscale x
set xrange [0:5000]
set yrange [-0.01:0.01]
set xlabel 'Time [-]'
set ylabel 'Gradient [-]'
set xtics 0,5,50
set ytics -0.01,0.01,0.01
set tics out
#set size 0.7,1.
#
plot [0:50] [-0.01:0.01]\
'zeit.dat' using 3:6 with lines



















































































