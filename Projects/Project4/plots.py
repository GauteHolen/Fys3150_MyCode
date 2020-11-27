import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt

def plot_EM(T,filename):

    df = pd.read_csv(filename,sep='\t')

    E=df['E_i'].values.tolist()
    M=df['M_i'].values.tolist()

    EE=[E[0]]
    EM=[M[0]]
    t=[0]
    for i in range(1,len(E)):
        EE.append(sum(E[0:i])/i)
        EM.append(sum(M[0:i])/i)
        t.append(i)

    plt.figure(1)
    plt.title("mean Energy and Energy per step for T ="+str(T))
    plt.plot(t,E)
    plt.plot(t,EE)
    plt.legend(["E","E[E]"])
    plt.figure(2)
    plt.title("mean Mangetic moment and magnetic moment per step for T ="+str(T))
    plt.plot(t,M)
    plt.plot(t,EM)
    plt.legend(["M","E[M]"])
    plt.show()





#plot_EM(1,"Projects/Project4/results/EM_rng_0_mcs_1000_L_20_T_1.000000.txt")
plot_EM(2.4,"Projects/Project4/results/EM_rng_0_mcs_1000_L_20_T_2.400000.txt")
#plot_EM(1,"Projects/Project4/results/EM_rng_1_mcs_1000_L_20_T_1.000000.txt")
plot_EM(2.4,"Projects/Project4/results/EM_rng_1_mcs_1000_L_20_T_2.400000.txt")