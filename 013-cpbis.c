#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> 



int main(int argc, char *argv[]) {


	if (argc < 3) {
		printf("Erreur : aucun fichier spécifié\n");
		printf("Usage : %s <nombre> <nom_du_fichier>\n", argv[0]);
		return 1; 
	    }
    
       int fdSrc = open(argv[2] , O_RDONLY ) ;
       
       printf("ouverture DU FICHIER A SUCCES ");
       

   	char buff  ;
   	int nbRead,nbWrite ;
   	int nbTotal = 0;
   	 int fdDst = open(argv[1] , O_WRONLY | O_CREAT | O_EXCL ,
    			S_IWUSR | S_IRUSR |S_IRGRP |
    			S_IROTH 
    			) ;
   	do{
   	
   		
   		nbRead = read(fdSrc , &buff , sizeof(char) ) ;
   		if(nbRead > 0 ) 
   		{
   			nbWrite = write(fdDst , &buff , sizeof(char) ) ;
   		
   			if(nbWrite ){
   			}
    		}
   	}while(nbRead > 0  ) ;
      
      
      
      return 0 ;
}
