
int main(int argc ,char const *argv[] ) {
	char cmd[255] ;
	char** argvbis ;
	do{
		printf("Minishell:->$ ") ;
		gets(cmd) ;
		argvbis = buildargv(cmd) ;
		executerIargvbis) ;
	}while(strcmp(cmd , "quit" ) != 0 ) ;
	
	return 0 ;
	
}
void executer(char *argv[]) 
{	
	pid_t pifils = fork() ;
	
	switch(pifils)
	{	
		case 1 :
			perror("ERREUR");
			break ;
		case 0 :
			execvp(argv[0] ,argv ) ;
			perror("ERREUR");
			break ;
		default :
			wait(NULL) ;
	}
}

char **buildagv(char * cmd) 
{
	char **argvbis = malloc(255 * sizeof(char*)) ;
	int i ;
	for( i = 0 ; i<255 ; i++)
	{
		argvbis[i] = NULL ;
	}
	char cmdbuff[255] ;
	strcpy(cmdbuf , cmd ) ;
	
	i = 0 ;
	argvbis[i] = strtok(cmdbuff , " " ) ; 
	 
	 while((argvbis[i] !=NULL) && (i <255 )
	 {	
	 	i++ ;
	 	argvbis[i] = strtok(NULL , " " ) ; 
	 }
	 return argvbis ;
	 
}
}
