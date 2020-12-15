#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "RK_solver.hpp"
#include "MC_solver.hpp"

TEST_CASE("MC init population", "[MC init population]"){
    MC_solver mc_solver;
    mc_solver.init_population(10,5,5,0);
    std::vector<Person> population = mc_solver.get_population();
    int S = 0;
    for (int i = 0; i < 10; i++)
    {
        int state = population[i].get_state();
        if(state==0){
            S+=1;
        }
    }
    REQUIRE(S==5);

    S = 0;
    Person person(0);
    population.push_back(person);
    for (int i = 0; i < 11; i++)
    {
        int state = population[i].get_state();
        if(state==0){
            S+=1;
        }
    }
    REQUIRE(S==6);

    S = 0;
    population.erase(population.begin());
        for (int i = 0; i < 10; i++)
    {
        int state = population[i].get_state();
        if(state==0){
            S+=1;
        }
    }
    REQUIRE(S==5);
    population[0].set_state(2);
    S = 0;
    int R = 0;
        for (int i = 0; i < 10; i++)
    {
        int state = population[i].get_state();
        if(state==0){
            S+=1;
        }
        else if(state==2){
            R+=1;
        }
    }
    REQUIRE(S==4);
    REQUIRE(R==1);
}

TEST_CASE("RK expected values", "[RK expected values]"){
    double a=4;
    double b=1;
    double c=0.5;
    double EI=400*(1-b/a)/(1+b/c);

    RK_solver rk_solver;
    rk_solver.init_population(400,300,100,0);
    rk_solver.init_constants(a,b,c,0,0,0,0,0,0);
    rk_solver.solve(0,10,500,&RK_solver::susceptible, &RK_solver::infected, &RK_solver::recovering);
    double I = rk_solver.get_last_I();

    REQUIRE(I-EI <1);
}