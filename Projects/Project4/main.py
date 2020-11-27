import os
import sys

mode = "single"
L=2
temperature = 1
msc = 1000
start_sampling = 0
random_start = 1 #1 is true, else is false


args = mode + " " + str(L) + " " +str(msc)+ " " + str(start_sampling) + " " +str(random_start) + " " +str(temperature)

#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./Projects/Project4/cpp_codes/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.
all_test_codes = "./Projects/Project4/tests/*.cpp"
test_includes = "-I./Projects/Project4/cpp_codes/"
main_cpp="./Projects/Project4/main.cpp"

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.

os.system("echo compiling...")
os.system("g++ -O3 -fopenmp" + " " + main_cpp + " " + all_cpp_codes + " " + compiler_flags + " -o main.out") #compile codes

os.system("echo executing...")
os.system("./main.out" + " " +args) #Execute code