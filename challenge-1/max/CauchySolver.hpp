#include <cmath>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include "basicZeroFun.hpp"
#include "Derivatives.hpp"

typedef enum{secant, newton} method; 


class CauchySolver{

private:

    size_t N; // number of steps

    double y0; // initial condition

    double T; // final time

    std::function<double(double ,double )> f; // function f

    double theta = 0.5;

    method met;




public:

    // Constructor
    CauchySolver(size_t n_steps, double init_cond, double final_time,std::function<double(double,double)> force,double th,method met):
        N(n_steps), y0(init_cond), T(final_time),f(force), theta(th),met(met) {};


    // solver

    std::pair<std::vector<double>, std::vector<double>> solver();

    // rate of convergence -> pair < h, error > N= 2 ^1 - 2^K

    std::pair<std::vector<double>,std::vector<double>> conv_rate(unsigned int,std::function<double(double)>);

    void set_Nsteps(unsigned nsteps){ N = nsteps;};


};