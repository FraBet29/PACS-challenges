
#include "ZeroSolver.hpp"
#include <cmath>



#include "SolverFactory.hpp"





int main(){
    const func_t f([](double x){ return 0.5 - std::exp(x*M_PI); });

    double a=-1,b=1;

    auto newton_ptr= SolverFactory<SolverType::QuasiNewton>(f,a,b);
    auto newton_result=newton_ptr->solve();

    auto secant_ptr= SolverFactory<SolverType::Secant>(f,a,b);
    auto secant_result=secant_ptr->solve();

    auto bisection_ptr= SolverFactory<SolverType::Bisection>(f,a,b);
    auto bisection_result=bisection_ptr->solve();

    std::cout<<newton_result.solution<<std::endl;
    std::cout<<secant_result.solution<<std::endl;
    std::cout<<bisection_result.solution<<std::endl;




    return 0;
}