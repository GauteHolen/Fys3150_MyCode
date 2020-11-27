import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt
from operator import itemgetter

def plot_gradient(filenames):

    plt.close()

    path="Projects/Project4/results/"


    for filename in filenames:

        df = pd.read_csv(path+filename+".txt",sep='\t')
        T=df['T'].values.tolist()
        EE=df['E[E]'].values.tolist()
        EM=df['E[M]'].values.tolist()
        X=df['X'].values.tolist()
        CV=df['CV'].values.tolist()

        L = sorted(zip(T,EE,EM,X,CV), key=itemgetter(0))
        _T,_EE,_EM,_X,_CV, = zip(*L)

        _EM =  [abs(ele) for ele in _EM] 
        
        plt.figure(1)
        plt.plot(_T,_CV)
        plt.figure(2)
        plt.plot(_T,_X)
        plt.figure(3)
        plt.plot(_T,_EE)
        plt.figure(4)
        plt.plot(_T,_EM)
    
    plt.figure(1)
    plt.title("Specific heat as function of temperarure")
    plt.xlabel("t")
    plt.ylabel("CV")
    plt.legend(["L = 40","L = 60","L = 80","L = 100"])

    plt.figure(2)
    plt.title("Susceptibility as function of temperarure")
    plt.xlabel("t")
    plt.ylabel("X")
    plt.legend(["L = 40","L = 60","L = 80","L = 100"])

    plt.figure(3)
    plt.title("Mean energy as function of temperarure")
    plt.xlabel("t")
    plt.ylabel("<E>")
    plt.legend(["L = 40","L = 60","L = 80","L = 100"])

    plt.figure(4)
    plt.title("Mean magnetic moment as function of temperarure")
    plt.xlabel("t")
    plt.ylabel("<|M|>")
    plt.legend(["L = 40","L = 60","L = 80","L = 100"])
    
    plt.show()

files1=[]
files1.append("T_gradient_2.000000-3.000000_L_40_mcs_10000")
files1.append("T_gradient_2.000000-3.000000_L_60_mcs_10000")
files1.append("T_gradient_2.000000-3.000000_L_80_mcs_10000")
files1.append("T_gradient_2.000000-3.000000_L_100_mcs_10000")

files2=[]
files2.append("T_gradient_2.000000-3.000000_L_40_mcs_1000")
files2.append("T_gradient_2.000000-3.000000_L_60_mcs_1000")
files2.append("T_gradient_2.000000-3.000000_L_80_mcs_1000")
files2.append("T_gradient_2.000000-3.000000_L_100_mcs_1000")

files3=[]
files3.append("T_gradient_2.000000-2.600000_L_40_mcs_50000")
files3.append("T_gradient_2.000000-2.600000_L_60_mcs_50000")
files3.append("T_gradient_2.000000-2.600000_L_80_mcs_50000")
files3.append("T_gradient_2.000000-2.600000_L_100_mcs_50000")

plot_gradient(files3)