#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <functional>
#include <memory>
#include "Derivatives.hpp"

struct SolverTraits {
	using ResultType = double;
	struct FullResultType {
		ResultType zero; // result
		bool conv_status; // convergence status
		unsigned int n_it; // number of iterations
	};
	using FunctionType = std::function<ResultType (ResultType)>;
	enum class SolverName{QuasiNewton, Bisection, Secant};
};

class SolverBase: public SolverTraits {

public:
	SolverBase(FunctionType f): m_f(f) {};
	virtual FullResultType solve() = 0;
	FullResultType m_result;

protected:
	const FunctionType m_f;
	void printFullResultCommon() const;

};

class QuasiNewton: public SolverBase {

public:
	QuasiNewton(FunctionType f, ResultType a): SolverBase(f), m_df(apsc::makeCenteredDerivative<1>(f, 1e-10)), m_a(a) {};
	FullResultType solve() override;
	void printFullResult() const;

private:
	const FunctionType m_df;
	const ResultType m_a;
	const double m_tol = 1.e-4;
    const double m_tola = 1.e-10;
	const unsigned int m_max_it = 150;

};

class Bisection: public SolverBase {

public:
	Bisection(FunctionType f, ResultType a, ResultType b): SolverBase(f), m_a(a), m_b(b) {};
	FullResultType solve() override;
	void printFullResult() const;

private:
	const ResultType m_a;
	const ResultType m_b;
	const double m_tol = 1.e-5;
	const unsigned int m_max_it = 150;

};

class Secant: public SolverBase {

public:
	Secant(FunctionType f, ResultType a, ResultType b): SolverBase(f), m_a(a), m_b(b) {};
	FullResultType solve() override;
	void printFullResult() const;

private:
	const ResultType m_a;
	const ResultType m_b;
	const double m_tol = 1.e-4;
	const double m_tola = 1.e-10;
	const unsigned int m_max_it = 150;

};

template<class... Args>
std::unique_ptr<SolverBase> SolverFactory(SolverTraits::SolverName s, Args&&... args) {
	switch(s) {
		case SolverTraits::SolverName::QuasiNewton: return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);
		case SolverTraits::SolverName::Bisection: return std::make_unique<Bisection>(std::forward<Args>(args)...);
		case SolverTraits::SolverName::Secant: return std::make_unique<Secant>(std::forward<Args>(args)...);
		default: return std::make_unique<SolverBase>();
	}
}

#endif // SOLVER_HPP