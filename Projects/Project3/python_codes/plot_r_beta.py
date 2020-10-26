import plot_orbit

filenames=[]
legends=[]
folderpath="Projects/Project3/results/"

for i in range(9,10):
    legends.append("2."+str(i))

    filename = "beta2."+str(i)+"_n_100000_tn_30.0_GR_0_B_2."+str(i)+"0/earth_xyzt.txt"
    filenames.append(filename)

legends.append("2.95")
filenames.append("beta2.95_n_100000_tn_30.0_GR_0_B_2.95/earth_xyzt.txt")

legends.append("2.99")
filenames.append("beta2.99_n_100000_tn_30.0_GR_0_B_2.99/earth_xyzt.txt")

legends.append("2.999")
filenames.append("beta2.999_n_100000_tn_30.0_GR_0_B_2.99/earth_xyzt.txt")

legends.append("2.999")
filenames.append("beta2.9999_n_100000_tn_30.0_GR_0_B_2.99/earth_xyzt.txt")

#legends.append("3.0")
#filenames.append("beta3.0_n_100000_tn_30.0_GR_0_B_3.00/earth_xyzt.txt")

plot_orbit.plot_orbits(filenames,"r_beta","r_beta_9999.png",legends)