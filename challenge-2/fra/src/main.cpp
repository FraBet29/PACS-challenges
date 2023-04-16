#include "../include/solver.hpp"
#include <iostream>
#include <cmath>
#include <numbers>

struct Data {
	SolverTraits::SolverName solver_name;
	SolverTraits::FunctionType f;
	SolverTraits::ResultType a;
	SolverTraits::ResultType b;
};

int main() {

	Data data{
		SolverTraits::SolverName::QuasiNewton, // solver name
		[](SolverTraits::ResultType x){ return 0.5 - std::exp(std::numbers::pi * x); }, // function
		-1., // 1st end of the initial interval
		1., // 2nd end of the initial interval (needed only for Bisection and Secant)
	};

	/*
	auto qn = SolverFactory(SolverTraits::SolverName::QuasiNewton, data.f, data.a); // the derivative is computed automatically by the solver
	auto bis = SolverFactory(SolverTraits::SolverName::Bisection, data.f, data.a, data.b);
	auto sec = SolverFactory(SolverTraits::SolverName::Secant, data.f, data.a, data.b);

	qn->solve();
	bis->solve();
	sec->solve();

	std::cout << "Zero exact: " << - std::log(2) / std::numbers::pi << std::endl;
	std::cout << std::endl;

	qn->printFullResult();
	bis->printFullResult();
	sec->printFullResult();
	*/

	auto qn = QuasiNewton(data.f, data.a); // the derivative is computed automatically by the solver
	auto bis = Bisection(data.f, data.a, data.b);
	auto sec = Secant(data.f, data.a, data.b);

	qn.solve();
	bis.solve();
	sec.solve();

	std::cout << "Zero exact: " << - std::log(2) / std::numbers::pi << std::endl;
	std::cout << std::endl;

	qn.printFullResult();
	bis.printFullResult();
	sec.printFullResult();

	return 0;
}