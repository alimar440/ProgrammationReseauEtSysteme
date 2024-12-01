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

//pour tester : nc 0.0.0.0 port


int main(int argc, char *argv[]) {


	if (argc < 2) {
		printf("Erreur : aucun fichier spécifié\n");
		printf("Usage : %s  < PORT>\n", argv[0]);
		return 1; 
	}
	
	//creation socket TCP
   
	int socketServerTCP = socket(AF_INET , SOCK_STREAM , 0) ;
	  
	if(socketServerTCP == -1){
	   	perror("Erreur! creation socket TCP" ) ;
	 }
	   
	printf("Creation socketTCP reussie 🥳 \n");	
	
	//init de la struct de nommage du server
	struct sockaddr_in addrServer;
        memset(&addrServer, 0, sizeof(struct sockaddr_in));

        addrServer.sin_family = AF_INET;
        addrServer.sin_port = htons(atoi(argv[1]));
        addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");

	
	//nommage du server avec bind

	int result = bind(socketServerTCP, (struct sockaddr*) &addrServer, sizeof(struct sockaddr_in));
	
	if(result==-1){
	    perror("Error de bind");
	     exit(1);
	}

	printf("Execution execution  bind success 🥳 \n");

	result = listen(socketServerTCP, 5);
	
	if(result==-1){
	   perror("Error de Listen");
	    exit(1);
	}

	printf("Execution de listen success 🥳 \n");


	//accept


	//adresse du client distant
	struct sockaddr_in addrClient;
	//taille de l adress du client distant
	int tailleAddrClient = sizeof(addrClient);
	//socket secondaire
	int socketClientDistant = accept(socketServerTCP, (struct sockaddr*) &addrClient, &tailleAddrClient);

	if(socketClientDistant == -1){
	perror("socketClientDistant error");
	exit(1);
	}

	printf("Connexion du client %s:%d reussie\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));
	// //init les champs


	// printf("Infos de l @\n");
	// printf("@ : %s (%X)\n", inet_ntoa(addrServer.sin_addr), ntohl(addrServer.sin_addr.s_addr));

	      
     	return 0 ;
}
