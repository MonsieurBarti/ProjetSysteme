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

				printf("Pour : %ld ",val);

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
				printf("\n");
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