#include<armadillo>
#include "./cpp_codes/Ising.hpp"

/*


Takes args Lattice length L, temperature T and MC cycles mcs

*/
int main(int argc, char const *argv[]){
    int L = atoi(argv[1]);
    double temperature = atof(argv[2]);
    int mcs = atoi(argv[3]);

    Ising ising(L,temperature,true);
    ising.print();
    ising.run(mcs);
    ising.print();


}