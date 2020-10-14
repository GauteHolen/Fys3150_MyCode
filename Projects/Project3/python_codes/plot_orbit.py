from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

def plot_orbits(filenames,title,outfile,legend=None, plot_t=False):

    fig = plt.figure()
    ax = plt.axes(projection='3d')
    t_n=0
    n=0
    for filename in filenames:
        filename="Projects/Project3/results/"+filename
        infile = open(filename,'r')
        lines=infile.readlines()
        lines.pop(0)

        x=[]
        y=[]
        z=[]
        t=[]

        for line in lines:
            vals=line.split()
            x.append(float(vals[0]))
            y.append(float(vals[1]))
            z.append(float(vals[2]))
            t.append(float(vals[3]))

        if plot_t: 
            ax.scatter3D(x,y,t)
        else: 
            ax.scatter3D(x,y,z)
        n=len(x)
        t_n=t[n-1]


    if(legend!=None):
        plt.legend(legend)
    plt.title(title)

    if plot_t:
        z_label=("t")
        z_unit=" [years]"
    else:
        z_label=("z")
        z_unit = " [AU"
    
    ax.set_xlabel("x [AU]")
    ax.set_ylabel("y [AU]")
    ax.set_zlabel(z_label + z_unit)
    ax.text(0.0,0,1.2*t_n,"n = "+str(n))
    


    ofilename=outfile
    ofilename+="_n_"+str(n)
    ofilename+="_t_"+str(t_n)+"yrs"
    ofilename+="xy"+z_label

    
    #ax.view_init(60, 35)
    plt.savefig("./Projects/Project3/plots/"+ofilename+".png")


def main():
    plot_orbits(["vv_posE.txt","euler_posE.txt"],"Orbit of earth","Earth_Orbit",["verlet","euler"],plot_t=True)


def plot_system():
    plot_orbits(["earth_xyzt.txt","sun_xyzt.txt"],"solar system","Solar_system",["earth","sun"],plot_t=False)


plot_system()