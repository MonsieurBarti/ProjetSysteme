def syracuse():
    n=int(input ("entrez un nombre: "))
    compteur=1
    while (n!=1):
    if n%2==0:
        n=n/2
        compteur=compteur+1
    else:
        n=3*n+1
        compteur=compteur+1
    print ("Nombre de valeurs:" , compteur)