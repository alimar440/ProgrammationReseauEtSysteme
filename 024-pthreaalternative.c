#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_THREADS 10

int suiv = 1;
int nbThread;
sem_t semaphores[MAX_THREADS];

void* threadFunction(void* arg) {
    int courant = *(int*)arg - 1;

    while (1) {
        sem_wait(&semaphores[courant ]);
        
        printf("Thread %d s'est exécuté.\n", courant +1 );
        
        suiv = (suiv % nbThread) + 1;
        
        sem_post(&semaphores[suiv -1]);
        
        usleep(100000);
    }

    return NULL;
}

int main() {
    printf("Entrez le nombre de threads : ");
    scanf("%d", &nbThread);

   

    for (int i = 0; i < nbThread; i++) {
        sem_init(&semaphores[i], 0, 0);
    }

    pthread_t threads[nbThread];
    int courant[nbThread];
    
    for (int i = 0; i < nbThread; i++) {
        courant[i] = i + 1 ;
        pthread_create(&threads[i], NULL, threadFunction, &courant[i]);
    }

    sem_post(&semaphores[0]);

    for (int i = 0; i < nbThread; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < nbThread ; i++) {
        sem_destroy(&semaphores[i]);
    }

    return 0;
}
