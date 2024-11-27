#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>




int main(int argc, char *argv[]) {

	pid_t pidfils1 ,pidfils2 , pidfils3 ;
	
	
	
	for(int i = 0 ; i< 10 ; i++)
	{	
		pidfils1 = fork() ;
		switch(pidfils1) 
		{	
					
			case -1 :	perror("Erreurde le creation du procesus") ;	break ;
			case 0  :	
				
				printf(" %d -> %d ; \n",getppid() , getpid());
				return 0 ;
			default :	
				wait(NULL) ;
				
				break ;
		}
	}
	

	return 0 ;
}
