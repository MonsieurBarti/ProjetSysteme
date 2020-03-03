#include <stdio.h>
#include <stdlib.h>

int cpt = 1;

int syracuse(int n) {
    while (n != 1) {
        if (n%2 == 0) {
            n=n/2;
            cpt+=1;
        } else {
            n=3*n+1;
            cpt+=1;
        }
    }
}

int main() {
    int n;
    printf("Entrez un nombre: ");
    scanf("%d", &n);
    printf("Nombre de calculs: %d \n", syracuse(n));
}