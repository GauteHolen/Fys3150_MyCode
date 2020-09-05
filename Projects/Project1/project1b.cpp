#include <iostream>
#include <math.h>
#include "time.h"
#include <fstream>
#include <iomanip>
#include <armadillo>


using namespace std;
using namespace arma;

double f_exact(double x){
    return 1.0-(1-exp(-10))*x-exp(-10*x);
}

double f(double x){
    return 100.0*exp(-10.0*x);
}



double * get_x (int n, double x_0, double x_n, double h) {
    double * x = new double[n];
    x[0]=x_0;
    x[n-1]=x_n;
    for (int i = 1; i < n-1; i++){
        x[i]=x[i-1]+h;
    }
    return x;
}

//-----VECTOR FUNCTIONS------//

vec get_exact(double x[], int n){
    vec exact(n);
    for (int i = 0; i < n; i++)
    {
        exact(i)=f_exact(x[i]);
    }
    return exact;
}


vec get_b(int n, double hh, double x[]){
    vec b(n);

    for (int i = 0; i < n; i++)
    {
        b(i)=hh*f(x[i]);
    }
    
    return b;
}

rowvec get_A_row(int row,int n){
    rowvec v = zeros<rowvec>(n);
    v(row-1)=-1;
    v(row)=2;
    v(row+1)=-1;
    return v;
}

//-----MATRIX FUNCTIONS------//


dmat get_A(int n) {
    dmat A(n,n);

    rowvec first_row = zeros<rowvec>(n);
    rowvec last_row = zeros<rowvec>(n);
    first_row(0)=2;
    first_row(1)=-1;
    last_row(n-2)=-1;
    last_row(n-1)=2;
    A.row(0) = first_row;
    A.row(n-1)=last_row;

    for (int i=1;i<n-1;i++){
        A.row(i) = get_A_row(i,n);
    }

    return A;
}


//-----UTILS-----//
void print_results(double x[], vec v, vec exact, int n){
    cout<<"   x:              v:              exact:          error:"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<setw(15)<<setprecision(7)<<x[i];
        cout<<setw(15)<<setprecision(7)<<v(i);
        cout<<setw(15)<<setprecision(7)<<exact(i);
        cout<<setw(15)<<setprecision(7)<<abs(v(i)-exact(i))<<endl;
    }
    
}



//-----SOLVER FUNCTIONS-----//

void general_solution(double x_0, double x_n, int n){

    clock_t start, finish;
    start = clock();

    double h; double hh;
    h=(double)1/(n-1);
    hh=h*h;

    double * x = get_x(n,x_0,x_n,h);

    mat A(n,n);
    vec b(n);
    A = get_A(n);
    b = get_b(n,hh,x);
    vec v = solve(A,b);
    vec exact = get_exact(x,n);
    print_results(x,v,exact,n);

    finish = clock();
    double clock_delta = finish - start;
    double clock_clocks = CLOCKS_PER_SEC;
    double time = clock_delta/clock_clocks;
    cout<<"time elapsed: " << setprecision(15) << time << "s" <<endl;
    cout <<"n = "<<n<<endl;
    cout<<"avg error: "<< setprecision(15) << abs(sum(v)-sum(exact))/n <<endl;

}



int main(){



    int n=10000;
    double x_0=0;
    double x_n=1;

    general_solution(x_0,x_n,n);

    return 0;
}