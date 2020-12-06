#ifndef functions_HPP
#define functions_HPP

#include <iostream>

using namespace std;

class functions {
    public:
        functions(double _a, double _b, double _c, int _N);
        void init(double _a, double _b, double _c, int _N);
        double susceptible(double S, double I, double t);
        double infected(double S, double I, double t);

    private:
        double a;
        double b;
        double c;
        int N;
};

#endif