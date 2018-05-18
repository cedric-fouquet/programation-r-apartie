#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 50

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}

int main(int argc, char * argv[]){
	
	cout << "nombre d'élements " << argc ;
	
if(argc <4){
	cout << "Usage invalide";
	exit(EXIT_FAILURE);
}
		

int sock_client = socket(AF_INET, SOCK_STREAM,0);

struct sockaddr_in sockaddr_serveur;

sockaddr_serveur.sin_family = AF_INET; 

inet_aton(argv[1], &sockaddr_serveur.sin_addr);

sockaddr_serveur.sin_port = htons(atoi(argv[2])) ;

char * msgWrite ;



if (connect(sock_client, (struct sockaddr *)&sockaddr_serveur, sizeof (sockaddr_serveur)) == -1)  
	exitErreur("connect");  

// envoie de requête : 
string requete  = string("GET ") +string(argv[3])  + string("\r\n");



msgWrite = new char[requete.length()];

strcpy(msgWrite, requete.c_str());
						
			
if (write(sock_client, msgWrite, requete.size()) == -1) exitErreur("write");

int n ; 

char msg[TAILLE_BUFFER] ; 

string msgHTML("") ;

// reccupérer la réponse du serveur : comme pour le daytime.
// On fait plusieurs read jusqu'à ce que read retourne 0 à la déconnexion.
 
while ( 1 ) {
	
	n = read(sock_client, msg, TAILLE_BUFFER);

	
	if ( n == -1  )
		exitErreur("read");

	
	if( !n) break ;

	// sinon, n est le nombre d'octets lus.
	msgHTML = msgHTML + string (msg, n);

}

// Affichage du code html envoyé par le serveur
std::cout << msgHTML  ;

close(sock_client);

}
