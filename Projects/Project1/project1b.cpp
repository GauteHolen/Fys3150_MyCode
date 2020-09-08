#include "project1.cpp"
#include <iostream>


void write_results(int n, string filename){

    results result;
    result = fastest_solution (0,1,n);
    ofstream ofile;
    ofile.open("./Projects/Project1/Results/"+filename);
    ofile<<"x"<<"\t"<<"v"<<"\t"<<"u"<<"\t"<<"e"<<endl;
    for (int i = 0; i < n; i++)
    {
        ofile<<setprecision(12)<<result.x(i)<<"\t";
        ofile<<setprecision(12)<<result.v(i)<<"\t";
        ofile<<setprecision(12)<<result.u(i)<<"\t";
        ofile<<setprecision(12)<<result.e(i)<<endl;
    }
    ofile.close();

}

int main(){

    write_results(1000,"fastest100n.txt");

}