#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char *argv[]) {

	pid_t pidfils = fork() ;
	int compteur_fils = 0 ;
	int compteur_pere = 0 ;
	
	switch(pidfils) 
	{	
		case -1 :	perror("Erreurde le creation du procesus") ;	break ;
		case 0  :	
			while(1){
				compteur_fils++ ;
				printf(" %d | %d \n",compteur_fils , compteur_pere);
			}
			//printf("Processus fils : PID %d : PPID",getpid() , getppid());
			break;
		default :	
			printf("Processus pere : PID %d : PID_FILS",getpid , pidfils);
			while(1){
				compteur_pere++ ;
				printf(" %d | %d \n",compteur_fils , compteur_pere);
			}
			break ;
	}

	return 0 ;
}
