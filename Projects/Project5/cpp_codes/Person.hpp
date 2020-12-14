#ifndef Person_HPP
#define Perspn_HPP
#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * 
 * @brief Object holding a persons state, with simple get and set functions
 * 
 */
class Person{
    public:
        Person(int initial_state);
        Person(const Person &person);
        
        int get_state();
        void set_state(int _state);


    private:
        int state;//0 suspectible, 1 infected, 2 recovering

};

#endif