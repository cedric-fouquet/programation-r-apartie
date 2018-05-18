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

  // if (connect (sock_client, (struct sockaddr *) &sockaddr_serveur,
  // 	       sizeof (sockaddr_serveur)) == -1) {
  //   exitErreur ("connect");
  // }

  int n;
  string message;
  char buf[TAILLE_BUFFER];
 
  while (true) {
    getline(cin, message);

    if ("bye" == message)
      break;

    if (-1 == sendto(sock_client, message.c_str(), message.size(), 0, (struct sockaddr *) &sockaddr_serveur, sizeof (sockaddr_serveur))) {
      exitErreur("sendto");
    }

    int n = recvfrom(sock_client, buf, sizeof(buf), 0, (struct sockaddr *) &sockaddr_serveur, (unsigned int *) TAILLE_BUFFER);

    if (-1 == n) {
      exitErreur("recvFrom");
    }

    string message_recu(buf, n);

    cout << message_recu << endl;
  }
  
  close(sock_client);
}
