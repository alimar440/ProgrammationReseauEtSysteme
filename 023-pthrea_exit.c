#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 

int countPrincipal = 0 ;
int countSecondaire = 0;
int i = 0 ;
void *ftheadsecondaire(void *arg) {
    
    while (1) {
        printf("%d  %10d  %10d\n",  ++i , countPrincipal , countSecondaire++);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t th1;

    
    if (pthread_create(&th1, NULL, ftheadsecondaire, NULL) != 0) {
        perror("Erreur: creation thread");
        return 1;
    }

   
    while (1) {
        printf("%d  %10d  %10d\n",  ++i , countPrincipal++ , countSecondaire);
    }

    return 0;
}
