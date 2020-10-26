#include "Body.hpp"


void Body::write_to_file(double t){


    ofile.open(folderpath+"/"+filename,std::ios::app);
    ofile<<position(0)<<"\t"<<position(1)<<"\t"<<position(2)<<"\t"<<t<<endl;
    ofile.close();

};

double Body::get_r(){
    return sqrt(position(0)*position(0)+position(1)*position(1)+position(2)*position(2));
}

double Body::get_speed(){
    return sqrt(velocity(0)*velocity(0)+velocity(1)*velocity(1)+velocity(2)*velocity(2));
}




void Body::print(){
    cout<<"Body named '"<<name<<"' with mass "<<mass<<endl;
    cout<<"position:"<<endl;
    position.print();
    cout<<"velocity:"<<endl;
    velocity.print();
    cout<<"Fg:"<<endl;
    Fg.print();
}

void Body::set_folderpath(string path){
    folderpath = path;
    ofile.open(folderpath+"/"+filename);
    ofile.close();
}

Body::Body(arma::vec3 pos, arma::vec3 vel, double m,string name_,bool affected_by_Fg_, bool contributes_to_Fg_){
    affected_by_Fg = affected_by_Fg_;
    contributes_to_Fg = contributes_to_Fg_;
    position = pos;
    velocity = vel;
    mass = m;
    name = name_;
    lost = false;
    


    Fg = {0,0,0};
    filename=name+"_xyzt.txt";

};

Body::Body(arma::vec3 pos, arma::vec3 vel, double m,string name_,bool affected_by_Fg_){
    affected_by_Fg = affected_by_Fg_;
    contributes_to_Fg = true;
    position = pos;
    velocity = vel;
    mass = m;
    name = name_;
    lost = false;
    


    Fg = {0,0,0};
    filename=name+"_xyzt.txt";

};

//Had to make a copy constructor, this seems really dumb and tedious, I really hope there's a better way to do this...
Body::Body(const Body &body){
    affected_by_Fg=body.affected_by_Fg;
    contributes_to_Fg=body.contributes_to_Fg;
    lost = body.lost;
    position=body.position;
    velocity=body.velocity;
    mass=body.mass;
    name=body.name;
    Fg=body.Fg;
    filename=body.filename;
};
