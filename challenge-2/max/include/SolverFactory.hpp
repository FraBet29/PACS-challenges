#include "ZeroSolver.hpp"


#ifndef SOLVER_FACTORY
#define SOLVER_FACTORY



template<SolverType type, class ... Args>
    std::unique_ptr<SolverBase> SolverFactory(Args &&... args){


        if constexpr(type == SolverType::QuasiNewton)
            return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);

        else if constexpr(type == SolverType::Bisection)
            return std::make_unique<Bisection>(std::forward<Args>(args)...);
                    
        else if constexpr(type == SolverType::Secant)
            return std::make_unique<Secant>(std::forward<Args>(args)...); 
            

    }

    /*


struct SolverFactory {
    template<typename... Args>
    std::unique_ptr<SolverBase> operator()(const std::string& id, Args&&... args) const {
        if (id == "QuasiNewton") 
            return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);
          else if (id == "Bisection") 
            return std::make_unique<Bisection>(std::forward<Args>(args)...);
          else if(id=="Secant")
            return std::make_unique<Secant>(std::forward<Args>(args)...);
          else
            return nullptr;
    }
};

*/


#endif //SOLVER_FACTORY