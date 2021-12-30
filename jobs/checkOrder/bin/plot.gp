set terminal png
set output 'output/plot.png'

set key right bottom
set logscale xy
set grid
set xlabel "h"
set ylabel "relative error"
set title "Order of the numerical methods"

p "output/EE.dat" u 1:2 title "EE",\
  "output/EE.dat" u 1:($1)/2 w l title "h^1",\
  "output/RK4.dat" u 1:2 title "RK4",\
  "output/RK4.dat" u 1:($1)**4/100 w l title "h^4",\
  "output/RK5.dat" u 1:2 title "RK5",\
  "output/RK5.dat" u 1:($1)**5/2000 w l title "h^5",\
  "output/SE.dat" u 1:2 title "SE",\
  "output/SE.dat" u 1:($1)/5 w l title "h^1",\
  "output/Verlet.dat" u 1:2 title "Verlet",\
  "output/Verlet.dat" u 1:($1)**2/10 w l title "h^2",\