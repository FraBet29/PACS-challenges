#include <iostream>
#include <functional>
#include <type_traits>
#include <string>
#include <memory>

#include "SolverTraits.hpp"
#include "Derivatives.hpp"


#ifndef ZEROSOLVER_HPP
#define ZEROSOLVER_HPP


class SolverBase: public SolverTraits {

protected:
    FunctionType m_f;
    double m_a;
    double m_b;
    OptionsType m_options;
    ResultType m_result;

public:
    SolverBase(FunctionType f, double a, double b): m_f(f), m_a(a), m_b(b) {}

    virtual ResultType solve () = 0;

    void set_interval(double a, double b) {
        m_a = a;
        m_b = b;
    }

    ResultType get_result() const {
        return m_result;
    }

    void print_result() const {
        std::cout << "Zero: " << m_result.solution << std::endl;
	    std::cout << "Convergence status: " << (m_result.converged ? "converged" : "not converged") << std::endl;
	    std::cout << "Number of iterations: " << m_result.iteration << std::endl;
        std::cout << std::endl;
    }

};


////////////////////////////////////////////////////////////////////////////

class Bisection: public SolverBase {

public:

    ResultType solve() override;

    Bisection(FunctionType f, double a, double b, double tol=1.e-5, unsigned int maxIt=150): SolverBase(f, a, b) {
        m_options.tol = tol;
        m_options.max_iter = maxIt;
    }

};


////////////////////////////////////////////////////////////////////////////

class QuasiNewton: public SolverBase {

private:
    FunctionType m_Df;
    
public:

    ResultType solve() override;

    QuasiNewton(FunctionType f, double a, double b, double tol=1.e-5, double tola=1.e-10, unsigned int maxIt=150, double h=1e-4): 
    SolverBase(f, a, b) {
        m_options.tol = tol;
        m_options.tola = tola;
        m_options.max_iter = maxIt;
        m_options.h = h;

        m_Df = apsc::makeCenteredDerivative<1>(m_f, m_options.h);
    }

};


////////////////////////////////////////////////////////////////////////////

class Secant: public SolverBase {

public:

    ResultType solve() override;

    Secant(FunctionType f, double a, double b, double tol=1.e-4, double tola=1.e-10, unsigned int maxIt=150): 
    SolverBase(f, a, b) {
        m_options.tol = tol;
        m_options.tola = tola;
        m_options.max_iter = maxIt;
    }

};


#endif //ZEROSOLVER_HPP




