#ifndef eigenvaluesolver_HPP
#define eigenvaluesolver_HPP
#include <fstream>
#include <armadillo>
#include "time.h"
#include <iomanip>

using namespace std;
using namespace arma;

class eigenvaluesolver{

    protected:

        clock_t start, finish;
        double runtime;
        double epsilon;
        double iterations;
        int m_N;
        mat m_R;
        mat m_A;
        vec eigenvalues;
        ofstream ofile;

    public:
        void initialize(mat A, int n);
        void write_to_file(string filename);
        void print_eigenvalues();
        
        
};

class jacobi_method : public eigenvaluesolver {

    private:
        void rotate();
        double vector_length(vec v, int n);
        double max_off_diag;
        int max_iterations;
        int l;
        int k;

    public:
        void init(mat A, int n);
        void solve();
        mat get_eigenvectors();
        vec get_eigenvalues();
        void update_max_off_diag();
        struct off_diag{
            int l;
            int k;
            double max_off_diag;
        };
        off_diag get_max_off_diag();
        
};

class mat_utils {

    protected:
        string algorithm;
        double h;
        int n;
        double p_0;
        double p_max;
        double w_r;
        ofstream ofile;


    public:
        void init(double p_first, double p_last, int n, string algorithm);
        void write_to_file(string filename);
        mat get_simple_A();
        mat get_single_electron_V();
        mat get_double_electron_V(double w);
        vec get_analytical_eigval_simple();
};

#endif