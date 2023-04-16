#ifndef NEWTONTRAITS_HPP
#define NEWTONTRAITS_HPP

#include <functional>

enum class SolverType : unsigned int
{
  QuasiNewton = 0,
  Bisection   = 1,
  Secant = 2
};

using func_t = std::function<double(double)>;

struct OptionsType
{
  double a=0;

  double b=1;

  double tol = 1e-6;

  double tola = 1e-8;

  double h = 1e-5;

  /// Max. number of iterations.
  unsigned int max_iter = 150;
};

/// Output results.
struct ResultType
{
  /// Solution.
  double solution;

  /// Iteration counter.
  unsigned int iteration = 0;

  /// Convergence flag. True if convergence is reached
  bool converged = false;
};

#endif /* NEWTONMETHODSSUPPORT_HPP */
