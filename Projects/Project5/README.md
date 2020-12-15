# Project 5: Disease modelling 
In this project, disease development in a population is modelled with a fourth order Runge-Kutta metod and a Monte-Carlo simulation.

Please see report.pdf for more info.

## How to run
There is a python wrapper called main.py, with all the input parameters for the initial conditions for the .cpp program which runs the simulations. 

When all the boleans do_tests, do_compile, do_execute and
do_plots are True, the wrapper will test, compile, execute, write to files and plot the relevant plots for the type of run.

<img src="/Projects/Project5/Python_wrapper.png">

Every run will trigger both the RK method and the MC method. Comparing the results from both types of simulations is useful to verify the results

<img src="/Projects/Project5/Example_plot.png">

## Optimizations and dependencies
The program has paralellization with OpenMD where applicaple, and is by default compiled with -O3 compiler flags.

The library armadillo is used extensively for dealing with matrices and memory management.

Catch is used for testing.
