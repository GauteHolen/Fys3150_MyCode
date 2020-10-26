#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "SolarSystem.hpp"
#include "Body.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>
#include <iostream>
#include <iomanip>




using namespace arma;

TEST_CASE("Conservation of angular momentum", "[Angular momentum]"){

    double pi = arma::datum::pi;
    SolarSystem solarsystem("test");

    vec3 pos_E = {1.0, 0.0, 0.0}; vec3 v_E = {0.0, 2*pi, 0.0};
    Body earth(pos_E, v_E, 0.000003, "earth",true);

    solarsystem.add_body(earth);

    vec3 pos_S = {0.0, 0.0 ,0.0}; Body sun(pos_S,pos_S,1,"sun",false,true);
    solarsystem.add_body(sun);

    double L_i = solarsystem.get_angular_momentum();


    solarsystem.run(10000,20,true,2.0);

    double L_f = solarsystem.get_angular_momentum();


    double epsilon = 1e-8;
    REQUIRE(abs(L_f-L_i) < epsilon);
}