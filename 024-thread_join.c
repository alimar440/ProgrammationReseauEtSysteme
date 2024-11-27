#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int countPrincipal = 0;
int countSecondaire = 0;
int i = 0;

// Pointeur pour le fichier de sortie
FILE *file;

void *ftheadsecondaire(void *arg) {
    while (1) {
        fprintf(file, "%d %d %d\n", ++i, countPrincipal, countSecondaire++);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t th1;

    // Ouvrir un fichier en écriture
    file = fopen("output.dat", "w");
    if (file == NULL) {
        perror("Erreur: ouverture fichier");
        return 1;
    }

    if (pthread_create(&th1, NULL, ftheadsecondaire, NULL) != 0) {
        perror("Erreur: creation thread");
        return 1;
    }

    while (countPrincipal < 10000) {
        fprintf(file, "%d %d %d\n", ++i, countPrincipal++, countSecondaire);
    }

    pthread_join(th1, NULL);

    fclose(file); // Fermer le fichier
    return 0;
}
