import os
import sys

mode = "gradient"
start_T=2
end_T=2.6
T_steps=30

#Ls=[40,60,80,100]
Ls=[40]
mcs=5000
start_sampling=mcs/5
random_start = 1 #1 is true, else is false

for L in Ls:
    args = mode+" "+str(L)+" "+str(mcs)+" "+str(start_sampling)+" "+str(random_start)+" "+str(start_T)+" "+str(end_T)+" "+str(T_steps)
    os.system("./main.out" + " " +args)