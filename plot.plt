set terminal pngcairo size 1280,720
set output "plot3.png"

set contour base
set hidden3d
set pm3d

splot "boundary3.txt" w l lt 3
