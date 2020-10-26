# Project 3: Solar system

## How to run

The non object oriented solvers for euler and verlet methods are found in the cpp_codes_nonOO folder. It has it's own python program for compilation and execution called run_non_object_oriented.py.

The object oriented solar system cpp files are found in the cpp_codes_OO folder. It is compiled and run by running main.py, creating exeutable main.out.

main.out has input parameters:
n(integration points)
t_n (number of years the simulation runs)

<img src="/Projects/Project3/screenshots/terminal_run.png">

## Program structure

The program consists of 2 classes, one called SolarSystem and one called Body. The SolarSystem has a vector containing each Body in the SolarSystem. 

For every time step h, the update() is called in the solarsystem, where the new position vectors for each body is found using the verlet method, until the program has run for the given number of years. The position vectors of each celestial body in the system is written to a .txt file in results.

## Finding Force of Gravity
The method get_Fg will actually account for gravitational contributions from every body in the system, not just Jupiter and Saturn. This is because it is quite interesting to see things like moons orbiting planets, binary planets (pluto and charon), trajectory/slingshots of probes, and list goes on. Everyone knows that things orbit the sun, but all the other subtleties of how gravity works between the other bodies in the system is what's interesting to me. As such, every gravitational contribution from every body on every body in the system is calculated.

## File structure
### Resulting position vectors
Each run of the main program will generate a folder in ./results/ which name indicates n and t_n, with one text file for each celestial body in the run containing the 4d (3d space, 1d time) position vectors at each integration point in the run. 

The position vectors txt files for each run have a dedicated folder in the folder results.

### Plots
Plots for each run are put in a generated unique folder, making plots for different runs easier to identify. 

