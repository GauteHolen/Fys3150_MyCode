import os
import sys


mode = "single"
L=2
temperature = 1
msc = 1000
random_start = 1 #1 is true, else is false


args = mode + " " + str(L) + " " +str(msc) + " " +str(random_start) + " " +str(temperature)

os.system("./main.out" + " " +args)