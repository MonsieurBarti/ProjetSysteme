# Projet Système Syracuse
> Ce projet consiste à optimiser la conjecture de syracuse le plus possible à l'aide de threads et/ou processus

Table of Contents (up to date)
- [Projet Système Syracuse](#projet-syst%c3%a8me-syracuse)
- [Version 1 - Itératif](#version-1---it%c3%a9ratif)
- [Version 2 - Récursif](#version-2---r%c3%a9cursif)
- [Version 3 - Utilisation des threads](#version-3---utilisation-des-threads)
- [Version 4 - Utilisation des processus](#version-4---utilisation-des-processus)

# Version 1 - Itératif
```python
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
```
# Version 2 - Récursif
```C
    int syracuse(int n) {
        int cpt;
        if(n % 2 == 0) {
            n /= 2;
        } else {
            n = 3*n+1;
        }
        if(n != 1) {
            cpt += 1;
            syracuse(n);
        } else {
            return cpt;
    }
}
```
# Version 3 - Utilisation des threads

# Version 4 - Utilisation des processus

