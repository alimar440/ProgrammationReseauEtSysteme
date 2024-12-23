#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h> 
#include "utils.h"

int main(int argc, char* argv[]){

    if(argc<4)
        printf("Argument count : %s < @ > < port > \n", argv[0]);

    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    if(socketClient == -1){
        perror("Socket TCP error in creation");
        return 0;
    }
    printf("Creation de la socket ok\n");

    //init de la struct de nommage du server
    struct sockaddr_in addrServer;
    
    memset(&addrServer, 0, sizeof(struct sockaddr_in));


    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(atoi(argv[2])); //htonshort(16bits)
    addrServer.sin_addr.s_addr = inet_addr(argv[1]);

    //Connect
    int resultat = connect(socketClient , (struct sockaddr*) &addrServer , sizeof(struct sockaddr_in));

    if(resultat==-1){
        perror("Erreur d'ouverture de connexion ");
        return 0 ;
    }
    
    
    
    
    //4 Copie
   	//4/1 Recuperer les informations du fichier
   	
   struct stat stfile ;
   stat(&stfile) ;
   
   //Envoyer
   struct infofile info ;
   
   info.taille = stfile.st_size ;
   info.mode = stfile.st_mode ;
   strcpy(info.nomfichier , argv[3]);
   
   int nbsend = send(socketClient , &info, sizeof(struct infofile) , 0 ) ;
   
   if(nbsend<=0){
   	perror("") ;
   	return  0;
   }
   char buffRecv[255] ;
   memset(socketClient , buffRecv , 255 *sizeof(char) ,0 ) ;
   
   if(strcmp(buffRecv , "OK")!=0){
   	perror("") ;
   	return  ;
   }
   
   
      
    close(socketClient) ;
    return 0;
}


    
    
    
    
    
    
    
    
    
    
    
    
