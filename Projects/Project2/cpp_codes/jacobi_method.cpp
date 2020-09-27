#include "eigenvaluesolver.hpp"

/*

======== DISCLAIMER =========

This file is implementing the jacobi method just as described in the lecture 
notes chapter 7. A lot of the code is copied, only modified slightly
as I use armadillo and classes to structure this code. I do not claim to
have invented the jacobi method, or this way of implementing it. However,
as I understand the concepts of how it works, I see no reason to re-write 
it from scratch, as it would in all likelyhood be pretty much the same code
with the same variable-names.

*/

void jacobi_method::init(mat A, int n){
    initialize(A, n);
    max_iterations = (double) n * (double) n * (double) n ;
}

void jacobi_method::rotate(){

    double s, c;
    if ( m_A(k,l) != 0.0 ) {
        double t, tau;
        tau = (m_A(l,l) - m_A(k,k))/(2*m_A(k,l));
        if ( tau > 0 ) {
            t = 1.0/(tau + sqrt(1.0 + tau*tau));
        } else {
            t = -1.0/( -tau + sqrt(1.0 + tau*tau));
        }
        c = 1/sqrt(1+t*t);
        s = c*t;

    } else {
        c = 1.0;
        s = 0.0;
    }

    //cout<<"c = "<<c<<" , s = "<<s<<endl;

    double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
    a_kk = m_A(k,k);
    a_ll = m_A(l,l);

    // changing the matrix elements with indices k and l
    m_A(k,k) = c*c*a_kk - 2.0*c*s*m_A(k,l) + s*s*a_ll;
    m_A(l,l) = s*s*a_kk + 2.0*c*s*m_A(k,l) + c*c*a_ll;
    m_A(k,l) = 0.0; // hard-coding of the zeros
    m_A(l,k) = 0.0;
    // and then we change the remaining elements
    for ( int i = 0; i < m_N; i++ ) {
        if ( i != k && i != l ) {
            a_ik = m_A(i,k);
            a_il = m_A(i,l);
            m_A(i,k) = c*a_ik - s*a_il;
            m_A(k,i) = m_A(i,k);
            m_A(i,l) = c*a_il + s*a_ik;
            m_A(l,i) = m_A(i,l);
            }
        // Finally, we compute the new eigenvectors
        r_ik = m_R(i,k);
        r_il = m_R(i,l);
        m_R(i,k) = c*r_ik - s*r_il;
        m_R(i,l) = c*r_il + s*r_ik;
        }
    return;

}

void jacobi_method::update_max_off_diag(){
    max_off_diag=0;
    for (int i = 0; i < m_N; i++)
    {
        for (int j = i + 1; j < m_N; j++)
        {
            if(abs(m_A(i,j))>max_off_diag){
                max_off_diag=abs(m_A(i,j));
                l = i;
                k = j;
            }
        }
    }
    //cout<<"max off diag ="<<max_off_diag<<" , l = "<<l<<" , k = "<<k<<endl;
}

void jacobi_method::solve(){

    iterations = 0;
    update_max_off_diag();

    m_R.print();

    while (max_off_diag > epsilon && iterations < max_iterations)
    {
        //m_A.print();
        rotate();
        update_max_off_diag();
        iterations++;
    }
    
    cout<<"iterations: "<<iterations<<endl;
    m_R.print();

}

