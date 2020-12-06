import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt

def plot(filename,a,b,c,N):

    path = "Projects/Project5/results/"+filename+".txt"


    df = pd.read_csv(path,sep='\t')

    S=df['S'].values.tolist()
    I=df['I'].values.tolist()
    R=df['R'].values.tolist()
    t=df['t'].values.tolist()

    ES=b/a
    EI=(1-b/a)/(1+b/c)
    ER=(b/c)*(1-b/a)/(1+b/c)




    plt.figure(1)
    plt.title("Disease development over time")
    plt.plot(t,S, color='b')
    plt.plot(t,I, color = 'r')
    plt.plot(t,R, color = 'g')
    plt.axhline(y=N*ES, color='b', linestyle='dashed')
    plt.axhline(y=N*EI, color='r', linestyle='dotted')
    plt.axhline(y=N*ER, color='g', linestyle='dashdot')
    plt.legend(["S","I","R"])
    plt.ylabel("population")
    plt.xlabel("time")
    plt.savefig("./Projects/Project5/plots/"+filename+".png")
    