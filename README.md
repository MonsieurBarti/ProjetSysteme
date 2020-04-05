# Projet Système Syracuse

> Ce projet consiste à optimiser la conjecture de syracuse le plus possible à l'aide de threads et/ou processus

Table of Contents (up to date)
- [Projet Système Syracuse](#projet-syst%c3%a8me-syracuse)
- [Version 1 - Itératif](#version-1---it%c3%a9ratif)
- [Version 2 - Récursif](#version-2---r%c3%a9cursif)
- [Version 3 - Utilisation des threads](#version-3---utilisation-des-threads)
- [Version 4 - Utilisation des processus](#version-4---utilisation-des-processus)
- [Parties Personnelles - Arnaud](#parties-personnelles---arnaud)
- [Parties Personnelles - Pierre](#parties-personnelles---pierre)
- [Conclusion du projet](#conclusion-du-projet)

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

```C

int main (void)
{

  tableau_profondeur=calloc(taille, sizeof(long));

  long debut1;
  long debut2;
  long boucle=1;

  pthread_t monThread1;
  pthread_t monThread2;

  while(boucle){

    printf("Faire calcules ? (oui=1, non=0)");
    scanf("%ld",&boucle);

    if(boucle==1){

      printf("Premier nombre de départ :");
      scanf("%ld",&debut1);

      printf("Deuxième nombre de départ :");
      scanf("%ld",&debut2);

      pthread_create (&monThread1, NULL, fonction_thread, (void*)&debut1);
      pthread_create (&monThread2, NULL, fonction_thread, (void*)&debut2); /* Création des threads */

      pthread_join (monThread1, NULL);
      pthread_join (monThread2, NULL);/* Attente de la fin des threads */
    }else{
      boucle=0;
    }
  }
  free(tableau_profondeur);
  return 0;
}

```

# Version 4 - Utilisation des processus

# Parties Personnelles - Arnaud
Le premier obstacle que j'ai rencontré, c'était la limitation par la mémoire. 

En effet j'ai commencé par initialiser un tableau de 3000 cases. Mais si l'algorithme depassais la valeur de 3000 alors j'obtenais l'erreur "segmentation fault". J'ai donc décidé de faire une allocation de mémoire dynamique en utilisant calloc et realloc.

J'initialise un tableau avec calloc et si je me rends compte que j'ai besoin de plus de place alors j'augmente la taille avec realloc.

J'ai décidé d'utiliser calloc au lieu de malloc, car je voulais pouvoir tester si j'avais deja remplis une case du tableau ou non. Si la valeur est à 0 alors cela signifie que je n'ai pas effectué ce calcul.

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

# Parties Personnelles - Pierre
De mon côté, je me suis penché sur les IPC et j'ai pour cela effectué quelques recherches pour déterminer ce qui pourrait m'aider à réaliser ce programme.

J'ai donc commencé par créer un segment de mémoire partagée :
```C
shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
```
Une fois ce segment créé, j'ai testé qu'il n'y avait pas d'erreur liée à cette création.
```C
if (shm_fd == -1) {
	printf("\tErreur liée au segment de mémoire partagée.\n");
	exit(-1);
}
printf("\tLe segment de mémoire partagée est ouvert.\n");
```
Une fois ce segment créé, il me fallait un moyen pour que mes différents processus puissent y accéder. J'ai donc utiliser la fonction mmap qui permet d'accéder à ce segment.
```C
ptr = mmap(0,SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
```
Je vérifie ensuite que la fonction mmap n'a pas généré d'erreur.
```C
if (ptr == MAP_FAILED) {
	printf("\terreur map du process enfant\n");
	return -1;
}
```
Dans le processus enfant, j'exécute ma fonction Collatz après avoir demandé à l'utilisateur quel nombre il souhaitait avoir.
```C
printf("Entrez un entier positif pour vérifier la conjecture de Collatz(Syracuse)\n");
scanf("%llu", &number);
Collatz(number);
```
Une fois la fonction exécutée, je passe au processus parent à qui j'applique le mmap de la même façon pour pouvoir lire les données du segment de mémoire partagée.

Parlons maintenant de notre fonction Collatz que je vous mets ci-dessous :
```C
void Collatz(unsigned long long int n) {
    char buffer [SIZE];
    sprintf(buffer, "%llu", n);
    sprintf(ptr, "%s", buffer);
    ptr += strlen(buffer);
    if (n == 1) {
        return;
    }
    else {
        sprintf(ptr, " ");
        ptr++;
        if (n%2 == 0)
            n = n/2;
        else
            n = (3*n)+1;
        Collatz(n);
    }
}
```
C'est une fonction récursive qui permet deux choses :
- Elle calcule les éléments de la séquence de Syracuse impliquée.
- Elle les ajoute à la mémoire partagée pour que tous les processus puissent y accéder après un mapping.

Cela est possible grâce à l'utilisation du buffer local qui contient les valeurs dans un tableau de caractères.
On envoie ensuite les données à la mémoire partagée en utilisant la fonction sprintf
```C
sprintf(ptr, "%s", buffer);
```

# Conclusion du projet

Nous avons beaucoup aimé effectuer ce projet et nous pensons que c'était très intéressant à faire. Cela nous a permis d'utiliser les compétences que nous avons appris pendant le DUT et notamment en cours de système d'exploitation. (IPC,thread, recursivité, ...)

Cependant, peut être qu'un exemple plus concret avec une compléxité mathématique plus élevée aurait été plus intéressant pour voir l'impact de l'optimisation apportée au code. Pour le moment on ne distingue pas une grande différence entre le programme utilisant les threads, IPC, et récursif.  
