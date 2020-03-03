def syracuse(n):
    cpt=1
    while (n!=1):
        if n%2==0:
            n=n/2
            cpt+=1
        else:
            n=3*n+1
            cpt+=1
    print ("Nombre de valeurs:" , cpt)

if __name__ == '__main__':
    n=int(input ("entrez un nombre: "))
    syracuse(n)