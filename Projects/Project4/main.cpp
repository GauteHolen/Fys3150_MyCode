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
    int start_sampling = atoi(argv[4]);
    bool random_spins = false;
    int rng =atoi(argv[5]);
    if(rng==1){
        random_spins=true;
    }


    if(T_mode == "gradient"){

        double T_start = atof(argv[6]);
        double T_end = atof(argv[7]);
        int n_steps = atoi(argv[8]);

        double T_step = (T_end-T_start)/((double) n_steps);
        
        ofstream ofile;
        string filename = "./Projects/Project4/results/T_gradient_"+to_string(T_start)+"-"+to_string(T_end)+"_L_"+to_string(L)+"_mcs_"+to_string(mcs)+".txt";
        ofile.open(filename);
        ofile<<"T\t"<<"E[E]\t"<<"E[M]\t"<<"CV\t"<<"X"<<endl;
        ofile.close();
        cout<<"Running simulations on all available threads..."<<endl;
        cout<<"["<<ends;


        double start = omp_get_wtime();

        {
        #pragma omp parallel for   
            for (int i = 0; i < n_steps; i++)
            {   
                cout<<"-";
                double T = T_start+i*T_step;
                Ising ising(L,T,random_spins);
                ising.sampler.T_gradient_filename(filename);
                ising.run(mcs,start_sampling,false,true);
            }
        }
        cout<<"]"<<endl;
        double finish = omp_get_wtime();
        double runtime=finish-start;
        cout<<"runtime: "<<runtime<<" seconds"<<endl;

    }

    else if (T_mode == "single")
    {
        double temperature = atof(argv[6]);
        Ising ising(L,temperature,random_spins);
        ising.run(mcs, start_sampling, true, false);
    }
    
    cout<<"Done"<<endl;

}