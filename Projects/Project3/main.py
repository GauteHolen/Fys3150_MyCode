import os
import sys


n=30
years=1
name = "earth_sun"


all_cpp_codes = "./Projects/Project3/cpp_codes_OO/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.

main_cpp="./Projects/Project3/main.cpp"

os.system("echo compiling...")
os.system("g++ -o main.out" + " " + main_cpp + " " + all_cpp_codes + " " + compiler_flags) #compile codes

os.system("echo executing n = "+str(n)+" , t_n = "+str(years)+" years...")
os.system("./main.out" + " " +str(n) + " " + str(years) + " " + name) #Execute code
