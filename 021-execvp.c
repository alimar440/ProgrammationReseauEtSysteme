#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char **argv[]) {

	char *argvbis[] = {
		 "ls" ,
		  "-l" ,
		   "-a" , 
		   (char * ) NULL 
	} ;
		   
	printf("Nouvelle commande ls \n");
	execlp("ls" ,argvbis );
	printf"Erreur d'execution de exec \n") ;
	
	return 0 ;
}
