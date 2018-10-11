set term png size 1000,1000
set output 'pm3d.png'
set pm3d map corners2color c1
set key outside
set size square
set pm3d map
set cntrparam levels auto 7
set cbtics 2000
set zrange [0:1000]
set palette rgbformulae 7,5,15
set samples 10
set isosamples 10
splot 'out.txt' notitle
