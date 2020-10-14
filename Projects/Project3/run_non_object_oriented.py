import os
import sys

n=1000
years=5

verlet_velocity = "./Projects/Project3/cpp_codes_nonOO/verlet_velocity.cpp"
euler = "./Projects/Project3/cpp_codes_nonOO/euler.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.


os.system("echo compiling verlet velocity...")
os.system("g++ -o vv_main.out" + " " + verlet_velocity +" " + compiler_flags) #compile codes

os.system("echo executing verlet velocity...")
os.system("./vv_main.out" + " " +str(n) + " " + str(years)) #Execute code

os.system("echo compiling euler...")
os.system("g++ -o euler_main.out" + " " + euler +" " + compiler_flags) #compile codes

os.system("echo executing euler...")
os.system("./euler_main.out" + " " +str(n) + " " + str(years)) #Execute code