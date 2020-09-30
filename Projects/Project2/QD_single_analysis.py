import matplotlib.pyplot as plt


def get_eigenvalues(N,p_max):

    filename="Projects/Project2/resulsts/QDsingle_N_"+str(N)+"_pmax_"+str(p_max)+".000000.txt"
    infile = open(filename,'r')
    lines=infile.readlines()

    eigval = []
    for i in range(5):
        eigval.append(float(lines[13+i].split("\t")[0]))
    infile.close()

    return eigval

def main():
    
    N=[10,50,100]
    p_max=[1,5,10,50]
    actualEigvals=[3,7,11,15,19]
    errors=[[],[],[]]

    k=0
    for n in N:
        for p in p_max:
            eigvals=get_eigenvalues(n,p)
            error=0
            for i in range(len(eigvals)):
                print(eigvals)
                error+=abs(eigvals[i]-actualEigvals[i])/5
            errors[k].append(error)
        k+=1
    
    plt.plot(p_max,errors[0])
    plt.plot(p_max,errors[1])
    plt.plot(p_max,errors[2])
    plt.legend(["N=10","N=50","N=100"])
    plt.yscale('log')
    plt.xscale('log')
    plt.xlabel("p_max")
    plt.ylabel("avg error")
    
    
    plt.savefig("./Projects/Project2/plots/QD_single.png")
    print(errors)

    
    


main()
