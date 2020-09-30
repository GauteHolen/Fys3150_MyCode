#include "catch.hpp"
#include "eigenvaluesolver.hpp"


TEST_CASE("Arma eigenvector comparison", "[arma_eigenvec]"){
    int n = 5;
    double epsilon = 1e-06;

    mat_utils mat_utils;
    mat_utils.init(0,1,n,"unit_test");
    mat A = mat_utils.get_simple_A();
    jacobi_method jacobi_method;
    jacobi_method.init(A,n,"unit_test");
    jacobi_method.solve();
    mat eigenvec_jacobi = jacobi_method.get_eigenvectors();
    vec eigval;
    mat eigvec;
    eig_sym(eigval, eigvec, A);

    int same_vec_count=0;
    for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                double similarity = abs(dot(eigenvec_jacobi.col(i),eigvec.col(j)));
                if(similarity>1-epsilon){
                    same_vec_count++;
                }
            }
            
        }
    REQUIRE(same_vec_count==n);
}

TEST_CASE("eigenvector orthogonality", "[eigenvec_orthogonal]"){
    int n = 5;
    double epsilon = 1e-06;
    mat_utils mat_utils;
    mat_utils.init(0.0,1.0,n,"unit_test");
    mat A = mat_utils.get_simple_A();
    jacobi_method jacobi_method;
    jacobi_method.init(A,n,"unit_test");
    jacobi_method.solve();
    mat eigenvec_jacobi = jacobi_method.get_eigenvectors();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(j!=i){
                REQUIRE(abs(dot(eigenvec_jacobi.col(i),eigenvec_jacobi.col(j)))<epsilon);
            }
        }
    }
}

TEST_CASE("Test max off diag", "[max_off_diag]"){
    mat A(5,5);
    A.zeros();
    A(2,2)=7.0;
    A(0,3)=5.0;

    jacobi_method solver;
    solver.init(A, 5,"unit_test");
    solver.update_max_off_diag();
    jacobi_method::off_diag max_off_diag;
    max_off_diag = solver.get_max_off_diag();
    REQUIRE(max_off_diag.l==0);
    REQUIRE(max_off_diag.k==3);
    REQUIRE(max_off_diag.max_off_diag==5.0);

}