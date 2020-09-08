import matplotlib.pyplot as plt
import pandas as pd


def plot_1b():
    data = pd.read_csv("./Projects/Project1/Results/fastest100n.txt", sep="\t", header=0)
    print(data.head())
    x=data['x']
    u=data['u']
    v=data['v']
    e=data['e']


    plt.plot(x,u)
    plt.plot(x,v)
    plt.ylabel("y")
    plt.xlabel("x")
    plt.title("fastest algoritm for u(x) and v(x) with n=1000")
    plt.legend(["u","v"])
    plt.savefig("./Projects/Project1/Plots/plot_fastest1000.png")


def plot_1d():
    data = pd.read_csv("./Projects/Project1/Results/max_e.txt", sep="\t", header=0)
    print(data.head())
    h=data['h']
    e=data['e_max']


    plt.plot(h,e)
    plt.ylabel("e_i")
    plt.xlabel("log10(h)")
    plt.title("Error as a function of log10(h)")
    plt.legend(["e_max"])
    plt.savefig("./Projects/Project1/Plots/e_max.png")


plot_1d()

