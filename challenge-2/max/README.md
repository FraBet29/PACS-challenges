# Build a hierarchy of solvers for f(x) = 0

Team: Francesca Bettinelli, Massimo Rizzuto

Compile: make

Execute: ./main

Remove the object files: make clean

Remove the object files and the executable: make distclean


The methods implemented are
- Bisection 
- QuasiNewton
- Secant 
- Brent Search


The files in include folder are:

- Derivatives.hpp : we use this to compute the centered derivative for the QuasiNewton method
- SolverFactory.hpp : it contains a template function which takes as template parameter the method type and returns a unique pointer to an element of a specified method class...
- ZeroSolver.hpp: it contains a basic pure abstract class and the methods classes inherited from the base class
- SolverTraits.hpp : we collected the options_type and result_type into a struct in order to have a more readable code.

NB: For Bisection and Brent search we used the method BracketInterval to ensure that the interval provided does contain effettively a zero.

In the main file we tried all the methods
