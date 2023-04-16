/*
 * Code adapted from basicZeroFun.hpp in Examples/LinearAlgebraUtil
 */

#include "../include/solver.hpp"
#include <iostream>
#include <string>

void SolverBase::printFullResultCommon() const {

	std::cout << "Zero: " << m_result.zero << std::endl;
	std::cout << "Convergence status: " << (m_result.conv_status ? "converged" : "not converged") << std::endl;
	std::cout << "Number of iterations: " << m_result.n_it << std::endl;
    std::cout << std::endl;
}

SolverTraits::FullResultType QuasiNewton::solve() {

	SolverTraits::ResultType a = m_a;
	
	double ya = m_f(a);
    double res = std::abs(ya);
    unsigned int it{0u};
    double check = m_tol * res + m_tola;
    bool go_on = res > check;
    
    while(go_on && it < m_max_it) {
      ++it;
      a += - ya / m_df(a);
      ya = m_f(a);
      res = std::abs(ya);
      go_on = res > check;
    }

	m_result.zero = a;
	m_result.conv_status = it < m_max_it;
	m_result.n_it = it;

    return m_result;
}

void QuasiNewton::printFullResult() const {

    std::cout << "--- Quasi-Newton ---" << std::endl;
    printFullResultCommon();
}

SolverTraits::FullResultType Bisection::solve() {

	SolverTraits::ResultType a = m_a;
	SolverTraits::ResultType b = m_b;
	
	double ya = m_f(a);
    double yb = m_f(b);
    double delta = b - a;

    if(ya * yb >= 0)
        std::cerr << "Function must change sign at the two end values." <<std::endl;
	
    double yc{ya};
    SolverTraits::ResultType c{a};
	unsigned int it{0u};

    while(std::abs(delta) > 2 * m_tol && it < m_max_it) {
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

	m_result.zero = (a + b) / 2.;
	m_result.conv_status = it < m_max_it;
	m_result.n_it = it;

    return m_result;
}

void Bisection::printFullResult() const {

    std::cout << "--- Bisection ---" << std::endl;
    printFullResultCommon();
}

SolverTraits::FullResultType Secant::solve() {

	SolverTraits::ResultType a = m_a;
	SolverTraits::ResultType b = m_b;
	SolverTraits::ResultType c{a};

	double ya = m_f(a);
    double res = std::abs(ya);
    unsigned int it{0u};
    double check = m_tol * res + m_tola;
    bool go_on = res > check;
    
    while(go_on && it < m_max_it) {
        ++it;
        double yb = m_f(b);
        c = a - ya * (b - a) / (yb - ya);
        double yc = m_f(c);
        res = std::abs(yc);
        go_on = res > check;
        ya = yc;
        a = c;
    }

	m_result.zero = c;
	m_result.conv_status = it < m_max_it;
	m_result.n_it = it;

    return m_result;
}

void Secant::printFullResult() const {

    std::cout << "--- Secant ---" << std::endl;
    printFullResultCommon();
}