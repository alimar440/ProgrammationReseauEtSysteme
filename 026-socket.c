#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[]) {


   
   //creatio socket TCP
   
   int socketTCP = socket(AF_INET , SOCK_STREAM , 0) ;
   
   if(socketTCP == -1){
   	perror("Erreur! creation socket TCP" ) ;
   }
   
   printf("Creation socketTCP reussie 🥳 \n");	
   //creatio socket UDP
   
   int socketUDP = socket(AF_INET , SOCK_DGRAM , 0) ;
   
   if(socketUDP == -1){
   	perror("Erreur! creation socket TCP" ) ;
   }
   
   printf("Creation socketUDP reussie 🥳 \n");	
	      
     	return 0 ;
}
