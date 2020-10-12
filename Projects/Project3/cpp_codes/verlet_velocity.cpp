#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(){

    int n = 100;
    double t_n=2;
    double h = t_n/(double) n;

    double pi = datum::pi;
    double v_0 = 2*pi;
    double G = 4*pi*pi;

    //Initial conditions:
    //Earth:
    vec3 pos_E = double[1.0, 0.0, 0.0];
    vec3 v_E = vec3(0.0, v_0, 0.0);
    vec3 a_E = vec3(0.0, 0.0, 0.0);
    vec3 F_g = vec3(0.0, 0.0, 0.0);
    double m_E = 0.000003;

    //Sun
    vec3 pos_S (0.0, 0.0 ,0.0);
    double m_S = 1;


    double t = 0;
    double r;
    double F_new;
    double a_new;
    while (t<t_n)
    {

        r=sqrt(pos_E(0)*pos_E(0)+pos_E(1)*pos_E(1)+pos_E(2)*pos_E(2));

        for (int i = 0; i < 3; i++)
        {
            //Current step:
            F_g(i) -= G*m_E*m_S*(pos_E(i)-pos_S(i))/(r*r*r);
            a_E(i) = F_g(i)/m_E;
            pos_E(i) = v_E(i)*h + 0.5*h*h*a_E(i);

            //Next step:
            F_new = G*m_E*m_S*(pos_E(i)-pos_S(i))/(r*r*r);
            a_new = F_new/m_E;
            v_E(i) += 0.5*h*(a_E(i)+a_new);
        }
    
        pos_E.print();
        



        t+=h;
    }
    
    





















}