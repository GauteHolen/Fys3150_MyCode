#include "SolarSystem.hpp"

SolarSystem::SolarSystem(string name_){
    n_bodies=0;

    name = name_;

    pi = arma::datum::pi;
    G = 4*pi*pi;
    c = 2.998*pow(10,4)*3.154/1.495;
    system_radius = 300;

    foldername = "./Projects/Project3/results/"+name;

};
 

double SolarSystem::get_angular_momentum(){

    double L = 0;
    double v;
    double r;
    double m;
    for (int i = 0; i < n_bodies; i++)
    {
        v = bodies[i].get_speed();
        r = bodies[i].get_r();
        m = bodies[i].mass;
        L += v*r*m;
    }
    return L;
}


double SolarSystem::relativistic_correction(arma::vec3 r_vec, arma::vec3 v){
    double l = arma::dot(r_vec,v);
    double r = sqrt(r_vec(0)*r_vec(0)+r_vec(1)*r_vec(1)+r_vec(2)*r_vec(2));

    return 1.0+((3*l*l)/(r*r*c*c));
}


void SolarSystem::add_body(Body &body){
    //Body new_body = body;

    cout<<"Added celestial body '"<<body.name<<"' to the system "<<name<<endl;

    bodies.push_back(body);
    n_bodies++;

};

arma::vec3 SolarSystem::get_Fg(Body &body){


    double r;
    double rb;
    double dx;
    double dy;
    double dz;
    double lambda = 1.0;
    arma::vec3 Fg = {0,0,0};


    for (int i = 0; i < n_bodies; i++)
    {   
        if((bodies[i].contributes_to_Fg == true) && (bodies[i].name!=body.name)){


            dx=body.position(0)-bodies[i].position(0);
            dy=body.position(1)-bodies[i].position(1);
            dz=body.position(2)-bodies[i].position(2);

            if(relativistic){

                lambda = relativistic_correction({dx,dy,dz},body.velocity);
            }


            r=sqrt(dx*dx+dy*dy+dz*dz);
            rb = pow(r,1.0 + beta);

            Fg(0)+= -G*body.mass*bodies[i].mass*dx*lambda/rb;
            Fg(1)+= -G*body.mass*bodies[i].mass*dy*lambda/rb;
            Fg(2)+= -G*body.mass*bodies[i].mass*dz*lambda/rb;
        }
        


    }


    return Fg;
    

}

void SolarSystem::update(){

    //Variables used to update:
    double F_new;
    arma::vec3 a = {0,0,0};
    double a_new;

    for (int i = 0; i < n_bodies; i++)
        {
            if(bodies[i].affected_by_Fg==true){


                //Has "new" Fg from before if not unless this is first update
                if(t==0.0){
                    bodies[i].Fg = get_Fg(bodies[i]);
                }
                

                //Current step for position update:
                for (int j = 0; j < 3; j++)
                {
                    a(j)=bodies[i].Fg(j)/bodies[i].mass;
                    bodies[i].position(j)+=bodies[i].velocity(j)*h + 0.5*h*h*a(j);

                    //Check if body is outside solar system
                    if(abs(bodies[i].position(j))>system_radius)
                    {
                        bodies[i].lost=true;
                    }
                }
                
                //Next step for velocity update with new position
                bodies[i].Fg = get_Fg(bodies[i]);
                for (int j = 0; j < 3; j++)
                {
                    a_new=bodies[i].Fg(j)/bodies[i].mass;
                    bodies[i].velocity(j)+=0.5*h*(a(j)+a_new);
                }

            }

            if(bodies[i].lost==false){
                bodies[i].write_to_file(t);
            }
            

            

        }



}

void SolarSystem::write_init(int n, double t_n, double runtime){
    string filename = "system_props.txt";
    string relativistic_str = "unassigned";
    ofile.open(foldername+"/"+filename);
    ofile<<"Number of bodies: "<<n_bodies<<endl;
    ofile<<"Beta = "<<beta<<endl;

    if(relativistic==true)
    {   
        relativistic_str="true";
        }
    else
    {
        relativistic_str="false";
    }
    

    ofile<<"Relativistic correction: "<<relativistic_str<<endl;
    ofile<<"n = "<<n<<endl;
    ofile<<"t_n = "<<t_n<<"years"<<endl;
    double h=t_n/n;
    ofile<<"stepsize = "<<h<<"years"<<endl;
    ofile<<"runtume = "<<runtime<<"seconds"<<endl;


}

void SolarSystem::run(int n, double t_n, bool GR, double Beta){

    relativistic = GR;
    beta = Beta;
    string beta_str = to_string(beta); beta_str = beta_str.substr(0,4);
    string tn_str = to_string(t_n); tn_str = tn_str.substr(0,4);

    
    foldername +="_n_"+to_string(n)+"_tn_"+tn_str+"_GR_"+to_string(GR)+"_B_"+beta_str;
    //const char * folderpath = foldername.c_str();
    int check = mkdir(foldername.c_str(),0777);
    if(check!=0){
        cout<<"Not able to create directory, it likely already exists from previous run. Consider deleting the directory and running again"<<endl;
    }

    for (int i = 0; i < n_bodies; i++)
    {
        bodies[i].set_folderpath(foldername);
    }

    clock_t start, finish;
    h = t_n/(double) n;

    start = clock();
    while (t<t_n){
        update();
        t+=h;
    }

    finish = clock();
    double runtime=(double) (finish-start)/ (double) CLOCKS_PER_SEC;

    write_init(n,t_n,runtime);



}

void SolarSystem::print(){

    cout<<"System name: "<<name<<endl;
    cout<<"Directory with position vectors: "<<foldername<<endl;
    cout<<"Number of bodies: "<<n_bodies<<endl;


}