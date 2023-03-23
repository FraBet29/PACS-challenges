#!/bin/bash

rm -f plots/CAUCHY_SOL.jpg
rm -f plots/ERROR_CONV_RATE.jpg
gnuplot>> load "plots/graph_cauchy.plt"
gnuplot>> load "plots/error_cauchy.plt"
rm -f load