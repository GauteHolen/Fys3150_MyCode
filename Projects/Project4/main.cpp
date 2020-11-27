#include<armadillo>
#include "./cpp_codes/Ising.hpp"
#include <omp.h>

/*


Takes args Lattice length L, temperature T and MC cycles mcs

*/
int main(int argc, char const *argv[]){

    string T_mode = argv[1];

    int L = atoi(argv[2]);
    int mcs = atoi(argv[3]);
    bool random_spins = false;
    int rng =atoi(argv[4]);
    if(rng==1){
        random_spins=true;
    }


    if(T_mode == "gradient"){

        double T_start = atof(argv[5]);
        double T_end = atof(argv[6]);
        int n_steps = atoi(argv[7]);

        double T_step = (T_end-T_start)/((double) n_steps);
        
        ofstream ofile;
        string filename = "./Projects/Project4/results/T_gradient_"+to_string(T_start)+"-"+to_string(T_end)+"_L_"+to_string(L)+"_mcs_"+to_string(mcs)+".txt";
        ofile.open(filename);
        ofile<<"T\t"<<"E[E]\t"<<"E[M]\t"<<"CV\t"<<"X"<<endl;
        ofile.close();
        cout<<"Running simulations on all available threads..."<<endl;
        cout<<"["<<ends;
        {
        #pragma omp parallel for   
            for (int i = 0; i < n_steps; i++)
            {   
                cout<<"-";
                double T = T_start+i*T_step;
                Ising ising(L,T,random_spins);
                ising.sampler.T_gradient_filename(filename);
                ising.run(mcs,mcs/5,false,true);
            }
        }
        cout<<"]"<<endl;
        cout<<"Done"<<endl;

    }

    else if (T_mode == "single")
    {
        double temperature = atof(argv[5]);
        Ising ising(L,temperature,random_spins);
        ising.run(mcs, mcs/5, true, false);
    }
    

}