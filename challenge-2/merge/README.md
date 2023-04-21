# Hierarchy of solvers to find the approximated zero of a function

Team: Francesca Bettinelli, Massimo Rizzuto

## Project description

In ```ZeroSolver.hpp```, we define an abstract class ```SolverBase``` and the derived classes ```QuasiNewton```, ```Bisection```, ```Secant```, and ```Brent``` that override the pure virtual method ```solve``` by providing the implementation of the corresponding method.

All the types used by the solvers are defined in the type trait ```SolverTraits``` in ```SolverTraits.hpp```.

Every solver inherits from the base class the following members:
- The function of which the user wants to find the approximated zero
- The interval in which the user expects to find the zero
- A struct ```m_options``` containing the parameters of the chosen method (tolerance, absolute tolerance, and maximum number of iterations)  
- A struct ```m_result``` containing the approximated zero, the convergence status and the number of iterations found after running the ```solve``` method

Note that, with the current implementation, some solvers do not require all the options in ```m_options```; however, these parameters are quite generic for iterative algorithms, so we decided to declare them in the base class. 

The base class also provides some getters and setters for the methods options and a method to print the result. Finally, it provides the (protected) method ```bracketInterval``` that, given a function and starting point, tries to compute an interval bracketing the zero. This method is used in bisection and Brent, both in the constructor and in the ```solve``` method, to perform a preliminary check on the interval provided by the user; if this interval is not guaranteed to bracket the zero, the methods prints a warning and suggests a better interval. The user is free to change it (by using setters) or leave it unchanged knowing that the method may not converge. This check is not needed for Quasi-Newton and secant, where the initial interval is used as a starting point but does not affect the convergence status.

The template function ```SolverFactory``` in ```SolverFactory.hpp``` allows the user to create a pointer to a solver object by passing the chosen method as type.

## Compile and execute

Compile: ```make```

Execute: ```./main```

Output: the results of some tests defined in the main are printed in the terminal

Remove the object files: ```make clean```

Remove the object files and the executable: ```make distclean```
