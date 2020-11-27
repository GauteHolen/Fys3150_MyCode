# Project 4: Metropolis algorithm and spins
I got an extention until the end of the week (Friday 27th)

## How to run
Compile and run by running main.py.
See python wrappers for running single or gradient mode run_single.py and run_gradient.py

The program runs in single temperature or temperature gradient mode. The first input argument of the program is either "gradient" or "single".

The rest of the input paramaters varies depending on the mode:

### Single temperature mode:
2) int L Lattice length (in LxL lattice)
3) int mcs Monte Carlo Cycles
4) random_spins, 1=true, else is false
5) temperature

### Temperature gradient mode:
2) int L Lattice length (in LxL lattice)
3) int mcs Monte Carlo Cycles
4) int random_spins, 1=true, else is false
5) double start_T
6) double final_T
7) int T_steps

There are python wrappers for running the different modes, however they need the program to be compiled first.


## Program structure
In order to gain insight into monte carlo simulations, there are mainly 2 objectives:
1) Running monte carlo simulations
2) getting values out of the monte carlo simulation
As such, there are two main classes in the program.
### Ising class
The Ising class, is the class running the simulations, based on the initial conditions. It then passes values to the Sampler class which will do statistics and write to files. 
### Sampler class
The Sampler class is "sampling" values from the simulations, and calculates statistics accordingly. The sampler starts receiving values after 1/5th of the cycles are done. What values are passed to the sampler can depend on what type of run it is.

## Parallell processes
When ran in temperature gradient mode, each temperature is a parallell process, running multiple temperatures simoultaneously for better speed using OpenMP