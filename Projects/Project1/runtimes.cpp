#include "project1.cpp"
#include <iostream>
#include <cmath>


int main(){

    double x_0=0;double x_n=1;

    ofstream ofile;
    ofile.open("./Projects/Project1/Results/runtimes.txt");

    ofile<<"algorithm";
    for (int i = 1; i < 7; i++){ofile<<"\t"<<i;}
    ofile<<endl;

    results result;
    ofile<<"fastest";
    for (int i = 1; i < 7; i++){
        clock_t start, finish; start = clock();
        results result = fastest_solution(x_0,x_n,pow(10,i));
        finish = clock();double clock_delta = finish - start;double clock_clocks = CLOCKS_PER_SEC;
        ofile<<"\t"<<clock_delta/clock_clocks;
        }
    ofile<<endl;
    ofile<<"specific";
    for (int i = 1; i < 5; i++){
        clock_t start, finish; start = clock();
        results result = specific_solution(x_0,x_n,pow(10,i));
        finish = clock();double clock_delta = finish - start;double clock_clocks = CLOCKS_PER_SEC;
        ofile<<"\t"<<clock_delta/clock_clocks;
        }
    ofile<<endl;
    ofile<<"general";
    for (int i = 1; i < 5; i++){
        clock_t start, finish; start = clock();
        results result = general_solution(x_0,x_n,pow(10,i));
        finish = clock();double clock_delta = finish - start;double clock_clocks = CLOCKS_PER_SEC;
        ofile<<"\t"<<clock_delta/clock_clocks;
        }
    ofile<<endl;
    ofile<<"arma solve1";
    for (int i = 1; i < 5; i++){
        clock_t start, finish; start = clock();
        results result = arma_solution1(x_0,x_n,pow(10,i));
        finish = clock();double clock_delta = finish - start;double clock_clocks = CLOCKS_PER_SEC;
        ofile<<"\t"<<clock_delta/clock_clocks;
        }
    ofile<<endl;
    ofile<<"arma solve2";
    for (int i = 1; i < 5; i++){
        clock_t start, finish; start = clock();
        results result = arma_solution2(x_0,x_n,pow(10,i));
        finish = clock();double clock_delta = finish - start;double clock_clocks = CLOCKS_PER_SEC;
        ofile<<"\t"<<clock_delta/clock_clocks;
        }
    
    ofile.close();







}