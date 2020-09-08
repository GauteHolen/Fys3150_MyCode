#include "project1.cpp"
#include <iostream>
#include <cmath>


void write_results(int n, string filename){


    ofstream ofile;
    ofile.open("./Projects/Project1/Results/"+filename);
    ofile<<"h"<<"\t"<<"e_max"<<endl;
    for (int i = 1; i < n+1; i++)
    {
        results result;
        result = fastest_solution (0,1,pow(10,i));

        ofile<<setprecision(12)<<log10(result.h)<<"\t";
        ofile<<setprecision(12)<<max(result.e(i))<<endl;
    }
    ofile.close();

}

int main(){

    write_results(6,"max_e.txt");

}