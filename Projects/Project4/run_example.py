import os
import sys

outfile = "testp4"

#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./Projects/Project4/lib/*.cpp"
lib_include = "-I./Projects/Project4/lib/"
compiler_flags = "-o3" #Linker to Armadillo.

main_cpp="./Projects/Project4/ising_2dim.cpp"

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.

os.system("echo compiling...")
os.system("g++ -o main.out" + " " + main_cpp + " "+all_cpp_codes + " " + lib_include ) #compile codes

os.system("echo executing...")
os.system("./main.out" + " " + outfile) #Execute code