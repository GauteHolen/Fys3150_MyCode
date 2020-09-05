#include <iostream>
#include <math.h>
#include "time.h"
#include <fstream>
#include <iomanip>
#include <armadillo>


using namespace std;
using namespace arma;

inline double f_u(double x){
    return 1.0-(1-exp(-10))*x-exp(-10*x);
}

inline double f(double x){
    return 100.0*exp(-10.0*x);
}

vec error(vec u, vec v, int n){
    vec e(n);
    for (int i = 1; i < n-1; i++){
        e(i)=abs(log(abs((v(i)-u(i))/u(i))));
    }
    return e;
}



vec get_x (int n, double x_0, double x_n, double h) {
    vec x(n);
    x(0)=x_0;x(n-1)=x_n;
    for (int i = 1; i < n-1; i++){
        x[i]=x[i-1]+h;
    }
    return x;
}

//-----VECTOR FUNCTIONS------//

vec get_u(vec x, int n){
    vec u(n);
    for (int i = 0; i < n; i++){
        u(i)=f_u(x(i));
    }
    return u;
}


vec get_b(int n, double hh, vec x){
    vec b(n);
    for (int i = 0; i < n; i++){
        b(i)=hh*f(x(i));
    }
    return b;
}

rowvec get_A_row(int row,int n){
    rowvec v = zeros<rowvec>(n);
    v(row-1)=-1;v(row)=2;v(row+1)=-1;
    return v;
}

//-----MATRIX FUNCTIONS------//


dmat get_A(int n) {
    dmat A(n,n);
    rowvec first_row = zeros<rowvec>(n);
    rowvec last_row = zeros<rowvec>(n);
    first_row(0)=2; first_row(1)=-1; last_row(n-2)=-1; last_row(n-1)=2;
    A.row(0) = first_row; A.row(n-1)=last_row;

    for (int i=1;i<n-1;i++){
        A.row(i) = get_A_row(i,n);
    }
    return A;
}


//-----UTILS-----//
void print_results(vec x, vec v, vec u, vec e, int n){
    cout<<"   x:              v:              u:          error:"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<setw(15)<<setprecision(7)<<x(i);
        cout<<setw(15)<<setprecision(7)<<v(i);
        cout<<setw(15)<<setprecision(7)<<u(i);
        cout<<setw(15)<<setprecision(7)<<e(i)<<endl;
    }
    
}


//-----SOLUTION FUNCTIONS-----//

vec general_solve(mat A, vec b, int n){
    vec y(n),x(n);
    mat L(n,n),U(n,n);
    lu(L,U,A);

    //Forwards substitution for y
    for (int j = 0; j < n; j++)
    {   
        double y_sum=0;     
        for (int i = 0; i < j+1; i++)
        {
            double l_ij=L(j,i);
            double y_i=y(i);
            y_sum+=l_ij*y_i;
        }        
        y(j)=(b(j)-y_sum)/L(j,j);
        
    }

    //Backwards substitution for x
    for (int j = n-1; j > -1; j--)
    {   
        double x_sum=0;     
        for (int i = n-1; i > j; i--)
        {
            x_sum+=U(j,i)*x(i);
        }        
        x(j)=(y(j)-x_sum)/U(j,j);   
    }   

    //y = solve(L,b);
    return x;
}


//-----SOLUTION FUNCTIONS-----//

void general_solution(double x_0, double x_n, int n){

    clock_t start, finish;
    start = clock();

    double h; double hh;
    h=(double)1/(n-1);
    hh=h*h;

    vec x = get_x(n,x_0,x_n,h);

    mat A(n,n);
    vec b(n);
    A = get_A(n);
    b = get_b(n,hh,x);
    vec v = general_solve(A,b,n);
    vec u = get_u(x,n);
    vec e = error(u,v,n);
    print_results(x,v,u,e,n);

    finish = clock();
    double clock_delta = finish - start;
    double clock_clocks = CLOCKS_PER_SEC;
    double time = clock_delta/clock_clocks;
    cout<<"time elapsed: " << setprecision(15) << time << "s" <<endl;
    cout <<"n = "<<n<<endl;
    cout<<"max error: "<< setprecision(15) << max(e) <<endl;
}



int main(){



    int n=100;
    double x_0=0;
    double x_n=1;

    general_solution(x_0,x_n,n);

    return 0;
}