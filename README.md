# Projet Système Syracuse

> Ce projet consiste à optimiser la conjecture de syracuse le plus possible à l'aide de threads et/ou processus

Table of Contents (up to date)
- [Projet Système Syracuse](#projet-syst%c3%a8me-syracuse)
- [Version 1 - Itératif](#version-1---it%c3%a9ratif)
- [Version 2 - Récursif](#version-2---r%c3%a9cursif)
- [Version 3 - Utilisation des threads](#version-3---utilisation-des-threads)
- [Version 4 - Utilisation des processus](#version-4---utilisation-des-processus)
- [Parties Personnelles - Arnaud](#-Parties-Personnelles---Arnaud)

# Version 1 - Itératif
Code en C
```C
int syracuse(int n) {
    int cpt = 1;
    while (n != 1) {
        if (n%2 == 0) {
            n=n/2;
            cpt++;
        } else {
            n=3*n+1;
            cpt++;
        }
    }
    return cpt;
}
```
Code en python
```python
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
```
# Version 2 - Récursif
Code en C
```C
int syracuse(int n, int cpt) {
    if(n % 2 == 0) {
        n /= 2;
    } else {
        n = 3*n+1;
    }
    if(n != 1) {
        syracuse(n, cpt+1);
    } else {
        return cpt+1;
    }
}
```
Code en python
```python
def syracuse(n, cpt):
    if (n%2 == 0):
        n /= 2
    else:
        n = 3*n+1
    if (n != 1):
        syracuse(n, cpt+1)
    else:
        print("Nombre de valeurs: ", cpt+1)
```
# Version 3 - Utilisation des threads

# Version 4 - Utilisation des processus

# Parties Personnelles - Arnaud
Le premier obstacle que j'ai rencontré, c'était la limitation par la mémoire. 

En effet j'ai commencé par initialiser un tableau de 3000 cases. Mais si l'algorithme depassais la valeur de 3000 alors j'obtenais l'erreur "segmentation fault". J'ai donc décidé de faire une allocation de mémoire dynamique en utilisant calloc et realloc.

J'initialise un tableau avec calloc et si je me rends compte que j'ai besoin de plus de place alors j'augmente la taille avec realloc.

J'ai décidé d'utiliser calloc au lieu de malloc, car je voulais pouvoir tester si j'avais deja remplis une case du tableau ou non. Si la valeur est à 0 alors cela signifie que je n'ai pas effectué se calcule.

Voici un extrait du programme Allocation_dynamique.c :
```C
int main(int argc, char *argv[]){
	tableau_suivant=calloc(taille, sizeof(long));
	tableau_profondeur=calloc(taille, sizeof(long));
	while(boucle){
		profondeur=0;
		printf("Nombre de départ :");
		scanf("%ld",&debut);
		if(debut!=-1){
			val=debut;
			while(val!=1){
				if(val>taille){
					taille=val+1;
					tableau_suivant = realloc(tableau_suivant, taille * sizeof(long));
					tableau_profondeur = realloc(tableau_profondeur, taille * sizeof(long));
				}
```

Le deuxième obstacle que j'ai rencontré, c'était le fait que je n'utilisais pas les calculs réalisés avant pour diminuer le nombre de calcul. 

Exemple, si je calculais 18 puis ensuite 19, les deux contiennent la valeur 22, et bien j'allais calculer l'intégralité des calcul que j'avais déjà effectué. 

Pour regler ce problème, avant d'effectuer un calcule je vérifie si la valeur n'a pas déjà été calculé puis je remplis dans le tableau.

Voici un extrait du programme Utilisation_du_tableau.c :

```C
				if(tableau_profondeur[val]!=0){
					profondeur=profondeur+tableau_profondeur[val]-1;
					val=1;
					printf("Je connais deja la profondeur ");
				}else{
					if(tableau_suivant[val]!=0){
						val=tableau_suivant[val];
						printf("Je connais deja la valeur ");
					}else{
						suivant=calc(val);
						tableau_suivant[val]=suivant;
						val=suivant;
						printf("Je connais rien ");
					}
				}
```
Le troisième obstacle, c'était le fait que quand je calculais la conjecture de syracuse, j'allais noter le nombre de calcul effectué pour un nombre mais pas pour tous les nombres par lequel je suis passé. 

Exemple si je calcule pour 16, je vais retenir que le nombre de calcul est de 5, mais je ne vais pas retenir le nombre de calcul nécessaire pour les nombres par lesquels je suis passé.

Pour réussir cela, j'ai effectué un programme récursif qui rentre dans le tableau la profondeur de chaque nombre par lequel on passe pour obtenir la profondeur du nombre de départ

Voici un extrait du programme Recursive.c : 

```C
long fonc_recursive(long nombre){
	if(nombre!=1){
		if(nombre>taille){
				taille=nombre+1; 
				tableau_profondeur = realloc(tableau_profondeur, taille * sizeof(long));
			}

			printf("Pour : %ld ",nombre);

			if(tableau_profondeur[nombre]!=0){
				printf("Je connais deja la profondeur \n");
			}else{
				printf("Je connais rien \n");
				long ma_profondeur;
				ma_profondeur=fonc_recursive(calc(nombre));
				tableau_profondeur[nombre]=ma_profondeur;
			}
			return tableau_profondeur[nombre]+1;
	}else{
		return 0;
	}
}

```

Pour finir, l'objectif final était de paralléliser le calcule de la conjoncture de syracus. 

J'ai donc décidé d'utiliser les threads afin de pouvoir effectuer plusieurs conjoncures en même temps. Dans ce programme, je me suis limité à deux threads, mais il serai bien sûr possible d'augmenter le nombre de threads. 

En utilisant le programme Utilisation_de_threads.c si on choisi de faire une conjoncture de Syracus avec 549 et 2, on verra bien que les deux threads fonctionnent en parralèlle car le programme va commencer en premier par calculer la conjoncture de 549. Mais le résultat de la conjoncture de 2 apparaîtra en premier car son nombre de calculs est bien plus court.

Afin de pouvoir travailler ensemble, les threads partage un tableau commun contenant tous les resultats de leurs calculs.

Extrait du programme Utilisation_de_threads.c

```C

void* fonction_thread (void* arg)
{
  long *pointeur= arg;
  long profondeur=fonc_recursive(*pointeur);

  pthread_mutex_lock (&mutex);/* On verrouille le mutex */

  printf("La profondeur de %ld est de %ld\n\n",*pointeur, profondeur);

  pthread_mutex_unlock (&mutex); /* On déverrouille le mutex */ 

  pthread_exit(NULL); /* Fin du thread */
}

```
