set terminal pngcairo size 500, 500 font "Helvetica, 20"
set output "check.png"

unset xtics
unset ytics
unset key

set samples 100
set isosample 1000,1000
set xrange [0:1]
set yrange [0:1]
set palette defined (0 "white", 1 "blue")
set autoscale cbfix
unset colorbox

# sun
set object 1 circle at 0,1 size 0.25 fc rgb "yellow" fs solid 1.0 front
set object 2 circle at 0,1 size 0.25 lw 3 fs empty border lc rgb "orange" front

# head
set object 3 circle at 0.5, 0.5 size 0.06 fc rgb "white" fs solid 1.0 front
set object 4 circle at 0.5, 0.5 size 0.06 lw 3 fs empty border lc rgb "black" front

# textbox
set object 5 rect from 0.1, 0.6 to 0.9, 0.7 fc rgb "white" fs solid 1.0 front
set object 6 rect from 0.1, 0.6 to 0.9, 0.7 lw 3 fs empty border lc rgb "black" front

# text
set label "This was made in gnuplot" at 0.13, 0.65 front

# body
set arrow from 0.5, 0.44 to 0.5, 0.25 nohead lw 4 front

# arms
set arrow from 0.5005, 0.43 to 0.5505, 0.25 nohead lw 4 front
set arrow from 0.5, 0.43 to 0.45, 0.25 nohead lw 4 front

# legs
set arrow from 0.5, 0.25 to 0.475, 0.095 nohead lw 4 front
set arrow from 0.5005, 0.25 to 0.5255, 0.095 nohead lw 4 front

plot '++' using 1:2:2 with image, \
     0.1*sin(pi*x) w filledcu linecolor rgb "green", \
     0.1*sin(pi*x) w l lw 3 lc rgb "dark-green"
