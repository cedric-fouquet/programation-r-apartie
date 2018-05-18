#include "mesfonctions.h"


int main(int argc, char *argv[])
{
  if (argc < 2) {
    exitErreur("Usage invalide");
  }
	
  // Le serveur écoute sur toutes les interfaces réseaux de sa machine et sur le port donné comme argument de la ligne de commande.
	
  int port = atoi(argv[1]);

  int sock_serveur = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sockaddr_serveur;

  sockaddr_serveur.sin_family = AF_INET;
  sockaddr_serveur.sin_port = htons(port);
  sockaddr_serveur.sin_addr.s_addr = INADDR_ANY;

  int yes = 1;
  if (-1 == setsockopt(sock_serveur, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) {
    exitErreur("setsockopt");
  }

  if (-1 == bind(sock_serveur, (struct sockaddr *) &sockaddr_serveur, sizeof(sockaddr_in)))
    exitErreur("bind");

  if (listen(sock_serveur, BACKLOG) == -1)
    exitErreur("listen");

  int sock_client;
  string msgClavier;
  string msgRecu("");
  int n;

  cout << "Serveur chat lancé sur le port " << NUM_PORT << endl;

  for (int i = 1; i <= NB_CLIENTS; i++) {
    // Le serveur attend un client
    sock_client = accept(sock_serveur, NULL, NULL);
    
    if (-1 == sock_client) {
      exitErreur("accept");
    }

    // Le serveur chatte à tour de rôle avec le client
    // Le client commence, ça se termine lorsque le client envoie bye ou il y a déconnexion

    cout << "Client : "<< i << endl;
		
    while(true) {

      // lire le message du client qui doit se terminer par un saut de ligne
      // dès l'utilisation de readLine() qui est définie à part dans mesfonctions.h

      n = readLine(sock_client,msgRecu);
			
      // client s'est déconnecté
      if (!n) {
	break ;
      }
			
      cout << "Toi : " << msgRecu;

      // client envoie bye
			
      if (msgRecu == "bye\n" || msgRecu == "bye\r\n")
	break;
				
      //msgRecu == "bye\r\n" : si on teste le serveur depuis telnet
			
      // Lire depuis le clavier un msg sous de forme de string et lui rajouter un saut de ligne
      cout << "Moi : ";
      getline(cin , msgClavier);
      msgClavier = msgClavier + '\n';
		
      // Le serveur envoie le message au client
      if (-1 == write(sock_client, msgClavier.c_str(), msgClavier.size() )) {
	exitErreur("write");
      }
    }

    cout << "Un autre client ? " << endl;
    close(sock_client);
  }
  close(sock_serveur);
  return EXIT_SUCCESS;
}
