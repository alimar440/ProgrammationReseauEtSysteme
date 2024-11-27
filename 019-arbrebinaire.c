#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>




int main(int argc, char *argv[]) {

	pid_t pidfils1 ,pidfils2 , pidfils3 ;
	int profondeur = 0 ;
	
	
	for(int nbfils = 0 ; nbfils< 10 ; )
	{	
		pidfils1 = fork() ;
		switch(pidfils1) 
		{	
					
			case -1 :	perror("Erreurde le creation du procesus") ;	break ;
			case 0  :	
				
				printf(" %d -> %d ; \n",getppid() , getpid());
				profondeur++ ;
				
				if(profondeur > 5)
				{
					return 0 
				}
					
				
				nbfils = 0 ;
				break ;
			default :	
				wait(NULL) ;
				++nbfils ;
				if(nbfils >= 2)
				{
					return 0; 
				}
				
				
				
		}
	}
	

	return 0 ;
}
