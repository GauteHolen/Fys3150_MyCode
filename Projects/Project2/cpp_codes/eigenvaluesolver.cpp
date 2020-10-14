#include "eigenvaluesolver.hpp"

void eigenvaluesolver::initialize(mat A, int n, string algo){

    algorithm=algo;
    epsilon = 1.0e-8;
    m_N=n;
    m_A=A;

    //Setting up the matrix for the eigenvectors
    m_R = mat(n,n);
    m_R.eye();
#include <iostream>
}



void eigenvaluesolver::write_to_file(string filename){
    ofile.open("Projects/Project2/resulsts/"+filename,std::ios::app);
    
    ofile<<"==== Jacobi method details and results ===="<<endl;  
    ofile<<"iterations: "<<iterations<<endl;
    ofile<<"runtime: ";
    ofile<<setprecision(12)<<runtime<<"s"<<endl;
    ofile<<"First 5 eigenvalues: "<<endl;
    

    if(algorithm=="simple"){
        ofile<<"lambda\t"<<"analytical\t"<<"error\t"<<"n\t"<<endl;
        mat_utils utils;
        utils.init(0.0,1.0,m_N,algorithm);
        vec analytical = utils.get_analytical_eigval_simple();

        for (int i = 0; i < 5; i++)
        {
            ofile<<setprecision(12)<<eigenvalues(i)<<"\t"<<setprecision(12)<<analytical(i)<<"\t"<<setprecision(12)<<abs(analytical(i)-eigenvalues(i))<<"\t"<<i+1<<endl;
        }
    }

    else
    {
        ofile<<"lambda\t"<<"n\t"<<endl;
        for (int i = 0; i < 5; i++)
        {
            ofile<<setprecision(12)<<eigenvalues(i)<<"\t"<<i+1<<endl;
        }
    }
    
    
    
    ofile.close();
}

void eigenvaluesolver::print_eigenvalues(){
    eigenvalues=sort(eigenvalues);
    for (int i = 0; i < 5; i++)
        {
        cout<<"lambda_"<<i+1<<" = "<<eigenvalues(i)<<endl;
        }
}

