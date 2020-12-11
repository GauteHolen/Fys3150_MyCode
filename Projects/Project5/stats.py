import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.offsetbox import AnchoredText
import cycler
from scipy.ndimage.filters import gaussian_filter1d
from scipy import signal

class StatModule:

    def __init__(self,a,b,c,d,dI,e,f,w,A):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.dI = dI
        self.e = e
        self.f = f
        self.w = w
        self.A = A

        if(e==0.0 and d==0.0 and dI==0.0):
            self.static_N=True
        else:
            self.static_N=False

        self.I = []
        self.R = []
        self.R = []
        self.D = []
        self.DI = []
        self.E = []
        self.N = []
        self.Vacc = []
        self.algo = ""
        self.filename = ""
        self.has_vacc = False
        self.has_I_zero = False
    
    def read_data(self,filename):
        path = "Projects/Project5/results/"+filename+".txt"
        self.filename=filename

        if(filename.split("_")[0]=="RK"):
            self.algo = "Runge-Kutta"
        elif(filename.split("_")[0]=="MC"):
            self.algo = "Monte Carlo"

        df = pd.read_csv(path,sep='\t')

        self.S=df['S'].values.tolist()
        self.I=df['I'].values.tolist()
        self.R=df['R'].values.tolist()
        self.t=df['t'].values.tolist()
        self.D=df['d'].values.tolist()
        self.DI=df['dI'].values.tolist()
        self.E=df['e'].values.tolist()
        self.Vacc = df['f'].values.tolist()
        if sum(self.Vacc)>0:
            self.has_vacc=True

        for i in range(len(self.S)):
            self.N.append(self.I[i]+self.R[i]+self.S[i])
            if self.I[i] == 0 and self.has_I_zero==False:
                self.t_I_zero = self.t[i]
                self.has_I_zero = True
                self.I_zero_index2 = int(i*2)

        if self.has_I_zero == True:
            i = int(self.I_zero_index2)
            self.S=self.S[0:i]
            self.I=self.I[0:i]
            self.R=self.R[0:i]
            self.t=self.t[0:i]
            self.D=self.D[0:i]
            self.DI=self.DI[0:i]
            self.E=self.E[0:i]
            self.Vacc=self.Vacc[0:i]
            self.N=self.N[0:i]
    
    def plot_ISR(self):

        n = 4
        color = plt.cm.Accent(np.linspace(0, n/12,n))
        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
        plt.figure()
        ax = plt.axes()
        #plt.title("Disease development over time")
        plt.plot(self.t,self.S)
        plt.plot(self.t,self.I)
        plt.plot(self.t,self.R)
        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
        
        legend=["Susceptible","Infected","Recovering"]
        if self.has_vacc:
            total_Vacc=[]
            total_Vacc.append(self.Vacc[0])
            for i in range(1,len(self.Vacc)):
                total_Vacc.append(total_Vacc[i-1]+self.Vacc[i])
            plt.plot(self.t,total_Vacc[0:len(self.t)])
            legend.append("Vaccinatations")
        
        if self.has_I_zero:
            plt.axvline(x=self.t_I_zero, ymin=0,ymax=1, color='grey', linestyle='dashed')
            legend.append("Infection over")

        plt.legend(legend)
        plt.ylabel("population")
        boxstr = '   '.join(('a = '+str(self.a),('b = '+str(self.b)),('c = '+str(self.c))))
        if(self.algo == "Monte Carlo"):
            plt.title("Disease development Monte Carlo\n"+boxstr)
            plt.xlabel("time")
        elif(self.algo == "Runge-Kutta"):
            plt.title("Disease development fourth order Runge-Kutta\n"+boxstr)
            plt.xlabel("time")
        
        if self.static_N:
            ES=self.b/self.a
            EI=(1-self.b/self.a)/(1+self.b/self.c)
            ER=(self.b/self.c)*(1-self.b/self.a)/(1+self.b/self.c)
            plt.axhline(y=self.N[0]*ES, color=color[0], linestyle='dashed')
            plt.axhline(y=self.N[0]*EI, color=color[1], linestyle='dashdot')
            plt.axhline(y=self.N[0]*ER, color=color[2], linestyle='dotted')

        plt.savefig("./Projects/Project5/Report/plots/"+self.filename+"_SIR.png")


    def plot_IdI(self):
        n_steps = len(self.N)
        window = round(n_steps*100/(50*self.t[n_steps-1]))
        if window%2==0:
            window+=1

        
        fig, ax1 = plt.subplots()
        #plt.title("Disease development over time")

        n = 8
        color = plt.cm.seismic(np.linspace(0, 1,n))
        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)

        total_DI=[]
        total_DI.append(self.DI[0])
        for i in range(1,len(self.DI)):
            total_DI.append(total_DI[i-1]+self.DI[i])

        ax1.plot(self.t,self.I, color=color[1])
        ax1.plot(self.t,total_DI, color=color[2])
        ax1.plot(self.t,self.N, color=color[3])
        ax1.tick_params(axis='y', labelcolor=color[1])
        ax1.set_ylabel("population per time", color=color[1])
        ax2 = ax1.twinx()

        dI = signal.savgol_filter(self.DI,window,1)
        d = signal.savgol_filter(self.D,window,1)
        e = signal.savgol_filter(self.E,window,1)

        

        ax2.plot(self.t,dI, color=color[6], linestyle='dashed')
        ax2.plot(self.t,d, color=color[5], linestyle='dashed')
        ax2.plot(self.t,e, color=color[4], linestyle='dashed')
        ax2.tick_params(axis='y', labelcolor=color[6])
        ax2.set_ylabel("avergeg population per time", color=color[6])


        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
        
        title = "Infection, death rates and birth ratess"
        title +="\n"
        title += '   '.join(('a = '+str(self.a),('b = '+str(self.b)),('c = '+str(self.c))))
        title +="\n"
        title += '   '.join(('e = '+str(self.e),('dI = '+str(self.dI)),('d = '+str(self.d))))
        ax1.set_xlabel("time")
        plt.title(title)
        fig.tight_layout()
        fig.legend(["Infected","Total infected deaths","Total population","Infected deaths rate","natural deaths rate","Birth rate"], loc='center')


        plt.savefig("./Projects/Project5/Report/plots/"+self.filename+"_IdI.png")


        