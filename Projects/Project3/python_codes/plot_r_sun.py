import plot_orbit

filenames=[]
legends=[]

legends.append("sun")
filenames.append("solar_system_n_2000_tn_30.0_GR_0_B_2.00/sun_xyzt.txt")

plot_orbit.plot_orbits(filenames,"sun zero momentum","sun_zero_momentum",legends)