#include <iostream>
#include <math.h>
#include "time.h"
#include <fstream>
#include <iomanip>

using namespace std;

double f(double x){
    return atan(x);
}

double o(double x){
    return 0;
}

double derivative(double h, double x){
    return (f(x+h)-f(x-h))/(2*h);
}


double * get_h(double start, double factor, int n){
    double * h = new double[n];
    h[0]=start;
    for(int i=1; i<n;i++){    
        h[i]=h[i-1]*factor;
    }
    return h;
}

void derivatives ( double x, int n){
    ofstream ofile;
    ofile.open("results.txt");
    ofile << "f(x) = atan(x), x=sqrt(2), where h is the step size" << endl;

    clock_t start, finish;
    start = clock();

    double one = 1;
    double three = 3;
    double actual_value=one/three;


    double * h = get_h(1,0.1,n);
    double results[n];
    for (int i = 0;i<n;i++){
        double result=derivative(h[i],x);
        ofile << " h = " << setw(7) << h[i] << setprecision(15) << " |  f'(x) = " << setw(17) << result << " | Error = " << abs(actual_value-result) << endl;
    }

    finish = clock();
    double clock_delta = finish - start;
    double clock_clocks = CLOCKS_PER_SEC;
    double time = clock_delta/clock_clocks;
    ofile  <<"time elapsed: " << setprecision(15) << time << "s" <<endl;

}

int main(){

    int n=20;
    double x = sqrt(2);

    derivatives(x,n);

    return 0;
}

