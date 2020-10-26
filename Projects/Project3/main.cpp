#include "./cpp_codes_OO/SolarSystem.hpp"
#include "./cpp_codes_OO/Body.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>
#include <iostream>
#include <iomanip>


using namespace arma;

int main(int argc, char const *argv[]){

    int n = atoi(argv[1]);
    double t_n = atof(argv[2]);
    string name = argv[3];
    string scenario = argv[4];
    string GR_str = argv[5];
    
    bool GR;
    if(GR_str=="GR"){GR=true;}
    else{GR=false;};  

    double beta = 2.0;
    if(argc>=6){beta=atof(argv[6]);}  
    

    

    ofstream ofile;
    
    double pi = arma::datum::pi;

    SolarSystem solarsystem(name);

    

    if(scenario == "earth_sun"){
        DEFAULT_SCENARIO:
        cout<<"Scenario: earth - sun"<<endl;
        vec3 pos_E = {1.0, 0.0, 0.0}; vec3 v_E = {0.0, 2*pi, 0.0};
        Body earth(pos_E, v_E, 0.000003, "earth",true);

        solarsystem.add_body(earth);

        vec3 pos_S = {0.0, 0.0 ,0.0}; Body sun(pos_S,pos_S,1,"sun",false,true);
        solarsystem.add_body(sun);
    }

    else if(scenario == "mercury"){
        cout<<"Scenario: mercury"<<endl;
        
        double m_merc = 0.000000166;
        vec3 pos_merc = vec3{0,0.3075,0};
        vec3 vel_merc = vec3{12.44,0,0};
        Body mercury (pos_merc,vel_merc,m_merc,"mercury",true);

        
        solarsystem.add_body(mercury);

        vec3 pos_S = {0.0, 0.0 ,0.0}; Body sun(pos_S,pos_S,1,"sun",false,true);
        solarsystem.add_body(sun);
    }

    else if(scenario == "escape"){

        cout<<"Scenario: escape velocity"<<endl;

        double min_v = 8.75;
        double max_v = 9.0;
        int n_planets = 12;

        vec3 pos_E = {1.0, 0.0, 0.0}; 
        vec3 v_E;
        double v_step = (max_v-min_v)/n_planets;
        double v = min_v;

        for (int i = 0; i < n_planets; i++)
        {
            v += v_step;
            v_E = {v, 0.0, 0.0};
            Body earth(pos_E, v_E, 0.000003, to_string(v),true,false);
            solarsystem.add_body(earth);
        }

        vec3 pos_S = {0.0, 0.0 ,0.0}; Body sun(pos_S,pos_S,1,"sun",false,true);
        solarsystem.add_body(sun);
    }

    else if(scenario=="3body"){

        vec3 pos_E = {0.9128884513088843,0.3928032801600736, 0.00006577938183713410}; 
        vec3 v_E = {-0.006957269992142644, 0.01579734315560513,-0.0000002582593092148153};
        v_E = v_E*365.24;
        Body earth(pos_E, v_E, 0.000003, "earth",true);
        solarsystem.add_body(earth);

        


        vec3 pos_J = {2.556653950007264e+00,-4.428596022378350e+00,-3.882840438937561e-02}; 
        vec3 v_J = {6.442741439253338e-03,4.130146620372741e-03,-1.612738541610256e-04};
        v_J = v_J * 365.24;
        double m_J = 0.000956 * atof(argv[7]);
        Body jupiter(pos_J, v_J,m_J , "jupiter",true);
        solarsystem.add_body(jupiter);




        vec3 pos_S = {0.0, 0.0 ,0.0}; Body sun(pos_S,pos_S,1,"sun",false,true);
        solarsystem.add_body(sun);

    }

    

    else
    {
        goto DEFAULT_SCENARIO; //This is a big nono but I wanted to try it and it was the easiest/laziest solition
    }
    
    
    solarsystem.run(n,t_n,GR,beta);
    
    solarsystem.print();

    return 0;
}