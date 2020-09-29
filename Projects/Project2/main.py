import os
import sys

N = 10
algorithm="QDsingle"
p_max = 10

#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./Projects/Project2/cpp_codes/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.
all_test_codes = "./Projects/Project2/tests/*.cpp"
test_includes = "-I./Projects/Project2/cpp_codes/"
main_cpp="./Projects/Project2/main.cpp"

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.

os.system("echo compiling tests...")
os.system("g++ -o testmain.out" + " " + all_test_codes + " " + all_cpp_codes +  " "+ test_includes +" " + compiler_flags)
#You may replace the line above with os.system(" ".join(["g++", "-o main.out", all_cpp_codes, compiler_flags]))

os.system("echo executing tests...")
os.system("./testmain.out")

os.system("echo compiling...")
os.system("g++ -o main.out" + " " + main_cpp + " " + all_cpp_codes + " " + compiler_flags) #compile codes

os.system("echo executing...")
os.system("./main.out" + " " + str(N) + " " + algorithm + " " + str(p_max)) #Execute code