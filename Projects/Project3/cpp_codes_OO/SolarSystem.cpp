#include "SolarSystem.hpp"

SolarSystem::SolarSystem(string name_){
    n_bodies=0;
    name = name_;
    pi = arma::datum::pi;
    G = 4*pi*pi;
    foldername = "./Projects/Project3/results/"+name;

};


void SolarSystem::add_body(Body &body){
    //Body new_body = body;

    cout<<"Added celestial body '"<<body.name<<"' to the system "<<name<<endl;
    cout<<body.name<<" initial position: "<<endl;
    body.position.print();

    bodies.push_back(body);
    n_bodies++;

};

arma::vec3 SolarSystem::get_Fg(Body &body){


    double r;
    double r3;
    double dx;
    double dy;
    double dz;
    arma::vec3 Fg = {0,0,0};


    for (int i = 0; i < n_bodies; i++)
    {
        if(bodies[i].name!=body.name){

            dx=body.position(0)-bodies[i].position(0);
            dy=body.position(1)-bodies[i].position(1);
            dz=body.position(2)-bodies[i].position(2);


            r=sqrt(dx*dx+dy*dy+dz*dz);
            r3=r*r*r;

            Fg(0)+= -G*body.mass*bodies[i].mass*dx/r3;
            Fg(1)+= -G*body.mass*bodies[i].mass*dy/r3;
            Fg(2)+= -G*body.mass*bodies[i].mass*dz/r3;
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

            //Has "new" Fg from before if not unless this is first update
            if(t==0.0){
                bodies[i].Fg = get_Fg(bodies[i]);
            }
            

            //Current step for position update:
            for (int j = 0; j < 3; j++)
            {
                a(j)=bodies[i].Fg(j)/bodies[i].mass;
                bodies[i].position(j)+=bodies[i].velocity(j)*h + 0.5*h*h*a(j);
            }
            
            //Next step for velocity update with new position
            bodies[i].Fg = get_Fg(bodies[i]);
            for (int j = 0; j < 3; j++)
            {
                a_new=bodies[i].Fg(j)/bodies[i].mass;
                bodies[i].velocity(j)+=0.5*h*(a(j)+a_new);
            }

            bodies[i].write_to_file(t);

        }



}

void SolarSystem::run(int n, double t_n){

    foldername +="_n_"+to_string(n)+"_tn_"+to_string(t_n);
    //const char * folderpath = foldername.c_str();
    int check = mkdir(foldername.c_str(),0777);
    if(check!=0){
        cout<<"Not able to create directory"<<endl;
    }

    for (int i = 0; i < n_bodies; i++)
    {
        bodies[i].set_folderpath(foldername);
    }
    

    h = t_n/(double) n;
    foldername=name+"_n_"+to_string(n)+"_tn_"+to_string(t_n);
    while (t<t_n){
        update();
        t+=h;
    }



}

void SolarSystem::print(){

    cout<<"System name: "<<name<<endl;
    cout<<"Number of bodies: "<<n_bodies<<endl;

    for (int i = 0; i < n_bodies; i++)
    {
        cout<<"position of body "<<bodies[i].name<<endl;
        bodies[i].position.print();
    }
    


}