import os
import sys

verlet_velocity = "./Projects/Project3/cpp_codes/verlet_velocity.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.


os.system("echo compiling...")
os.system("g++ -o main.out" + " " + verlet_velocity +" " + compiler_flags) #compile codes

os.system("echo executing...")
os.system("./main.out") #Execute code