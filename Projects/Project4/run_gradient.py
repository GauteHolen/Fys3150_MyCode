import os
import sys

mode = "gradient"
start_T=2
end_T=2.6
T_steps=30

Ls=[40,60,80,100]
mcs=50000
random_start = 1 #1 is true, else is false

for L in Ls:
    args = mode+" "+str(L)+" "+str(mcs)+" "+str(random_start)+" "+str(start_T)+" "+str(end_T)+" "+str(T_steps)
    os.system("./main.out" + " " +args)