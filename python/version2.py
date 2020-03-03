def syracuse(n, cpt):
    if (n%2 == 0):
        n /= 2
    else:
        n = 3*n+1
    if (n != 1):
        syracuse(n, cpt+1)
    else:
        print("Nombre de valeurs: ", cpt+1)

if __name__ == '__main__':
    n=int(input ("entrez un nombre: "))
    syracuse(n, 1)