/*
 * Code adapted from basicZeroFun.hpp in Examples/LinearAlgebraUtil
 */

#include <iostream>

#include "../include/ZeroSolver.hpp"

/*!
 * This function tries to find an interval that brackets the zero of a function f. 
 * It does so by sampling the value of f at points generated starting from a given point.
 *
 * @param f Function
 * @param x1 Initial point
 * @param h Initial increment for the sampling
 * @param maxIter Maximum number of iterations
 */
void SolverBase::bracketInterval(SolverTraits::FunctionType const &f, double x1, double h, unsigned int maxIter) {

    constexpr double expandFactor = 1.5;
    h = std::abs(h);
    auto direction = 1.0;
    auto x2 = x1 + h;
    auto y1 = f(x1);
    auto y2 = f(x2);
    unsigned int iter = 0u;
    
    // Get initial decrement direction
    while((y1 * y2 > 0) && (iter < maxIter)) {
        ++iter;
        if(std::abs(y2) > std::abs(y1)) { // change direction
            std::swap(y1, y2);
            std::swap(x1, x2);
        }
        direction = (x2 > x1) ? 1.0 : -1.0;
        x1 = x2;
        y1 = y2;
        x2 += direction * h;
        y2 = f(x2);
        h *= expandFactor;
    }

    if ((iter < maxIter) && (m_a > x1 || m_b < x2)) {
        std::cout << "The provided interval may not include a zero. Try with: a = " << x1 << ", b = " << x2 << std::endl;
    }
}

SolverTraits::ResultType Bisection::solve() {

    // Check if the interval does include a zero
    bracketInterval(m_f, m_a);

    double a = m_a;
	double b = m_b;
	
	double ya = m_f(a);
    double yb = m_f(b);
    double delta = b - a;

    if(ya * yb >= 0) {
        std::cerr << "Function must change sign at the two end values." << std::endl;
        return m_result;
    }
    
    double yc{ya};
    double c{a};
	unsigned int it{0u};

    while(std::abs(delta) > 2 * m_options.tol && it < m_options.max_iter) {
		++it;
        c = (a + b) / 2.;
        yc = m_f(c);
        if(yc * ya < 0.0) {
            yb = yc;
            b = c;
        }
        else {
            ya = yc;
            a = c;
        }
        delta = b - a;
    }

	m_result.solution = (a + b) / 2.;
	m_result.converged = it < m_options.max_iter;
	m_result.iteration = it;

    return m_result;

}

SolverTraits::ResultType QuasiNewton::solve() {

    double a = m_a;
	
	double ya = m_f(a);
    double res = std::abs(ya);
    unsigned int it{0u};
    double check = m_options.tol * res + m_options.tola;
    bool go_on = res > check;
    
    while(go_on && it < m_options.max_iter) {
        ++it;
        a += - ya / m_Df(a);
        ya = m_f(a);
        res = std::abs(ya);
        go_on = res > check;
    }

	m_result.solution = a;
	m_result.converged = it < m_options.max_iter;
	m_result.iteration = it;

    return m_result;

}

SolverTraits::ResultType Secant::solve() {

    double a = m_a;
	double b = m_b;
	double c{a};

	double ya = m_f(a);
    double res = std::abs(ya);
    unsigned int it{0u};
    double check = m_options.tol * res + m_options.tola;
    bool go_on = res > check;
    
    while(go_on && it < m_options.max_iter) {
        ++it;
        double yb = m_f(b);
        c = a - ya * (b - a) / (yb - ya);
        double yc = m_f(c);
        res = std::abs(yc);
        go_on = res > check;
        ya = yc;
        a = c;
    }

	m_result.solution = c;
	m_result.converged = it < m_options.max_iter;
	m_result.iteration = it;

    return m_result;

}

SolverTraits::ResultType Brent::solve() {

    // Check if the interval does include a zero
    bracketInterval(m_f, m_a);

    double a = m_a;
	double b = m_b;

    auto ya = m_f(a);
    auto yb = m_f(b);
    
    // First check
    if((ya * yb) >= 0.0) {
        if(ya == 0.) {
            m_result = SolverTraits::ResultType{a, 0, true};
            return m_result;
        }
        else if(yb == 0.) {
            m_result = SolverTraits::ResultType{b, 0, true};
            return m_result;
        }
        else {
            m_result = SolverTraits::ResultType{a, 0, false};
            return m_result;
        }
    }

    if(std::abs(ya) < std::abs(yb)) {
        std::swap(a, b);
        std::swap(ya, yb);
    }

    auto c = a;
    auto d = c;
    auto yc = ya;
    bool mflag{true};
    auto s = b;
    auto ys = yb;
    unsigned iter{0u};
    
    do {
        ++iter;

        if(ya != yc and yb != yc) {
            auto yab = ya - yb;
            auto yac = ya - yc;
            auto ycb = yc - yb;
            // Inverse quadratic interpolation
            s = a * ya * yc / (yab * yac) + b * ya * yc / (yab * ycb) - c * ya * yb / (yac * ycb);
        }
        else {
            // Secant
            s = b - yb * (b - a) / (yb - ya);
        }

        if(((s - 3 * (a + b) / 4) * (s - b) >= 0) or // condition 1
        (mflag and (std::abs(s - b) >= 0.5 * std::abs(b - c))) or // condition 2
        (!mflag and (std::abs(s - b) >= 0.5 * std::abs(c - d))) or // condition 3
        (mflag and (std::abs(b - c) < m_options.tol)) or // condition 4
        (!mflag and (std::abs(c - d) < m_options.tol))) // condition 5
        {
            mflag = true;
            s = 0.5 * (a + b); // back to bisection step
        }
        else {
            mflag = false;
        }

        ys = m_f(s);
        d = c;
        c = b;
        yc = yb;

        if(ya * ys < 0) {
            b = s;
            yb = ys;
        }
        else {
            a = s;
            ya = ys;
        }

        if(std::abs(ya) < std::abs(yb)) {
            std::swap(a, b);
            std::swap(ya, yb);
        }
    }
    while(ys != 0. && std::abs(b - a) > m_options.tol && iter < m_options.max_iter);

    m_result.solution = s;
	m_result.converged = iter < m_options.max_iter;
	m_result.iteration = iter;

    return m_result;
}
