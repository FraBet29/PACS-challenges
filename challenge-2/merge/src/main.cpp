#include "../include/ZeroSolver.hpp"
#include "../include/SolverFactory.hpp"
#include <iostream>
#include <cmath>
#include <numbers>

struct Data {
	SolverTraits::FunctionType f;
	double a;
	double b;
};

int main() {

	// Set the input data for the solver
	Data data{
		[](double x){ return 0.5 - std::exp(std::numbers::pi * x); }, // function
		-1., // 1st end of the initial interval
		1., // 2nd end of the initial interval (needed for Bisection and Secant only)
	};

	// QuasiNewton applied to the provided problem
	auto newton_ptr = SolverFactory<SolverTraits::SolverType::QuasiNewton>(data.f, data.a, data.b);
	newton_ptr->solve();
	std::cout << "Quasi-Newton" << std::endl;
	newton_ptr->print_result();

	// Secant applied to the provided problem
	auto secant_ptr = SolverFactory<SolverTraits::SolverType::Secant>(data.f, data.a, data.b);
	secant_ptr->solve();
	std::cout << "Secant" << std::endl;
	secant_ptr->print_result();

	// Bisection applied to the provided problem
	auto bisection_ptr = SolverFactory<SolverTraits::SolverType::Bisection>(data.f, data.a, data.b);
	bisection_ptr->solve();
	std::cout << "Bisection" << std::endl;
	bisection_ptr->print_result();

	// Brent search applied to the provided problem
	auto brent_ptr = SolverFactory<SolverTraits::SolverType::Brent>(data.f, data.a, data.b);
	brent_ptr->solve();
	std::cout << "Brent" << std::endl;
	brent_ptr->print_result();

	// Brent search applied to the provided problem, we changed tolerance
	brent_ptr->tol() = 1.e-7;
	brent_ptr->solve();
	std::cout << "Brent" << std::endl;
	brent_ptr->print_result();

	// Brent search applied to the provided problem, we changed the interval so that it does not contain the zero
	brent_ptr->set_interval(0., 1.);
	brent_ptr->solve();
	std::cout << "Brent" << std::endl;
	brent_ptr->print_result();


	// Print the exact solution (It can be computed analitically)
	std::cout << "Exact zero: " << - std::log(2) / std::numbers::pi << std::endl;
	std::cout << std::endl;

	return 0;
}