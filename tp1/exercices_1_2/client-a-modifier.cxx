#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_BUFFER 10 

using namespace std;

void exitErreur(const char * msg) {
  perror(msg);
  exit( EXIT_FAILURE);
}

int main(int argc, char * argv[]){
  if(argc < 3){
    cout << "Usage invalide" << endl;
    exit (EXIT_FAILURE);
  }

  int sock_client = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sockaddr_serveur;
  sockaddr_serveur.sin_family = AF_INET;
  inet_aton(argv[1], &sockaddr_serveur.sin_addr);


  struct sockaddr_in sockaddr_client;
  socklen_t addrlen = sizeof(struct sockaddr_in);

  if (connect (sock_client, (struct sockaddr *) &sockaddr_serveur, sizeof (sockaddr_serveur)) == -1)  
    exitErreur ("connect");


  int n;

  char msg[TAILLE_BUFFER];

  string date("");
 
  while (true) {
	
    n = read (sock_client, msg, TAILLE_BUFFER);

	
    if (n == -1) {
      exitErreur("read");
    }
	
    if (!n) {
      break;
    }

    // sinon, n est le nombre d'octets lus.
    date = date + string (msg, n);

  }

  // Affichage de la date envoyée par le serveur
  std::cout << date;

  close(sock_client);
}
