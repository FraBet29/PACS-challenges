#ifndef SOLVERTRAITS_HPP
#define SOLVERTRAITS_HPP

#include <functional>
#include <limits>

struct SolverTraits {

enum class SolverType
{
    QuasiNewton,
    Bisection,
    Secant
};

using FunctionType = std::function<double(double)>;

struct OptionsType
{
    double tol;

    double tola; // Secant, Newton

    double h; // Netwon

    /// Max. number of iterations.
    unsigned int max_iter;
};

/// Output results.
struct ResultType
{
    /// Solution.
    double solution = std::numeric_limits<double>::quiet_NaN();

    /// Iteration counter.
    unsigned int iteration = 0;

    /// Convergence flag. True if convergence is reached
    bool converged = false;
};

};

#endif /* SOLVERTRAITS_HPP */
