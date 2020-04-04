#include <stdio.h> 
#include <stdlib.h> 


long taille=3000;
long *tableau_suivant;
long *tableau_profondeur;
long  profondeur=0;
long  debut;
long  val=0;
long  suivant;
int boucle=1;


int calc(int nombre){
	if(nombre%2==0){
		return nombre/2;
	}else{
		return 3*nombre+1;
	}
}


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
				profondeur++;
				suivant=calc(val);
				tableau_suivant[val]=suivant;
				val=suivant;
				printf("%ld\n",val);
			}
			tableau_profondeur[debut]=profondeur;
			printf("Profondeur pour %ld est :%ld \n",debut,profondeur);
		}else{
			boucle=0;
		}
	}
	free(tableau_suivant);
	free(tableau_profondeur);
	return 0;
}

