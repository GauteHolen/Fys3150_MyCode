#ifndef eigenvaluesolver_HPP
#define eigenvaluesolver_HPP
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

class eigenvaluesolver{

    protected:
        double epsilon;
        double iterations;
        int m_N;
        mat m_R;
        mat m_A;
        ofstream ofile;

    public:
        void initialize(mat A, int n);
        void write_to_file(string filename);
};

class jacobi_method : protected eigenvaluesolver {

    private:
        void rotate();
        void update_max_off_diag();
        double max_off_diag;

        int max_iterations;
        int l;
        int k;

    public:
        void init(mat A, int n);
        void solve();

};

class utils {
    public:
        mat get_simple_A(double p_min, double p_max, int n);
};

#endif