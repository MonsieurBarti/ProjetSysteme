def syracuse(n):
    if n%2 ==0:
        n /= 2
    else:
        n = 3*n+1
    if n != 1:
        cpt+=1
        syracuse(n)
    else:
        return cpt+1

n=int(input ("entrez un nombre: "))
print(syracuse(n))