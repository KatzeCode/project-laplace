set terminal eps 
set output "plot1vm.eps"

set contour base
set view map
set hidden3d
set palette rgb 33,13,10
set pm3d
set ytics offset -0.5,-0.5
set xtics offset -0.5,-0.5
# unset colorbox
unset key

splot "boundary1.txt" w l lt 3
