#ifndef ZEROSOLVER_HPP
#define ZEROSOLVER_HPP

#include <iostream>
#include <functional>

#include "SolverTraits.hpp"
#include "Derivatives.hpp"

class SolverBase: public SolverTraits {

protected:

    void bracketInterval(SolverTraits::FunctionType const &f, double x1, double h=0.01, unsigned int maxIter=200);

    FunctionType m_f; // function
    double m_a; // 1st end of the initial interval
    double m_b; // 2nd end of the initial interval (needed for Bisection and Secant only)
    OptionsType m_options; // struct containing the parameters of the chosen method
    ResultType m_result; // struct containing the approximated zero, the convergence status and the number of iterations
    
public:

    SolverBase(FunctionType f, double a, double b): m_f(f), m_a(a), m_b(b) {} // abstract constructor

    virtual ResultType solve() = 0; // pure virtual function 

    // Getters and setters for the method options
    void set_interval(double a, double b) {
        m_a = a;
        m_b = b;
    }

    double & tol() { return m_options.tol; }
    double & tola() { return m_options.tola; }
    unsigned int & max_iter() { return m_options.max_iter; }

    ResultType get_result() const { return m_result; }

    void print_result() const {
        std::cout << "Solution (approximated zero): " << m_result.solution << std::endl;
	    std::cout << "Convergence status: " << (m_result.converged ? "converged" : "not converged") << std::endl;
	    std::cout << "Number of iterations: " << m_result.iteration << std::endl;
        std::cout << std::endl;
    }

};

////////////////////////////////////////////////////////////////////////////

class Bisection: public SolverBase {

public:

    Bisection(FunctionType f, double a, double b, double tol=1.e-5, unsigned int max_iter=150): SolverBase(f, a, b) {
        bracketInterval(f, a);
        m_options.tol = tol;
        m_options.max_iter = max_iter;
    }

    ResultType solve() override;

};

////////////////////////////////////////////////////////////////////////////

class QuasiNewton: public SolverBase {

private:
    FunctionType m_Df;
    
public:

    QuasiNewton(FunctionType f, double a, double b, double tol=1.e-5, double tola=1.e-10, unsigned int max_iter=150): 
    SolverBase(f, a, b) {
        m_options.tol = tol;
        m_options.tola = tola;
        m_options.max_iter = max_iter;

        m_Df = apsc::makeCenteredDerivative<1>(m_f, tol);
    }

    ResultType solve() override;

};

////////////////////////////////////////////////////////////////////////////

class Secant: public SolverBase {

public:

    Secant(FunctionType f, double a, double b, double tol=1.e-4, double tola=1.e-10, unsigned int max_iter=150): 
    SolverBase(f, a, b) {
        m_options.tol = tol;
        m_options.tola = tola;
        m_options.max_iter = max_iter;
    }

    ResultType solve() override;

};

////////////////////////////////////////////////////////////////////////////

class Brent: public SolverBase {

public:

    Brent(FunctionType f, double a, double b, double tol=1.e-5, unsigned int max_iter=200): SolverBase(f, a, b) {
        bracketInterval(f, a);
        m_options.tol = tol;
        m_options.max_iter = max_iter;
    }

    ResultType solve() override;

};

#endif /* ZEROSOLVER_HPP */