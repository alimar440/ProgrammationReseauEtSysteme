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
#include <unistd.h> 
#include "serverweb.h"
#include <sys/stat.h> 
#include <fcntl.h>

//pour tester : nc 0.0.0.0 port

char* RACIN_SITE = "/home/ali/TP_prog_sys/031-server-web" ;

int Compter = 0;
int main(int argc, char *argv[]) {


	if (argc < 2) {
		printf("Erreur : aucun fichier spécifié\n");
		printf("Usage : %s  < PORT>\n", argv[0]);
		return 1; 
	}
	
	
	//1. creation socket TCP
   
	int socketServer = socket(AF_INET , SOCK_STREAM , 0) ;
	
	if(socketServer == -1){
	   	perror("Erreur! creation socket TCP" ) ;
	 }
	
	printf("[#Server web#] Creation socket................OK🥳 \n");	
	
	
	
	//2. init de la struct de nommage du server
	struct sockaddr_in addrServer;
        memset(&addrServer, 0, sizeof(struct sockaddr_in));

        addrServer.sin_family = AF_INET;
        addrServer.sin_port = htons(atoi(argv[1]));    //evite le probleme du big ENDian
        addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");
        
        printf("[#Server web#] Initialition la structure ................OK🥳 \n");
        
        
        //3. nommage de la  la structure avec bind

	int result = bind(socketServer, (struct sockaddr*) &addrServer, sizeof(struct sockaddr_in));
	
	if(result==-1){
	    perror("Error de bind");
	     exit(1);
	}
	
	printf("[#Server web#] nommage de la  la structure avec bind................OK🥳 \n");
	
	
	//4. Appel de listen
	result = listen(socketServer, 5);
	
	if(result==-1){
	   perror("Error de Listen");
	    exit(1);
	}
        
        
        printf("[#Server web#] Appel de listen................OK🥳 \n");
        
        
        //Logique 
        
        				//a. Accepter la connexion
        				//b. Analyser la requete 
        				//c. Construre Reponse 
        				//d. envoyer reponse et fermet la socket
        				//e. Retour vers 1
        
        
        struct sockaddr_in addrClient ;
        int taille_addr = sizeof(struct sockaddr ) ;
        int socketClient ;
        char buffReceive[8192] ;
		int nbReceive;
        
        
        while(1)
	{
		socketClient = accept(socketServer, (struct sockaddr *)&addrClient , &taille_addr) ;
		affiche_sockaddr(addrClient) ;
		//initialsaion de buffer
		memset(buffReceive, 0, 8192*sizeof(char) ) ;
		nbReceive = recv(socketClient,buffReceive, 8192*sizeof(char) , 0 ) ;
		if(nbReceive < 0)
		{ 
			perror("Erreur reception de le requete") ;
			return 0 ;
		}
		affiche_requete(buffReceive) ;
		repondre_requete(socketClient , buffReceive) ;
		close(socketClient) ;



	}

        
        
        
	     	return 0 ;
}

void affiche_sockaddr(struct sockaddr_in sockaddr ){
	printf("Client Accepter: \n");
	printf("===================================================================\n") ;
	printf("Adresse IP : %s\n", inet_ntoa(sockaddr.sin_addr));
	printf("Numero de port %d  	\n",ntohs(sockaddr.sin_port)) ;
	printf("===================================================================\n") ;


}
	
void affiche_requete(char * buffReceive ){
		printf("Requete du client : \n");
	printf("%s\n", buffReceive) ;
	printf("===================================================================\n") ;
}


int repondre_requete(int sock , char requete[]){
	
	//entete du fichier
	char requetetmp[8192] ;
	strcpy(requetetmp,requete);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n") ;
	printf("Requetetmp : %s\n", requetetmp) ;
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n") ;

	char  templateEntete[8192] = "HTTP/1.1 200 OK\n\
Date: Sat, 21 Dec 2024 11:30:00 GMT\n\
Server: Apache UGB \n\
Content-Type: %s\n\
Content-length: %d\n\
\n";
	
	char* nomFichierRecu = strtok(requetetmp , " ") ;
	nomFichierRecu = strtok(NULL, " ") ;
	char nomFichierComplet[255] ; // contient le chemain absolue local du fichier
	char extensionFichier[100] ; //contiendra l'extension pour en deduire le type MIME

	if(strcmp(nomFichierRecu, "/") == 0){   // cas de la racine du site
		sprintf(nomFichierComplet,"%s%sindex.html",RACIN_SITE,nomFichierRecu) ;
		strcpy(extensionFichier,  "html") ;

	}else{// car ou le nom du fichier est specifier 
		sprintf(nomFichierComplet,"%s%s",RACIN_SITE,nomFichierRecu) ;
		strcpy(requetetmp, nomFichierRecu) ;
		strcpy(extensionFichier, strtok(requetetmp , ".")) ;
		strcpy(extensionFichier,  strtok(NULL, " ")) ;
	}

	char typeMime[255]; //Type MiME á spécifier sur la reponse 
	if(strcmp( extensionFichier, "html") == 0){strcpy(typeMime , "application/xhml+xml");}
	else if (strcmp( extensionFichier, "pdf") == 0){
		strcpy(typeMime , "application/pdf");
	}
	else if (strcmp( extensionFichier, "mp4") == 0){strcpy(typeMime , "video/mp4");}
	else if (strcmp( extensionFichier, "png") == 0){strcpy(typeMime , "image/png");}
	else{strcpy(typeMime , "application/octet-stream");}

	//determination de la taille du fichier
	struct stat stfile ;
	stat(nomFichierComplet,&stfile );
	char reponseComplete[8192];
	sprintf(reponseComplete, templateEntete, typeMime,stfile.st_size) ;

	printf("Reponse %s\n", reponseComplete) ;
	int nbsend = send(sock, reponseComplete , strlen(reponseComplete) , 0);

	 if(nbsend<0){
		perror("Erreur envoie de messaque avec send");
		return -1;
	 }

	int fd = open(nomFichierComplet,O_RDONLY);
	if(fd == -1){
		perror("Erreur ouverture fichier");
		return 0;
	}

	char buffRead[1848576] ;
	int nbRead ,nbReadTotal = 0 ;

	do{
		nbRead = read(fd , buffRead , 1048576 * sizeof(char)) ;
		if(nbRead > 0){
			nbRead = send(sock , buffRead ,nbRead * sizeof(char) , 0) ;
			if(nbsend < 0 ){
				perror("Erreur envoie de reponse");
				return -1;
			}
			nbReadTotal +=nbsend ;
			printf("=================>    %d\n" , nbReadTotal) ;
		}
	}while(nbRead > 0) ;

	close(fd) ;
	return 0  ;
	
	

}
