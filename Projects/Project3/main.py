import os
import sys

do_compile=True
do_tests=True

n=2000
years=30
name = "solar_system"
scenario = "solar_system"
beta = 2.0

#The optional arg might do different things for different scenarios
optional_arg = 1


all_cpp_codes = "./Projects/Project3/cpp_codes_OO/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.

main_cpp="./Projects/Project3/main.cpp"

all_test_codes = "./Projects/Project3/tests/*.cpp"
test_includes = "-I./Projects/Project3/cpp_codes_OO/"


if do_compile:

    if do_tests:
        os.system("echo compiling tests...")
        os.system("g++ -o testmain.out" + " " + all_test_codes + " " + all_cpp_codes +  " "+ test_includes +" " + compiler_flags)
        os.system("echo executing tests...")
        os.system("./testmain.out")

    os.system("echo compiling...")
    os.system("g++ -o main.out" + " " + main_cpp + " " + all_cpp_codes + " " + compiler_flags) #compile codes

os.system("echo executing n = "+str(n)+" , t_n = "+str(years)+" years...")
folderpath = os.system("./main.out" + " " +str(n) + " " + str(years) + " " + name + " " + scenario +" "+ "true" + " " + str(beta) + " " + str(optional_arg)) #Execute code
print(folderpath)

#os.system("echo creating plots for the system...")
#plot_system_from_folder
