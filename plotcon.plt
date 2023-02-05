set terminal tikz 
set output "plotsconv.tikz"
set xlabel "Iteraciones" font ",15"
set ylabel "Potencial (V)" font ",15"
set grid
set key font ",12"
set key at 1500,94
set xtics font ",12"
set ytics font ",12"

plot "boundary1initcon1.txt" w l lw 4 lc 1 lt 3 t "$V_0 = \SI{0}{V}$", "boundary1initcon2.txt" w l lw 4 lc 2 lt 3 t "$V_0 = \SI{50}{V}$", "boundary1initcon3.txt" w l lw 4 lc 3 lt 3 t "$V_0 = \SI{100}{V}$"
