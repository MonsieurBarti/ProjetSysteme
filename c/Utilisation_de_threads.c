#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

//gcc ex2bis.c -o ex2bis -lpthread

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

long taille=3000;
long *tableau_profondeur;

int calc(int nombre){
  if(nombre%2==0){
    return nombre/2;
  }else{
    return 3*nombre+1;
  }
}

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

void* fonction_thread (void* arg)
{
  long *pointeur= arg;
  long profondeur=fonc_recursive(*pointeur);

  pthread_mutex_lock (&mutex);/* On verrouille le mutex */

  printf("La profondeur de %ld est de %ld\n\n",*pointeur, profondeur);

  pthread_mutex_unlock (&mutex); /* On déverrouille le mutex */ 

  pthread_exit(NULL); /* Fin du thread */
}



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



