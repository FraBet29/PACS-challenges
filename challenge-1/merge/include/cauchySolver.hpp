#ifndef CAUCHYSOLVER_HPP
#define CAUCHYSOLVER_HPP

#include <vector>
#include <array>
#include <functional>

// Vector type
using type_v = std::vector<double>;

// Function wrapper for a function of t and y(t)
using type_f = std::function<double (double, double)>;

// Function wrapper for a function of t
using type_u = std::function<double (double)>;

// Available methods to find the zeros of a function
enum zero_method {secant, Newton};

class cauchySolver {

public:
	cauchySolver(type_f f, type_u u_ex, double y0, double T, unsigned int N, double theta, int zero_fun):
		m_f(f), m_u_ex(u_ex), m_y0(y0), m_T(T), m_N(N), m_theta(theta), m_zero_fun(zero_fun) {
			m_tn.resize(m_N);
			m_un.resize(m_N);
		};
	std::array<type_v, 2> solve();
	std::array<type_v, 2> convergenceCheck(unsigned int n_ref) const;

private:
	const type_f m_f; // force
	const type_u m_u_ex; // exact solution
	const double m_y0; // initial condition
	const double m_T; // final time
	const unsigned int m_N; // number of timesteps
	const double m_theta; // parameter of the theta method
	const int m_zero_fun; // method used to find the zeros of the function
	type_v m_tn; // time instants
	type_v m_un; // approximated solution
	double computeInfError() const; // method to compute the infinity norm of the error

};

#endif /* CAUCHYSOLVER_HPP */