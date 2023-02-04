set terminal eps 
set output "plot1.eps"

# set contour base
# set view map
set hidden3d
set pm3d
# set palette rgb 33,13,10
unset colorbox
unset key

splot "boundary1.txt" w l lt 3
