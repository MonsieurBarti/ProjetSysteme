#include <stdio.h> 
#include <stdlib.h> 


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


int main(int argc, char *argv[]){

	tableau_profondeur=calloc(taille, sizeof(long));

	long debut;
	long boucle=1;
	long profondeur;

	while(boucle){

		printf("Nombre de départ :");
		scanf("%ld",&debut);
			if(debut!=-1){
				profondeur=fonc_recursive(debut);
				printf("La profondeur de %ld est de %ld\n\n",debut, profondeur);
			}else{
				boucle=0;
			}
	}
	free(tableau_profondeur);
	return 0;
}