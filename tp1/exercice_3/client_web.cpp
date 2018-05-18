#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_BUFFER 10 

void exitErreur(const char * msg)
{
  perror (msg);
  exit (EXIT_FAILURE);
}

int main (int argc, char * argv[])
{
  if (argc < 3) {
    std::cout << "Usage invalide" << std::endl;
    exit (EXIT_FAILURE);
  }

  int sock_client = socket (AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sockaddr_serveur;
  sockaddr_serveur.sin_family = AF_INET;
  inet_aton (argv[1], &sockaddr_serveur.sin_addr);


  struct sockaddr_in sockaddr_client;
  socklen_t addrlen = sizeof (struct sockaddr_in);

  if (-1 == connect (sock_client, (struct sockaddr *) &sockaddr_serveur, sizeof (sockaddr_serveur))) {
    exitErreur ("connect");
  }

  int n;
  char msg[TAILLE_BUFFER];
  std::string date ("");
  std::string requete = std::string ("GET ") + std::string (argv[3]) + std::string (" \n");
  
  while (true) {
    std::cout << "Passage dans la boucle." << std::endl;
    if (-1 == write (sock_client, requete.c_str (), TAILLE_BUFFER)) {
      std::cout << "Erreur d'écriture dans le socket." << std::endl;
    }
    
    n = read (sock_client, msg, TAILLE_BUFFER);

    if (n == -1) {
      exitErreur ("read");
    }
	
    if (!n) {
      break;
    }

    // sinon, n est le nombre d'octets lus.
    date = date + std::string (msg, n);
  }

  // Affichage de la date envoyée par le serveur
  std::cout << date << std::endl;

  close (sock_client);
}
