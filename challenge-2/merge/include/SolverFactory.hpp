#ifndef SOLVERFACTORY_HPP
#define SOLVERFACTORY_HPP

#include <memory>
#include <utility>

#include "ZeroSolver.hpp"

// This factory returns a unique_ptr to an object whose type is passed as template parameter

template<SolverTraits::SolverType type, class... Args>
std::unique_ptr<SolverBase> SolverFactory(Args&&... args) {

    if constexpr(type == SolverTraits::SolverType::QuasiNewton)
        return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);

    else if constexpr(type == SolverTraits::SolverType::Bisection)
        return std::make_unique<Bisection>(std::forward<Args>(args)...);
                    
    else if constexpr(type == SolverTraits::SolverType::Secant)
        return std::make_unique<Secant>(std::forward<Args>(args)...);

    else if constexpr(type == SolverTraits::SolverType::Brent)
        return std::make_unique<Brent>(std::forward<Args>(args)...);
        
    else
        return nullptr;

}

#endif /* SOLVERFACTORY_HPP */