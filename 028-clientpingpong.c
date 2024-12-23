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

//pour tester : nc -l -p 8000
//pour executer : executable 127.0.0.1


int main(int argc, char* argv[]){
    if(argc<3)
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

    printf("Execution de connect\n");
    
    //Logique de l'application

   
   
    char buffReceive[10];
    char buffSend[] = "Pong";
    int nbReceive = 0 ;
    int i = 0 ;

    while(1){
        memset(buffReceive ,0 , 10*sizeof(char)) ;
        nbReceive = recv(socketClient, buffReceive, 10*sizeof(char), 0);
        if(nbReceive>0){
        	printf("[%d] Recu : %s \n ",i, buffReceive);
   	 }
        sleep(1);
        
        send(socketClient, buffSend, 10*sizeof(char), 0);
        printf("[%d] Serveur >client : %s", i ,buffSend);
        i++ ;
       
        
    }
    
    close(socketClient) ;
    return 0;
}



