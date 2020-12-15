import os
import sys
import plot
import math
import matplotlib.pyplot as plt

from stats import StatModule


do_tests = False
do_compile = True
do_execute = True
do_plots = True

#TODO f independent of S in RK and MC? fixed vaccine rate independent of population?

mode = "getstd"

a = 4
b = 1
c = 0.5

S_0 = 300
I_0 = 100
R_0 = 0
N=S_0+I_0+R_0

t_0 = 0
t_n = 10
n_steps = 5000

e = 0.0#11
d = 0.0#1
dI = 0.0#1

f = 0#2
w = 2*math.pi
A = 0#4

f_BULK = 0 
vaccine_stock = 0

n_runs = 300

filename = mode+"_a_"+str(a)+"_b_"+str(b)+"_c_"+str(c)


args =mode+" "+filename+" "+str(a)+" "+str(b)+" "+str(c)+" "+str(S_0)+" "+str(I_0)+" "+str(R_0)+" "+str(t_0)+" "+str(t_n)+" "+str(n_steps)
args += " "+str(d) + " "+str(dI) + " "+str(e)
args += " "+str(f) + " "+str(w) + " "+str(A)
args += " "+str(f_BULK) + " "+str(vaccine_stock)
args += " "+str(n_runs)





#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./Projects/Project5/cpp_codes/*.cpp"
compiler_flags = "-larmadillo  -fopenmp" #Linker to Armadillo.
all_test_codes = "./Projects/Project5/tests/*.cpp"
test_includes = "-I./Projects/Project5/cpp_codes/"
main_cpp="./Projects/Project5/main.cpp"

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.

if do_tests:
        os.system("echo compiling tests...")
        os.system("g++ -o testmain.out" + " " + all_test_codes + " " + all_cpp_codes +  " "+ test_includes +" " + compiler_flags)
        os.system("echo executing tests...")
        os.system("./testmain.out")

if do_compile:

    os.system("echo compiling...")
    os.system("g++ -O3"+ " " + main_cpp + " " + all_cpp_codes + " " + compiler_flags + " -o main.out") #compile codes

if do_execute:
    os.system("echo executing...")
    os.system("./main.out" + " " +args) #Execute code


if do_plots:
    print("Creating plots...")
    if mode!="multiple":
        plotstatsMC = StatModule(a,b,c,d,dI,e,f,w,A)
        plotstatsMC.read_data("MC_solver_"+filename)
        plotstatsMC.plot_ISR()
        plotstatsMC.plot_IdI()


        plotstatsRK = StatModule(a,b,c,d,dI,e,f,w,A)
        plotstatsRK.read_data("RK_solver_"+filename)
        plotstatsRK.plot_ISR()
        plotstatsRK.plot_IdI()

        fig, ax1 = plt.subplots()
        ax2 = ax1.twinx()
        plotstatsMC.plot_ISR(fig=fig, ax1=ax1, ax2=ax2)
        plotstatsRK.plot_ISR(fig=fig, ax1=ax1,ax2=ax2, linestyle='dashed')
        plt.title("RK (dashed) and MC (line) disease development")
        plt.savefig("./Projects/Project5/Report/plots/Compare_"+filename+".png")

        plot.plot_std("MC_solver_"+filename,'I','Infected people','time','frequency','Infection statistics after steady state','I_SS',t_start=4)

    else:
        plot.plot_std("MC_solver_"+filename,'Peak[t]','Infection peak','time','frequency','Infection peak statstics','Peak_I')
        plot.plot_std("MC_solver_"+filename,'I_over[t]','Infection over','time','frequency','Infection over statistics','over_I')
    print("Plotting DONE")

    #plot.plot_SIR("RK_solver_"+filename,a,b,c,N,1,"simple")

    #plot.plot_SIR("MC_solver_"+filename,a,b,c,N,2,"vital")