import os
import sys


mode = "single"
L=20
temperature = 1
msc = 1000
start_sampling = 150
random_start = 0 #1 is true, else is false


args = mode + " " + str(L) + " " +str(msc) + " " +str(start_sampling) + " " +str(random_start) + " " +str(temperature)

os.system("./main.out" + " " +args)