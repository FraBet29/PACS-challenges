#include "../include/cauchySolver.hpp"
#include <cmath>
#include <iostream>
#include <fstream>

// Write the solution to a .txt file formatted for gnuplot
void write_solution(type_v hh, type_v sol) {

    std::ofstream fw("result.txt", std::ofstream::out);

    // Check if file was successfully opened for writing
    if (fw.is_open()) {

		// Store array contents to text file

		fw << "# n\t" << "t_n\t" << "u_n\n";

		for (size_t i = 0; i < hh.size(); i++) 
			fw << i+1 << "\t" << hh[i] << "\t" << sol[i] << "\n";
		
		fw.close();
    }
    else std::cerr << "Problem with opening file." << std::endl;
    
}

// Write the error to a .txt file formatted for gnuplot
void write_error(type_v hh, type_v err) {

    std::ofstream fw("error_conv.txt", std::ofstream::out);

    // Check if file was successfully opened for writing
    if (fw.is_open()) {

		// Store array contents to text file

		fw << "# t_n\t\t" << "err_inf\n";

		for (size_t i = 0; i < hh.size(); i++) 
			fw << hh[i] << "\t\t" << err[i] << "\n";
		
		fw.close();
    }
    else std::cerr << "Problem with opening file." << std::endl;

}

int main(int argc, char** argv) {

	const type_f f([](double t, double y){ return - t * std::exp(-y); }); // force, type_f is defined in cauchySolver.hpp (function wrapper)
	const type_u u_ex([](double t){ return std::log(1 - 0.5*t*t); }); // exact solution, type_u is defined in cauchySolver.hpp (function wrapper)
	const double y0 = 0; // initial condition
	const double T = 1; // final time
	const double N = 100; // number of timesteps
	const double theta = 0.5; // parameter of the theta method (0.5 = Crank-Nicolson)
	const int zero_method = Newton; // zero_method is defined in cauchySolver.hpp (enum), available methods: secant, Newton

	const bool conv_check = true; // true to perform a convergence test, false otherwise
	const unsigned int n_ref = 10; // number of refinements for the convergence test

	// Initialization of the solver
	cauchySolver solver(f, u_ex, y0, T, N, theta, zero_method);

	// Execution of the solver
	auto [tn, un] = solver.solve();
	write_solution(tn, un);

	// Convergence check
	if(conv_check) {
		auto [h, eh] = solver.convergenceCheck(n_ref);
		write_error(h, eh);
	}

	return 0;
}