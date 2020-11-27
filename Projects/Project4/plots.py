import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt

def plot_EM(T,rng,filename):

    df = pd.read_csv(filename,sep='\t')

    E=df['E_i'].values.tolist()
    M=df['M_i'].values.tolist()
    A=df['A(t)'].values.tolist()

    EE=[E[0]]
    EM=[M[0]]
    EA=[A[0]]
    t=[0]
    for i in range(1,len(E)):
        EE.append(sum(E[0:i])/i)
        EM.append(sum(M[0:i])/i)
        EA.append(sum(A[0:i])/i)
        t.append(i)


    if(rng):
        rng_string="_rng1_"
    else:
        rng_string="_rng0_"

    plt.figure(1)
    plt.title("mean Energy and Energy per step for T ="+str(T))
    plt.plot(t,E)
    plt.plot(t,EE)
    plt.legend(["E","E[E]"])
    plt.xlabel("t")
    plt.ylabel("E")
    plt.savefig("./Projects/Project4/Plots/SingleT/Energy_T_"+str(T)+rng_string+".png")
    plt.figure(2)
    plt.title("mean Mangetic moment and magnetic moment per step for T ="+str(T))
    plt.plot(t,M)
    plt.plot(t,EM)
    plt.xlabel("t")
    plt.ylabel("M")
    plt.legend(["M","E[M]"])
    plt.savefig("./Projects/Project4/Plots/SingleT/Magnetic_T_"+str(T)+rng_string+".png")
    plt.figure(3)
    plt.plot(t,A)
    plt.plot(t,EA)
    plt.title("mean accepted configs and accepted configs per step for T = "+str(T))
    plt.xlabel("t")
    plt.ylabel("A(t)")
    plt.legend(["A","<A>"])
    plt.savefig("./Projects/Project4/Plots/SingleT/AConfigs_T_"+str(T)+rng_string+".png")





#plot_EM(1,"Projects/Project4/results/EM_rng_0_mcs_1000_L_20_T_1.000000.txt")
plot_EM(1,True,"Projects/Project4/results/EM_rng_1_mcs_1000_L_20_T_1.000000.txt")
plot_EM(1,False,"Projects/Project4/results/EM_rng_0_mcs_1000_L_20_T_1.000000.txt")
#plot_EM(1,"Projects/Project4/results/EM_rng_1_mcs_1000_L_20_T_1.000000.txt")
plot_EM(2.4,True,"Projects/Project4/results/EM_rng_1_mcs_1000_L_20_T_2.400000.txt")
plot_EM(2.4,False,"Projects/Project4/results/EM_rng_0_mcs_1000_L_20_T_2.400000.txt")