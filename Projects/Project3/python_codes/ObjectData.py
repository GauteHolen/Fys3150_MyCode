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


    def plot_xyz(self, ax=None):

        if ax==None:
            fig=plt.figure()
            ax=ax = plt.axes(projection='3d')
            
        ax.scatter3D(self.x,self.y,self.z)
    
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