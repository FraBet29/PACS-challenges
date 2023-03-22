set grid
set term jpeg size 1024,768
set output "plots/ERROR_CONV_RATE.jpg"

set xtic auto
set ytic auto

set logscale x
set logscale y

set title "Error convergence rate, CN method"
set xlabel "h"
set ylabel "error_inf"


plot "error_conv.txt" u 1:2 title 'Error' w linespoints lw 4, \
"error_conv.txt" u 1:($1)**2 title 'h^2' w linespoints lw 3