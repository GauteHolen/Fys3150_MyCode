from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

class ObjectData:
    def __init__(self,x,y,z,t,name):
        self.x = x
        self.y = y
        self.z = z
        self.t = t
        self.name = name
        self.t_n = t[len(t)-1]

        self.r = []
        self.n = len(self.x)
        for i in range(self.n):
            x=self.x[i]
            y=self.y[i]
            z=self.z[i]
            self.r.append(np.sqrt(x*x+y*y+z*z))

    def perihelion_precession(self,start_perihelion=False):

        if(start_perihelion==True):
            x_p=self.x[0]
        else:
            x_p=None

        for i in range(1,len(self.x)-1):
            if self.r[i]<self.r[i+1] and self.r[i]<self.r[i-1]:
                if(x_p==None):
                    x_p = self.x[i]
                
                y_p = self.x[i]
                print(y_p)

        theta = np.arctan(y_p/x_p)
        theta = np.rad2deg(theta)
        return [x_p,y_p,theta]



    def plot_xyz(self, ax=None):

        if ax==None:
            fig=plt.figure()
            ax=ax = plt.axes(projection='3d')
        
        if self.name.lower() == "sun":
            ax.scatter3D(self.x,self.y,self.z)

        ax.plot3D(self.x,self.y,self.z)
    
    def plot_xyt(self, ax=None):
        if ax==None:
            fig=plt.figure()
            ax=ax = plt.axes(projection='3d')
            
        ax.plot3D(self.x,self.y,self.t)

    def plot_r(self, ax=None):
        if ax==None:
            fig=plt.figure()
            ax=ax = plt.axes()


        ax.plot(self.t,self.r)

    def plot_xy(self, ax=None):
        if ax==None:
            fig=plt.figure()
            ax=ax = plt.axes()

        if self.name.lower() == "sun":
            ax.scatter(self.x,self.y)
        ax.plot(self.x,self.y)