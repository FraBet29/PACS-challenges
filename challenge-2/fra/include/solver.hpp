#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <functional>
#include <memory>
#include <iostream>
#include "Derivatives.hpp"

struct SolverTraits {
	using ResultType = double;
	struct FullResultType {
		ResultType zero; // result
		bool conv_status; // convergence status
		unsigned int n_it; // number of iterations
	};
	using FunctionType = std::function<ResultType (ResultType)>;
	enum SolverName{QuasiNewton, Bisection, Secant};
};

class SolverBase: public SolverTraits {

public:
	SolverBase(FunctionType f): m_f(f) {};
	virtual FullResultType solve() = 0;
	virtual void printFullResult() const = 0;
	FullResultType m_result;

protected:
	const FunctionType m_f;

};

class QuasiNewton: public SolverBase {

public:
	QuasiNewton(FunctionType f, ResultType a): SolverBase(f), m_df(apsc::makeCenteredDerivative<1>(f, 1e-10)), m_a(a) { std::cout << "Quasi-Newton object created" << std::endl; };
	FullResultType solve() override;
	void printFullResult() const override;

private:
	const FunctionType m_df;
	const ResultType m_a;
	const double m_tol = 1.e-4;
    const double m_tola = 1.e-10;
	const unsigned int m_max_it = 150;

};

class Bisection: public SolverBase {

public:
	Bisection(FunctionType f, ResultType a, ResultType b): SolverBase(f), m_a(a), m_b(b) { std::cout << "Bisection object created" << std::endl; };
	FullResultType solve() override;
	void printFullResult() const override;

private:
	const ResultType m_a;
	const ResultType m_b;
	const double m_tol = 1.e-5;
	const unsigned int m_max_it = 150;

};

class Secant: public SolverBase {

public:
	Secant(FunctionType f, ResultType a, ResultType b): SolverBase(f), m_a(a), m_b(b) { std::cout << "Secant object created" << std::endl; };
	FullResultType solve() override;
	void printFullResult() const override;

private:
	const ResultType m_a;
	const ResultType m_b;
	const double m_tol = 1.e-4;
	const double m_tola = 1.e-10;
	const unsigned int m_max_it = 150;

};

/*
template<class... Args>
std::unique_ptr<SolverBase> SolverFactory(SolverTraits::SolverName s, Args&&... args) {
	switch(s) {
		case SolverTraits::SolverName::QuasiNewton: return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);
		case SolverTraits::SolverName::Bisection: return std::make_unique<Bisection>(std::forward<Args>(args)...);
		case SolverTraits::SolverName::Secant: return std::make_unique<Secant>(std::forward<Args>(args)...);
		//default: return std::make_unique<SolverBase>(std::forward<Args>(args)...);
	}
}
*/

class SolverFactory {

public:
	template<typename... Args>
	std::unique_ptr<SolverBase> operator()(SolverTraits::SolverName s, Args&&... args) {
		if(s == SolverTraits::SolverName::QuasiNewton)
			return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);
		//else if(s == SolverTraits::SolverName::Bisection)
		//	return std::make_unique<Bisection>(std::forward<Args>(args)...);
		//else if(s == SolverTraits::SolverName::Secant)
		//	return std::make_unique<Secant>(std::forward<Args>(args)...);
		//else
		//	return std::make_unique<SolverBase>(std::forward<Args>(args)...);
}

};

#endif // SOLVER_HPP



/*
template<typename T, typename... Args>
std::unique_ptr<T> create(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

int main() {
    // Creazione delle istanze usando il factory
    auto qn = create<QuasiNewton>();
    auto sec = create<Secant>(1.0, 0.5);
    auto bis = create<Bisection>();
}
*/