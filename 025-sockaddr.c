#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[]) {


	if (argc < 3) {
		printf("Erreur : aucun fichier spécifié\n");
		printf("Usage : %s  <adresse_IP> < PORT>\n", argv[0]);
		return 1; 
	}
	
	struct sockaddr_in addrServer;
	
	memset(&addrServer , 0 , sizeof( struct sockaddr_in)) ;
	
	addrServer.sin_family = AF_INET ;
	addrServer.sin_port   = atoi(argv[2]) ;
	addrServer.sin_addr.s_addr = inet_addr(argv[1]);
	
	printf("Adresse IP : %s\n : %x\n" , inet_ntoa(addrServer.sin_addr)  , ntohl(addrServer.sin_addr.s_addr ) )  ;
					/*ntoa  -> network to addresse */   /*ntoh  -> network to host */
	printf("\nNumero de port %d  : %d "  , ntohs(addrServer.sin_port ) , addrServer.sin_port );
	
	
	      
     	return 0 ;
}
