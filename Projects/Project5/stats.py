import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.offsetbox import AnchoredText
import cycler
import bottleneck as bn


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

        self.max_I = max(self.I)
        self.max_I_index=self.I.index(self.max_I)

        for i in range(len(self.S)):
            self.N.append(self.I[i]+self.R[i]+self.S[i])
            if self.I[i] <= 0.99 and self.has_I_zero==False:
                self.t_I_zero = self.t[i]
                self.has_I_zero = True
                self.I_zero_index2 = int(i*1.3)

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
    
    def plot_ISR(self, fig=None, ax1=None, ax2=None, linestyle='-'):

        if fig==None:
            multifig=False
        else:
            multifig=True
        

        n = 8
        color = plt.cm.Accent(np.linspace(0, n/8,n))
        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
        if fig==None:
            fig, ax1 = plt.subplots()
            if self.has_vacc:
                 ax2 = ax1.twinx()
                
        #plt.title("Disease development over time")
        ax1.plot(self.t,self.I, color=color[0], linestyle=linestyle)
        ax1.plot(self.t,self.S, color=color[1], linestyle=linestyle)
        ax1.plot(self.t,self.R,  color=color[2], linestyle=linestyle)

        legend=["I","S","R"]

        ax1.axvline(x=self.t[self.max_I_index], ymin=0,ymax=1, color='green', linestyle=linestyle)
        legend.append("I$_{peak}$")
        
        if self.has_vacc:
            total_Vacc=[]
            total_Vacc.append(self.Vacc[0])
            for i in range(1,len(self.Vacc)):
                total_Vacc.append(total_Vacc[i-1]+self.Vacc[i])
            ax2.plot(self.t,total_Vacc[0:len(self.t)], color=color[4], linestyle=linestyle)

            
            legend.append("$V_{total}$")
            ax2.set_ylabel("Vaccinations", color=color[4])
            ax2.tick_params(axis='y', labelcolor=color[4])

        
        if self.has_I_zero:
            ax1.axvline(x=self.t_I_zero, ymin=0,ymax=1, color='grey', linestyle=linestyle)
            legend.append("I$_{zero}$")


        
        ax1.set_ylabel("population")
        boxstr = '   '.join(('a = '+str(self.a),('b = '+str(self.b)),('c = '+str(self.c))))
        if(self.algo == "Monte Carlo"):
            plt.title("Disease development Monte Carlo\n"+boxstr)
            
        elif(self.algo == "Runge-Kutta"):
            plt.title("Disease development fourth order Runge-Kutta\n"+boxstr)
            
        ax1.set_xlabel("time")

        if self.static_N:
            ES=self.b/self.a
            EI=(1-self.b/self.a)/(1+self.b/self.c)
            ER=(self.b/self.c)*(1-self.b/self.a)/(1+self.b/self.c)
            ax1.axhline(y=self.N[0]*ES, color=color[1], linestyle='dashed')
            ax1.axhline(y=self.N[0]*EI, color=color[0], linestyle='dashdot')
            ax1.axhline(y=self.N[0]*ER, color=color[2], linestyle='dotted')

        fig.legend(legend, loc=(0.74,0.33))
        
        if multifig==False:
            plt.savefig("./Projects/Project5/Report/plots/"+self.filename+"_SIR.png")


    def plot_IdI(self, fig=None, ax1=None):

        #TODO FIX the stupid filter on the birth/death rates

        n_steps = len(self.N)
        window = round(n_steps/self.t[len(self.t)-1])

        
        fig, ax1 = plt.subplots()
        #plt.title("Disease development over time")

        n = 8
        color = plt.cm.seismic(np.linspace(0, 1,n))
        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)

        total_DI=[]
        total_DI.append(self.DI[0])
        for i in range(1,len(self.DI)):
            total_DI.append(total_DI[i-1]+self.DI[i])

        ax2 = ax1.twinx()

        #dI = self.DI; 
        steps_per_t=n_steps/self.t[len(self.t)-1]
        if self.algo == "Runge-Kutta":
            dI = self.DI
            d = self.D
            e = self.E
        else:
            dI=[self.DI[0]]
            d=[self.D[0]]
            e=[self.E[0]]
            for i in range(1,len(self.DI)):
                dI.append((self.DI[i]+dI[i-1]))
                d.append((self.D[i]+d[i-1]))
                e.append((self.E[i]+e[i-1]))
            for i in range(1,len(dI)):
                dI[i]=dI[i]/i
                d[i]=d[i]/i
                e[i]=e[i]/i
        for i in range(len(dI)):
            dI[i]=dI[i]*steps_per_t
            d[i]=d[i]*steps_per_t
            e[i]=e[i]*steps_per_t
        window=int(steps_per_t/5)
        dI=bn.move_mean(dI,window,min_count=window)
        d=bn.move_mean(d,window,min_count=window)
        e=bn.move_mean(e,window,min_count=window)

        ax2.plot(self.t,dI, color=color[6], linestyle='dotted')
        ax2.plot(self.t,d, color=color[5], linestyle='dotted')
        ax2.plot(self.t,e, color=color[4], linestyle='dotted')
        ax2.tick_params(axis='y', labelcolor=color[6])
        ax2.set_ylabel("rate", color=color[6])

        ax1.plot(self.t,self.I, color='green')
        ax1.plot(self.t,total_DI, color=color[2])
        ax1.plot(self.t,self.N, color=color[3])
        ax1.tick_params(axis='y', labelcolor=color[1])
        ax1.set_ylabel("total", color=color[1])
        #ax2.set_ylim(0,1)

        legend = ["I","$d_{Itotal}$","N","$d_I$","d","e"]

        if self.has_I_zero:
            plt.axvline(x=self.t_I_zero, ymin=0,ymax=1, color='grey', linestyle='dashed')
            legend.append("$I_{zero}$")

        plt.axvline(x=self.t[self.max_I_index], ymin=0,ymax=1, color='green', linestyle='dashed')
        legend.append("$I_{peak}$")


        mpl.rcParams['axes.prop_cycle'] = cycler.cycler('color', color)
        
        title = "Infection, death rates and birth ratess"
        title +="\n"
        title += '   '.join(('a = '+str(self.a),('b = '+str(self.b)),('c = '+str(self.c))))
        title +="\n"
        title += '   '.join(('e = '+str(self.e),('dI = '+str(self.dI)),('d = '+str(self.d))))
        ax1.set_xlabel("time")
        plt.title(title)
        fig.tight_layout()
        fig.legend(legend, loc=(0.70,0.33))


        plt.savefig("./Projects/Project5/Report/plots/"+self.filename+"_IdI.png")


        