#include "cauchySolver.hpp"
#include "basicZeroFun.hpp"
#include "Derivatives.hpp"
#include <iostream>

/*!
 * Computes the approximated solution of the Cauchy problem with the theta method.
 *  
 * @return The time instants tn and the approximated solution un
 */
std::array<type_v, 2> cauchySolver::solve() {

	const double h = m_T / m_N; // timestep size

	// Computation of time instants
	for(unsigned int n = 1; n < m_N; ++n) {
		m_tn[n] = m_tn[n-1] + h;
	}

	// Initialization of the approximated solution
	m_un[0] = m_y0;

	for(unsigned int n = 0; n < m_N - 1; ++n) {
		
		// Definition of the functional 
		std::function<double (double)> F([this, h, n](double x){ return x - h * (m_theta * m_f(m_tn[n+1], x) + (1 - m_theta) * m_f(m_tn[n], m_un[n])) - m_un[n]; });

		double a = - 1;

		if(m_zero_fun == secant) {
			double b = 1;
			auto [sol, converged] = apsc::secant(F, a, b, 1.e-10, 1.e-10, 1000);
			if(!converged) {
				std::cerr << "The algorithm has not converged at time " << m_tn[n] << ". Execution stopped." << std::endl;
				break;
			}
			m_un[n+1] = sol;
		}
		else if(m_zero_fun == Newton) {
			auto dF = apsc::makeCenteredDerivative<1>(F, 1e-4);
			auto [sol, converged] = apsc::Newton(F, dF, a, 1.e-10, 1.e-10, 1000);
			if(!converged) {
				std::cerr << "The algorithm has not converged at time " << m_tn[n] << ". Execution stopped." << std::endl;
				break;
			}
			m_un[n+1] = sol;
		}
		else {
			std::cerr << "Invalid zero method name. Execution stopped." << std::endl;
			break;
		}
	}

	return std::array<type_v, 2> {m_tn, m_un};
}

double cauchySolver::computeInfError() {

	double err{0.0};

	for(std::size_t n = 1; n < m_N - 1; ++n) {
		err = std::max(err, std::abs(m_un[n] - m_u_ex(m_tn[n])));
	}

	return err;
}

/*!
 * Checks the order of convergence of the method used to solve the Cauchy problem.
 *  
 * @param n_ref Number of refinements
 * 
 * @return The timestep sizes h and the infinity norm of the errors eh
 */
std::array<type_v, 2> cauchySolver::convergenceCheck(unsigned int n_ref) {

	type_v N(n_ref); // number of timesteps
	type_v h(n_ref); // timestep sizes
	type_v eh(n_ref); // errors

	N[0] = m_N;
	h[0] = m_T / m_N;

	for(unsigned int i = 1; i < n_ref; ++i) {
		N[i] = N[i-1] * 2;
		h[i] = h[i-1] / 2;
	}

	for(unsigned int i = 0; i < n_ref; ++i) {
		cauchySolver solver(m_f, m_u_ex, m_y0, m_T, N[i], m_theta, m_zero_fun);
		auto [tn, un] = solver.solve();
		eh[i] = solver.computeInfError();
	}

	return std::array<type_v, 2> {h, eh};
}