#include "CauchySolver.hpp"


double compute_inf_error(std::vector<double> v1,std::vector<double> v2){
    double max=0.;
    
    if(v1.size()==v2.size()){
        for (size_t i=0;i<v1.size();i++)
            max=std::max(max,std::abs(v1[i]-v2[i]));
        return max;
    }
    else {
        std::cerr<<"Sizes are not equal"<<std::endl;
        return -1;
    }
}

std::pair<std::vector<double>, std::vector<double>> CauchySolver::solver(){

        double h=T/N;

        std::vector<double> u(N), t(N);
        u[0]=y0;
        t[0]=0;
        
        double tt,uu;


        for(size_t i=0; i<N; i++){

            tt=t[i];
            uu=u[i];

            auto foo =[this,&h,&tt,&uu](double x) {return x - h*(theta*f(tt+h,x) + (1-theta)*f(tt ,uu))-uu;};

            std::tuple<double,bool> x;

            if(met==method::secant)

                x = apsc::secant(foo, -1, 1,h*h,h*h,1000);
            
            if(met==method::newton){

                auto dfoo= apsc::makeCenteredDerivative<1>(foo, h);

                x = apsc::Newton(foo, dfoo, -1, h*h, h*h, 1000);

            }

            if(std::get<1>(x)==false){
                std::cerr<<"This Method does not converge "<<std::endl;
                break;
            }


           u[i+1]=std::get<0>(x);
           t[i+1]=t[i]+h;
        }

        return std::make_pair(t,u);

    }


std::pair<std::vector<double>,std::vector<double>> CauchySolver::conv_rate(unsigned int K,std::function<double(double)> u_ex){

    std::vector<double> hh,error;

    for(unsigned i=1;i<=K;i++){

        auto NN=pow(2,i);

        std::vector<double> sol_ex;

        hh.emplace_back(T/NN);

        CauchySolver problem=*this;

        problem.set_Nsteps(NN);

        auto [tt,u_approx]= problem.solver();

        for(int j=0;j<NN;j++)
            sol_ex.push_back(u_ex((j/NN)*T));
        

        error.emplace_back(compute_inf_error(sol_ex,u_approx));

    }

    return std::make_pair(hh,error);

}
