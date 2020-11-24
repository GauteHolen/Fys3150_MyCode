import os
import sys

L=2
temperature = 1
msc = 100


args = str(L) + " " +str(temperature) + " " +str(msc)

#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./Projects/Project4/cpp_codes/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.
all_test_codes = "./Projects/Project4/tests/*.cpp"
test_includes = "-I./Projects/Project4/cpp_codes/"
main_cpp="./Projects/Project4/main.cpp"

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.

print(args)

os.system("echo compiling...")
os.system("g++ -o main.out" + " " + main_cpp + " " + all_cpp_codes + " " + compiler_flags) #compile codes

os.system("echo executing...")
os.system("./main.out" + " " +args) #Execute code