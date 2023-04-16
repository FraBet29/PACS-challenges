#include <iostream>
#include <functional>
#include <type_traits>
#include <string>
#include <memory>

#include "SolverTraits.hpp"
#include "Derivatives.hpp"


#ifndef ZERO_SOLVER
#define ZERO_SOLVER


class SolverBase{

protected:
    func_t m_f;


    OptionsType options;


public:

    virtual ResultType solve () = 0;

    //SolverBase(func_t f, double a, double b): m_f(f),m_a(a),m_b(b) {}

    void set_interval(double a, double b){
        options.a=a;
        options.b=b;

    }

};


////////////////////////////////////////////////////////////////////////////

class Bisection: public SolverBase {

public:

    ResultType solve () override ;

    Bisection() = default;

    Bisection(func_t f, double a, double b,double tol=1.e-5) {
        m_f=f;
        options.a=a;
        options.b=b;
        options.tol=tol;
    }

};



////////////////////////////////////////////////////////////////////////////


class QuasiNewton: public SolverBase {

private:
    func_t m_Df;
    
public:

    ResultType solve () override;

    QuasiNewton(func_t f, double a, double b,double tol=1.e-5,double tola=1.e-10,double maxIt=150,double h=1e-4){
        m_f=f;
        options.a=a;
        options.b=b;
        options.tol=tol;
        options.tola=tola;
        options.max_iter=maxIt;
        options.h=h;

        m_Df = apsc::makeCenteredDerivative<1>(m_f, options.h);
    }

};

////////////////////////////////////////////////////////////////////////////


class Secant: public SolverBase {

public:

    ResultType solve () override ;

    Secant(func_t f, double a, double b,double tol=1.e-5,double tola=1.e-10,double maxIt=150){
        m_f=f;
        options.a=a;
        options.b=b;
        options.tol=tol;
        options.tola=tola;
        maxIt=options.max_iter;
    }

};


#endif //ZERO_SOLVER




