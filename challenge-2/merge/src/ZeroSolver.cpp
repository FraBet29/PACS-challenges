/*
 * Code adapted from basicZeroFun.hpp in Examples/LinearAlgebraUtil
 */

#include "../include/ZeroSolver.hpp"

SolverTraits::ResultType Bisection::solve() {

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


