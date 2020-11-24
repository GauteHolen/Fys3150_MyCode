import math


e=math.e
J=1
T=100
k_b=1
B=1/(k_b*T)


Z=2*pow(e,8*J*B)+2*pow(e,-8*J*B)+12
EE=(16*J*pow(e,-8*B*J)-16*J*pow(e,8*B*J))/Z


print("Z = "+str(Z))
print("E[E] = "+str(EE))