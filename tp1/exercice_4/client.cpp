#include "mesfonctions.h"


int main(int argc , char * argv[])
{
  if (argc < 3){
    cout << "Usage invalide";
    exit(EXIT_FAILURE);
  }
  
  int sock_client = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sockaddr_serveur;
	
	
  sockaddr_serveur.sin_family = AF_INET; 

  inet_aton(argv[1], &sockaddr_serveur.sin_addr);

  sockaddr_serveur.sin_port = htons(atoi(argv[2])) ;
	
	
  if (-1 == connect(sock_client, (struct sockaddr *) &sockaddr_serveur, sizeof (sockaddr_serveur))) {
    exitErreur("connect");
  }

  string msgClavier;
  string msgRecu("");
  int n;
	
  while (true) {		
	
    // Lire depuis le claiver un msg sous de forme de string et lui rajouter un saut de ligne
    // car getline () ne garde pas le saut de ligne lu depuis le clavier

    cout << "Moi : ";
    getline(cin, msgClavier);
    msgClavier = msgClavier + '\n';

    // Envoi du message
    if (-1 == write(sock_client, msgClavier.c_str(), msgClavier.size())) {
      exitErreur("write");
    }
			
    // lire le message de serveur qui doit se terminer par un saut de ligne

    n = readLine(sock_client,msgRecu);
			
    if (n == 0) {
      break; // deconnexion.
    }

    cout << "Toi : " << msgRecu ;
    // le saut de ligne  \r\n avec telnet
  }

  close(sock_client);
  return EXIT_SUCCESS;
}
