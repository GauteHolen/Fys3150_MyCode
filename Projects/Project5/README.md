# Project 5: Disease modelling 
In this project, disease development in a population is modelled with a fourth order Runge-Kutta method and a Monte-Carlo simulation.

Please see the Report/Report.pdf for more details.

## How to run
The program is developed on Ubuntu 18.04.5 LTS in VS CODE.
The main python wrapper is using Python 3.8.3 with latest Anaconda 4.8.3.
The wrapper compiles with g++ 6.5.0 (2017).

There is a python wrapper called main.py, with all the input parameters for the initial conditions for the .cpp program which runs the simulations. Modify the input parameters in main.py directly to change the runs. Also use the "mode" parameter to differentiate different runs, to prevent overrides of data. 

When all the boleans do_tests, do_compile, do_execute and
do_plots are True, the wrapper will test, compile, execute, write to files and plot the relevant plots for the type of run.

<img src="/Projects/Project5/Python_wrapper.png">

Every run will trigger both the RK method and the MC method. Comparing the results from both types of simulations is useful to verify the results

<img src="/Projects/Project5/Example_plot.png">

## Optimizations and dependencies
The program has paralellization with OpenMD where applicaple, and is by default compiled with -O3 compiler flags.

The library armadillo is used extensively for dealing with matrices and memory management.

Catch is used for testing.

## Documentation and customization
The RK solver and MC solver funciton independently, and have docstrings describing functionality. 
Note that the initalizer methods are run first, then the solver methods, then the write to file methods.
By defauly the main.cpp prgram runs both RK and MC, but they can be setup to only run one by modifying or rewriting main.cpp.