#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace arma;


int main(int argc, char const *argv[]){

    int n = atoi(argv[1]);
    double t_n = atof(argv[2]);

    ofstream ofile;

    string filename = "euler_Earth_Pos.txt";
    ofile.open("./Projects/Project3/results/euler_posE.txt");
    ofile.close();
    ofile.open("./Projects/Project3/results/euler_posE.txt",std::ios::app);
    ofile<<"x\ty\tz\tt"<<endl;

    double h = t_n/(double) n;

    double pi = datum::pi;
    double v_0 = 2*pi;
    double G = 4*pi*pi;

    //Initial conditions:
    //Earth:
    vec3 pos_E = {1.0, 0.0, 0.0};
    vec3 v_E = {0.0, v_0, 0.0};
    vec3 a_E = {0.0, 0.0, 0.0};
    vec3 F_g = {0.0, 0.0, 0.0};
    double m_E = 0.000003;

    //Sun
    vec3 pos_S = {0.0, 0.0 ,0.0};
    double m_S = 1;

    //Setting up variables
    double t = 0;
    double r;
    double F_new;
    double a_new;
    while (t<t_n)
    {

        r=sqrt(pos_E(0)*pos_E(0)+pos_E(1)*pos_E(1)+pos_E(2)*pos_E(2));

        for (int i = 0; i < 3; i++)
        {
            F_g(i) = -G*m_E*m_S*(pos_E(i)-pos_S(i))/(r*r*r);
            pos_E(i) += v_E(i)*h;
            v_E(i) += F_g(i)*h/m_E;

        }


        ofile<<pos_E(0)<<"\t"<<pos_E(1)<<"\t"<<pos_E(2)<<"\t"<<t<<endl;
        



        t+=h;
    }
    
    ofile.close();

}