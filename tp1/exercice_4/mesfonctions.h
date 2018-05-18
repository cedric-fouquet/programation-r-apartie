#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_PORT 5000
#define BACKLOG 50
#define NB_CLIENTS 100
#define TAILLE_BUFFER 5

using namespace std;

void exitErreur (const char * msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int readLine (int sockfd, string & line) {	
  line = "";
  int n, i;
  char msgRead[TAILLE_BUFFER];

  while (true) {
    n = read(sockfd, msgRead, sizeof(msgRead));

    // gestion des erreurs
    if (-1 == n) {
      return -1;
    }

    // recv() retourne 0 quand la socket est fermée

    if (!n) {
      return 0;
    }
				
    // sinon, n est le nombre d'octets lus.
				
    // On s'arrête au premier \n rencontré car le message peut en contenir plusieurs
								
    for (i = 0; i < n; ++i) {
      if (msgRead[i] == '\n') {
	break;
      }
    }

    if (i < n) { 
      line = line + string(msgRead, i + 1);
      break;
    } else {
      line = line + string(msgRead, n);
    }
  }
  return line.size();
}
