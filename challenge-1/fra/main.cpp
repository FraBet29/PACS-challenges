#include "cauchySolver.hpp"
#include <cmath>
#include <iostream>
#include <fstream>

double force(double t, double y) {
	return - t * std::exp(-y);
}

double solution(double t) {
	return std::log(1 - 0.5*t*t);
}

void writeVectorToFile(std::ofstream &file, std::vector<double> v) {
	for(std::size_t n = 0; n < v.size() - 1; ++n) {
		file << v[n] << ',';
	}
	file << v[v.size() - 1] << '\n';
}

int main(int argc, char** argv) {

	type_f f(force); // type_f is defined in cauchySolver.hpp (function wrapper)
	type_u u_ex(solution); // type_u is defined in cauchySolver.hpp (function wrapper)
	const double y0 = 0;
	const double T = 1;
	const double N = 100;
	const double theta = 0.5;
	const bool conv_check = true;
	const unsigned int n_ref = 10;
	int zero_method = Newton; // zero_method is defined in cauchySolver.hpp (enum). Available methods: secant, Newton

	cauchySolver solver(f, u_ex, y0, T, N, theta, zero_method);

	auto [tn, un] = solver.solve();

	// Writing output to file output.csv
	std::ofstream output("output.csv");
	writeVectorToFile(output, tn);
	writeVectorToFile(output, un);

	// Convergence check
	// Writing error to file error.csv
	if(conv_check) {
		auto [h, eh] = solver.convergenceCheck(n_ref);
		std::ofstream error("error.csv");
		writeVectorToFile(error, h);
		writeVectorToFile(error, eh);
	}

	return 0;
}

// IMPROVEMENTS:
// WRITE INPUT IN JSON FILE AND READ IT WITH MUPARSER (?)
// PLOT THE RESULT WITH GNUPLOT (?)

// NOTES
// The algorithm is sensible to the choice of the interval [a, b] used to find the zeros of F
// The algorithm is sensible to the tolerance of the method used to find the zeros of F
// The solution is not computed for the last timestep because it is not defined for implicit methods