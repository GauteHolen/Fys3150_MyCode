# Project 3: Solar system

## How to run

The non object oriented solvers for euler and verlet methods are found in the cpp_codes_nonOO folder. It has it's own python program for compilation and execution called run_non_object_oriented.py.

The object oriented solar system cpp files are found in the cpp_codes_OO folder. It is compiled and run by running main.py, creating exeutable main.out.

main.out has input parameters:
    
    int n(integration points)
    double t_n (number of years the simulation runs)
    string name (the name of the run, which will determine the name of the output folder)
    string scenario
    string GR (if "true" then accounts for general relativity)
    double beta (changes from 2-3 to have different force of gravity)
    optional_arg (in case any scenario has additional args)

All these parameters can be set in main.py before running. When running through the python wrapper in main.py, the terminal will look like this.

<img src="/Projects/Project3/screenshots/terminal_run.png">

## Scenarios
The program will construct different scenarios automatically:

### earth_sun
This is the default scenario, and constructs the earth sun system with a static sun.

### mercury
This scenario constructs the earth mercury system and is used to explore the perihelion precession of mercury with relativity.

### escape
This scenario will construct many earth-like bodies with different velocities used to study escape velocity.

### 3body
This scenario will construct the earth, sun and jupiter system, with various masses of jupiter through the optional input argument. This scenario is used to study how jupiter's mass will change the orbit of the earth.

### solar_system
This scenario will add planets, and then add the sun with a position and velocity so that the center of mass remains at the origin, and so that the angular momentum of the system remains zero.

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

