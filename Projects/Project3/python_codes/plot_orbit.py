from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt
from ObjectData import ObjectData
import os

def plot_xy(bodies,legend,title,outfile,perihelion=""):
    fig = plt.figure()
    ax = plt.axes()

    for body in bodies:
        body.plot_xy(ax)
        if(perihelion==body.name):
            print("calculating perihelion of "+body.name)
            [xp,yp,theta] = body.perihelion_precession(start_perihelion=True)
            p_str = "x_p = "+str(round(xp,6)) +"\n"
            p_str += "y_p = "+str(round(yp,6)) +"\n"
            p_str += "theta = "+str(round(theta,6)) +"\n"
            ax.text(-0.1,0.05,p_str)
    
    if(legend!=None):
        plt.legend(legend)

    plt.title("xy-plane for '"+title+"'")
    ax.set_xlabel("x [AU]")
    ax.set_ylabel("y [AU]")
    ax.text(1,1,"n = "+str(bodies[0].n))

    file_path="./Projects/Project3/plots/"+outfile+"_plots"
    if os.path.exists(file_path) == False:
        os.mkdir("./Projects/Project3/plots/"+outfile+"_plots")

    plt.savefig("./Projects/Project3/plots/"+outfile+"_plots/"+"xy"+".png")


def plot_r(bodies,legend,title,outfile):
    fig = plt.figure()
    ax = plt.axes()

    for body in bodies:
        body.plot_r(ax)
    
    if(legend!=None):
        plt.legend(legend)

    plt.title("r with respect to time in '"+title+"'")
    ax.set_xlabel("time [years]")
    ax.set_ylabel("r [AU]")
    ax.text(1,1,"n = "+str(bodies[0].n))

    file_path="./Projects/Project3/plots/"+outfile+"_plots"
    if os.path.exists(file_path) == False:
        os.mkdir("./Projects/Project3/plots/"+outfile+"_plots")

    plt.savefig("./Projects/Project3/plots/"+outfile+"_plots/"+"rt"+".png")




def plot_xyz(bodies,legend,title,outfile):
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    for body in bodies:
        body.plot_xyz(ax)

    if(legend!=None):
        plt.legend(legend)
    plt.title("x, y and z positions for the bodies in '"+title+"'")
    ax.set_xlabel("x [AU]")
    ax.set_ylabel("y [AU]")
    ax.set_zlabel("z [AU]")
    ax.text(0.0,0,0.4,"n = "+str(bodies[0].n))

    file_path="./Projects/Project3/plots/"+outfile+"_plots"
    if os.path.exists(file_path) == False:
        os.mkdir("./Projects/Project3/plots/"+outfile+"_plots")

    plt.savefig("./Projects/Project3/plots/"+outfile+"_plots/"+"xyz"+".png")



def plot_xyt(bodies,legend,title,outfile):
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    for body in bodies:
        body.plot_xyt(ax)

    if(legend!=None):
        plt.legend(legend)
    plt.title("'"+title+"' xy-plane with respect to time")
    ax.set_xlabel("x [AU]")
    ax.set_ylabel("y [AU]")
    ax.set_zlabel("time [years]")
    ax.text(0.0,0,1.2*bodies[0].t_n,"n = "+str(bodies[0].n))

    file_path="./Projects/Project3/plots/"+outfile+"_plots"
    if os.path.exists(file_path) == False:
        os.mkdir("./Projects/Project3/plots/"+outfile+"_plots")

    plt.savefig("./Projects/Project3/plots/"+outfile+"_plots/"+"xyt"+".png")

def escape_velocity(filename):
    infile = open("Projects/Project3/results/"+filename)
    lines=infile.readlines()
    lines.pop(0)

    less=False
    x_i=0
    x_old=0
    for line in lines:
        vals=line.split()
        x_i=float(vals[0])
        if(x_i<x_old):
            print("Less than escape velocity")
            less=True
            break
        else:
            x_old=x_i
    if(less==False):
        print("more than escape velocity")




def plot_orbits(filenames,title,outfile,legend=None, plot_t=False):


    bodies=[]
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
        
        name=filename.split("/")[-1].split("_xyzt")[0]

        bodies.append(ObjectData(x,y,z,t,name))

    n=bodies[0].n
    t_n=bodies[0].t_n

    outfile+="_n_"+str(n)
    outfile+="_t_"+str(t_n)+"yrs"

    plot_r(bodies,legend,title,outfile)
    plot_xyz(bodies,legend,title,outfile)
    plot_xyt(bodies,legend,title,outfile)
    plot_xy(bodies,legend,title,outfile,perihelion="mercury")
    


def main():
    plot_orbits(["vv_posE.txt","euler_posE.txt"],"Orbit of earth","Earth_Orbit",["verlet","euler"],plot_t=True)


def plot_system():
    plot_orbits(["earth_xyzt.txt","sun_xyzt.txt"],"solar system","Solar_system",["earth","sun"],plot_t=False)

def plot_system_from_folder(foldername):
    paths=os.listdir("Projects/Project3/results/"+foldername)
    name=foldername.split("_n_")[0].replace("_"," ")

    legends=[]
    files=[]
    for file in paths:
        if "_xyzt" in file:
            legends.append(file.split("/")[-1].split("_xyzt")[0])
            files.append(foldername+"/"+file.split("/")[-1])
        

    plot_orbits(files,name,foldername,legend=legends)



plot_system_from_folder("beta3.0_n_100000_tn_30.0_GR_0_B_3.00")

