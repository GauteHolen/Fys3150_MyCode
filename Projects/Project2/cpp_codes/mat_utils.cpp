#include "eigenvaluesolver.hpp"



void mat_utils::init(double p_first, double p_last, int m_N, string algo){
    p_0=p_first;
    p_max=p_last;
    h = (p_last-p_first)/ (double) (m_N);
    n=m_N;
    algorithm=algo;
}

mat mat_utils::get_simple_A(){
    

    mat A(n,n);
    double a = (double) -1/(h*h);
    double d = (double) 2/(h*h);

    A(0,0)=d; A(0,1)=a;
    for(int i = 1; i<n-1; i++){
        A(i,i)=d;
        A(i,i-1)=a;
        A(i,i+1)=a;
    }
    A(n-1,n-1)=d;
    A(n-1,n-2)=a;

    return A;
}

mat mat_utils::get_single_electron_V(){
    mat A(n,n);
    double hh = h*h;
    double e = (double) -1/(hh);
    double d = (double) 2/(hh);

    vec p = vec(n);
    for (int i = 1; i < n+1; i++)
    {
        p(i-1)=(double) i*h;
    }
    


    A(0,0)=d+p(0)*p(0); A(0,1)=e;
    for(int i = 1; i<n-1; i++){
        double p_i=p(i);
        A(i,i)=d+(p_i*p_i);
        A(i,i-1)=e;
        A(i,i+1)=e;
    }
    A(n-1,n-1)=d + p(n-1)*p(n-1);
    A(n-1,n-2)=e;

    return A;
}


mat mat_utils::get_double_electron_V(double w){
    w_r=w;
    mat A(n,n);
    double hh = h*h;
    double ww = w_r*w_r;
    double e = (double) -1/(hh);
    double d = (double) 2/(hh);


    vec p = vec(n);
    for (int i = 1; i < n+1; i++)
    {
        p(i-1)=(double) i*h;
    }
    
    A(0,0)=d+ww*p(0)*p(0)+1.0/p(0); A(0,1)=e;
    for(int i = 1; i<n-1; i++){
        double p_i=p(i);
        A(i,i)=d + ww * (p_i*p_i) + 1.0/p_i;
        A(i,i-1)=e;
        A(i,i+1)=e;
    }
    A(n-1,n-1)=d + ww * p(n-1)*p(n-1) + 1.0/p(n-1);
    A(n-1,n-2)=e;

    return A;
}


vec mat_utils::get_analytical_eigval_simple(){

    vec eigval(n);
    double d = (double) 2/(h*h);
    double a = (double) -1/(h*h);

    for (int i = 0; i < n; i++)
    {
        int j=i+1;
        
        eigval(i)=(double) d+ 2*a*cos(j * datum::pi / (n+1));
        
    }
    
    return eigval;

}


void mat_utils::write_to_file(string filename){
    ofile.open("Projects/Project2/resulsts/"+filename);

    ofile<<"Algorithm: "<<algorithm<<endl;

    ofile<<endl;

    ofile<<"==== Matrix A initial conditions: ===="<<endl;  
    ofile<<"p_0: "<<p_0<<endl;  
    ofile<<"p_max: "<<p_max<<endl;
    ofile<<"matrix nxn dim(n): "<<n<<endl;
    ofile<<"h: "<<h<<endl;
    if(algorithm=="QDdouble"){
        ofile<<"w_r: "<<w_r<<endl;
    }
    ofile<<endl;

    ofile.close();


}