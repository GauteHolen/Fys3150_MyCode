#include "eigenvaluesolver.hpp"

void eigenvaluesolver::initialize(mat A, int n){

    epsilon = 1.0e-8;
    m_N=n;
    m_A=A;
    
    cout<<epsilon<<endl;

    //Setting up the matrix for the eigenvectors
    m_R = mat(n,n);
    m_R.eye();
    //cout<<m_R.print<<endl;;

}

void eigenvaluesolver::write_to_file(string filename){

}