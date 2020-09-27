import os
import sys


#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./Projects/Project2/cpp_codes/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.
os.system("echo compiling...")
os.system("g++ -o main.out" + " " + all_cpp_codes + " " + compiler_flags) #compile codes
#You may replace the line above with os.system(" ".join(["g++", "-o main.out", all_cpp_codes, compiler_flags]))

os.system("echo executing...")
os.system("./main.out") #Execute code