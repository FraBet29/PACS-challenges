#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "CauchySolver.hpp"

double test_function(double t, double y){
    return -t*exp(-y);
}

double exact_solution(double x){
    return log(1-x*x/2);
}

void write_solution(std::vector<double>,std::vector<double>);
void write_error(std::vector<double>,std::vector<double>);

int main() {

    size_t n_steps=100;
    double init_cond=0;
    double final_time=1.;

    CauchySolver P1(n_steps,init_cond,final_time,test_function,0.5,method::newton);

    auto solution= P1.solver();

    write_solution(solution.first,solution.second);

    auto error=P1.conv_rate(15,exact_solution);

    write_error(error.first,error.second);



    return 0;
}

   
void write_solution(std::vector<double> hh,std::vector<double> sol){



    std::ofstream fw("result.txt",std::ofstream::out);

    //check if file was successfully opened for writing
    if (fw.is_open()) {

    //store array contents to text file

    fw<<"# n\t"<<"t_n\t"<<"u_n\n";

    for (size_t i = 0; i < hh.size(); i++) 
        fw <<i+1<<"\t"<<hh[i]<<"\t"<<sol[i]<<"\n";
    
    fw.close();
    }
    else std::cout << "Problem with opening file";
    


}


void write_error(std::vector<double> hh,std::vector<double> err){

    std::ofstream fw("error_conv.txt",std::ofstream::out);

    //check if file was successfully opened for writing
    if (fw.is_open()) {

    //store array contents to text file

    fw<<"# t_n\t\t"<<"err_inf\n";

    for (size_t i = 0; i < hh.size(); i++) 
        fw <<hh[i]<<"\t\t"<<err[i]<<"\n";
    
    fw.close();
    }
    else std::cout << "Problem with opening file";
    

}