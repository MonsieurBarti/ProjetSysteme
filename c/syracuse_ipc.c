#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 2048

void *memoirepartagee;
int shm_fd;
pid_t pid;

void Collatz(unsigned long long int n) {
    char buffer[100];
    sprintf(buffer, "%llu", n);
    sprintf(memoirepartagee, "%s", buffer);
    memoirepartagee += strlen(buffer);
    if (n == 1) {
        return;
    }
    else {
        sprintf(memoirepartagee, " ");
        memoirepartagee++;
        if (n%2 == 0)
            n = n/2;
        else
            n = (3*n)+1;
        Collatz(n);
    }
}

int ipc_collatz(){
    unsigned long long int number = 0;
    shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("Erreur liée au segment de mémoire partagée.\n");
        exit(-1);
    }
    printf("Le segment de mémoire partagée est ouvert.\n");
    ftruncate(shm_fd,SIZE);
    
    pid = fork();
    if (pid < 0) {
        perror("Erreur fork");
    } else if (pid == 0) {
        memoirepartagee = mmap(0,SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (memoirepartagee == MAP_FAILED) {
            printf("erreur map du process enfant\n");
            return -1;
        }
        printf("Entrez un entier positif pour vérifier la conjecture de Collatz(Syracuse)\n");
        scanf("%llu", &number);
        Collatz(number);
    }  else {
        wait(NULL);     
        memoirepartagee = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (memoirepartagee == MAP_FAILED) {
            printf("erreur map process parent\n");
            exit(-1);
        }
        printf("La suite permettant d'arriver à 1 pour le nombre %llu est:\n", number);
        printf("%s\n",memoirepartagee);
        if (shm_unlink("OS") == -1) {
            printf("Erreur lors de la suppression de %s\n","OS");
            exit(-1);   
        }
        printf("Segment de mémoire partagée supprimé\n");
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    ipc_collatz();    
    return 0;
}