set grid
set term jpeg size 1024,768
set output "CAUCHY_SOL.jpg"

set xtic auto
set ytic auto

set title "Test Cauchy Problem"
set xlabel "t"
set ylabel "y(t)"


plot "result.txt" u 2:3 title 'Computed solution' w linespoints lw 2
