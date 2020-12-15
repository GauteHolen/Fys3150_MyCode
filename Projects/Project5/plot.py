import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.offsetbox import AnchoredText
import cycler

def plot_SIR(filename,a,b,c,N,nfig,scenario):

    path = "Projects/Project5/results/"+filename+".txt"

    mode = ""

    if(filename.split("_")[0]=="RK"):
        mode = "Runge-Kutta"

    elif(filename.split("_")[0]=="MC"):
        mode = "Monte Carlo"



    df = pd.read_csv(path,sep='\t')

    S=df['S'].values.tolist()
    I=df['I'].values.tolist()
    R=df['R'].values.tolist()
    t=df['t'].values.tolist()
    

    ES=b/a
    EI=(1-b/a)/(1+b/c)
    ER=(b/c)*(1-b/a)/(1+b/c)

    if(scenario!="simple"):
        Nt=[]
        ESt=[]
        EIt=[]
        ERt=[]
        for i in range(len(S)):
            Nt.append(S[i]+I[i]+R[i])
            ESt.append(Nt[i]*ES)
            EIt.append(Nt[i]*EI)
            ERt.append(Nt[i]*ER)



    #color = plt.cm.get_cmap(name='Set3')

    n = 3
    color = plt.cm.Accent(np.linspace(0, n/12,n))
    mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
    plt.figure(nfig)
    ax = plt.axes()
    #plt.title("Disease development over time")
    plt.plot(t,S)
    plt.plot(t,I)
    plt.plot(t,R)
    mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
    if scenario=="simple":
        plt.axhline(y=N*ES, color=color[0], linestyle='dashed')
        plt.axhline(y=N*EI, color=color[1], linestyle='dashdot')
        plt.axhline(y=N*ER, color=color[2], linestyle='dotted')
    #else:
        #plt.plot(t,ESt, color=color[0], linestyle='dashed')
        #plt.plot(t,EIt, color=color[1], linestyle='dashdot')
        #plt.plot(t,ERt, color=color[2], linestyle='dotted')
        
    #ax.set_xscale('log')
    plt.legend(["Susceptible","Infected","Recovering"])
    plt.ylabel("population")
    boxstr = '     '.join(('a = '+str(a),('b = '+str(b)),('c = '+str(c))))
    if(mode == "Monte Carlo"):
        plt.title("Disease development Monte Carlo\n"+boxstr)
        plt.xlabel("MC cycles")
    elif(mode == "Runge-Kutta"):
        plt.title("Disease development fourth order Runge-Kutta\n"+boxstr)
        plt.xlabel("time")
    
    plt.savefig("./Projects/Project5/Report/plots/"+filename+".png")
    

def plot_std(filename, columnname, label, xlabel, ylabel, title, outfile, t_start=None):
    path = "Projects/Project5/results/"+filename+".txt"
    df = pd.read_csv(path,sep='\t')
    
    data=df[columnname].values.tolist()
    data = [x for x in data if str(x) != 'nan']

    textstr = ''

    if t_start!=None:
        t = df['t'].values.tolist()
        N=len(data)
        index_start = 0
        for i in range(N):
            if t[i] > t_start:
                index_start = i
                break
        data=data[index_start:N-1]
        textstr+='$t_0$='+str(t_start)+'\n'
        textstr+='MC cycles='+str(N-index_start)+'\n'
        outfile+='_mcs_'+str(N-index_start)


    fig1, ax1 = plt.subplots()
    ax1.hist(data, density=True, bins=30, label=label)
    mean = np.mean(data)
    ax1.axvline(mean, color='black', linestyle = 'dashed', label='mean')
    std = np.std(data)
    ax1.axvline(mean+std, color='black', linestyle = 'dotted', label='1 std')
    ax1.axvline(mean-std, color='black', linestyle = 'dotted')
    plt.legend(loc='upper left')
    ax1.set_xlabel(xlabel)
    ax1.set_ylabel(ylabel)

    textstr += '\n'.join((
    r'$\mu=%.2f$' % (mean, ),
    r'$\sigma=%.2f$' % (std, )))
    # these are matplotlib.patch.Patch properties
    props = dict(boxstyle='round', facecolor='white', alpha=0.5)

    # place a text box in upper left in axes coords
    ax1.text(0.65, 0.95, textstr, transform=ax1.transAxes, fontsize=11,
            verticalalignment='top', bbox=props)
    plt.title(title)
    
    plt.savefig("./Projects/Project5/Report/plots/"+filename+outfile+".png")
