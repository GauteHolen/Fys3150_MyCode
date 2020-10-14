#include "Body.hpp"


void Body::write_to_file(string foldername,double t){


    ofile.open("./Projects/Project3/results/"+filename,std::ios::app);
    ofile<<position(0)<<"\t"<<position(1)<<"\t"<<position(2)<<"\t"<<t<<endl;
    ofile.close();

};

void Body::print(){
    cout<<"Body named '"<<name<<"' with mass "<<mass<<endl;
    cout<<"position:"<<endl;
    position.print();
    cout<<"velocity:"<<endl;
    velocity.print();
    cout<<"Fg:"<<endl;
    Fg.print();
}


Body::Body(arma::vec3 pos, arma::vec3 vel, double m,string name_){
    position = pos;
    velocity = vel;
    mass = m;
    name = name_;


    Fg = {0,0,0};
    filename=name+"_xyzt.txt";
    ofile.open("./Projects/Project3/results/"+filename);
    ofile.close();

};

//Had to make a copy constructor, this seems really dumb and tedious, I really hope there's a better way to do this...
Body::Body(const Body &body){
    position=body.position;
    velocity=body.velocity;
    mass=body.mass;
    name=body.name;
    Fg=body.Fg;
    filename=body.filename;
};
