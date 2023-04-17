#ifndef SOLVERTRAITS_HPP
#define SOLVERTRAITS_HPP

#include <functional>
#include <limits>

struct SolverTraits {

// Available solvers
enum class SolverType
{
    QuasiNewton,
    Bisection,
    Secant
};

using FunctionType = std::function<double (double)>;

// Parameters passed to the solvers
struct OptionsType
{
    // Tolerance
    double tol;

    // Absolute tolerance (needed for Secant and Newton only)
    double tola; 

    // Discretization step (needed for Netwon only)
    double h;

    // Maximum number of iterations
    unsigned int max_iter;
};

// Output results
struct ResultType
{
    // Solution (approximated zero)
    double solution = std::numeric_limits<double>::quiet_NaN();

    // Number of iterations
    unsigned int iteration = 0;

    // Convergence status (true if convergence is reached)
    bool converged = false;
};

};

#endif /* SOLVERTRAITS_HPP */