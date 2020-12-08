#include "Person.hpp"



Person::Person(int initial_state){
    state = initial_state;
}

Person::Person(const Person &person){
    state=person.state;
}

int Person::get_state(){
    return state;
}

void Person::set_state(int _state){
    state = _state;
}
