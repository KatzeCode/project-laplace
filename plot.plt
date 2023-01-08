set terminal pngcairo size 1280,720
set output "plot.png"

set contour base
set hidden3d
set pm3d

splot "datafile.txt" w l lt 3
