/*
 * Code adapted from basicZeroFun.hpp in Examples/LinearAlgebraUtil
 * Available methods: secant, Newton
 */

#ifndef BASICZEROFUN_HPP
#define BASICZEROFUN_HPP

#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>

namespace apsc {
/*!
 * Computes the zero of a scalar function with the secant method.
 * 
 * @tparam Function
 * 
 * @param f Function
 * @param a First point for computing derivatives
 * @param b Second point for computing derivatives
 * @param tol Relative tolerance
 * @param tola Absolute tolerance
 * @param max_it Maximum number of iterations
 * 
 * @return The approximation of the zero of f and the convergence status (false if not converging)
 */
template <class Function>
std::tuple<double, bool> secant(Function const &f, double a, double b, double tol = 1.e-4,
                                double tola = 1.e-10, unsigned int max_it = 150) {
    double ya = f(a);
    double res = std::abs(ya);
    double c{a};
    unsigned int it{0u};
    double check = tol * res + tola;
    bool go_on = res > check;
    
    while(go_on && it < max_it) {
        ++it;
        double yb = f(b);
        c = a - ya * (b - a) / (yb - ya);
        double yc = f(c);
        res = std::abs(yc);
        go_on = res > check;
        ya = yc;
        a = c;
    }

    return std::make_tuple(c, (it < max_it));
}
/*!
 * Computes the zero of a scalar function with the Newton method. The function must be differentiable.
 * 
 * @tparam Function
 * 
 * @param f Function
 * @param df Derivative of the function
 * @param a Initial point
 * @param tol Relative tolerance
 * @param tola Rbsolute tolerance
 * @param max_it Maximum number of iterations
 * 
 * @return The approximation of the zero of f and the convergence status (false if not converging)
 */
template <class Function, class Dfunction>
std::tuple<double, bool> Newton(Function const &f, Dfunction const & df, double a, double tol = 1.e-4,
                                double tola = 1.e-10, unsigned int max_it = 150) {
    double ya = f(a);
    double res = std::abs(ya);
    unsigned int it{0u};
    double check = tol * res + tola;
    bool go_on = res > check;
    
    while(go_on && it < max_it) {
      ++it;
      a += - ya/df(a);
      ya = f(a);
      res = std::abs(ya);
      go_on = res > check;
    }

    return std::make_tuple(a, (it < max_it));
}
} /* namespace apsc */

#endif /* BASICZEROFUN_HPP */
