#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int n;
    printf("Entrez un nombre: ");
    scanf("%d", &n);
    printf("Nombre de calculs: %d \n", syracuse(n));
}