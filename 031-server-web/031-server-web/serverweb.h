#ifndef SERVERWEB_H 
#define SERVERWEB_H 

void affiche_sockaddr(struct sockaddr_in sockaddr ) ;
void affiche_requete(char * buffReceiv ) ;
int repondre_requete(int sock , char requete[]);

#endif 
