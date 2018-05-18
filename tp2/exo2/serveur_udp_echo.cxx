#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define BACKLOG 50
#define NB_CLIENTS 100
#define TAILLE_BUFFER 5


using namespace std;

void exitErreur(const char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  int port;

  if (2 == argc) {
    port = atoi(argv[1]);
  } else {
    exitErreur("Usage invalide");
  }

  int sock_serveur = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in sockaddr_serveur;

  sockaddr_serveur.sin_family = AF_INET;
  sockaddr_serveur.sin_port = htons(port);
  sockaddr_serveur.sin_addr.s_addr = INADDR_ANY;

  int yes = 1;

  if (-1 == setsockopt(sock_serveur, SOL_SOCKET, SO_REUSEADDR,
		       &yes, sizeof(int))) {
    exitErreur("setsockopt");
  }

  if (-1 == bind(sock_serveur, (struct sockaddr *) &sockaddr_serveur,
		 sizeof(sockaddr_in))) {
    exitErreur("bind");
  }

  sockaddr_in sockaddr_client;
  socklen_t size = sizeof(sockaddr_client);

  char buf[TAILLE_BUFFER];
  int nbOctetsRecus;

  cout << "Serveur Echo UDP lancé  sur le port " << port << endl;

  for (int i = 1; i <= NB_CLIENTS; ++i) {
    if (-1 == (nbOctetsRecus = recvfrom(sock_serveur, buf,
					sizeof(buf), 0,
					(struct sockaddr *) &sockaddr_client,
					&size))) {
	exitErreur("recvfrom");
      }
				
    cout << string(buf, nbOctetsRecus) << endl;
		
    if (-1 == sendto(sock_serveur, buf, nbOctetsRecus, 0,
		     (struct sockaddr *) &sockaddr_client,
		     sizeof(sockaddr_client))) {
      exitErreur("sendto");
    }
  }

  close(sock_serveur);

  return EXIT_SUCCESS;
}
