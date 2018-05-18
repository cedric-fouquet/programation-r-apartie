int sockUdp = socket(AFINET, SOCK_DGRAM, 0);
int sockTcp = socket(AFINET, SOCKSTRAM, 0);

if(setsockopt(socktcp, SQL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
exitErreur("setsockopt");

if (bind(socktcp, (struct sockaddr *) &sockaddr_serveur, sizeof(sockaddr_in) == -1)
exitErreur("bind2");

listen (socktcp, BACKLOG);

sockaddr_in sockaddr_client;
socklen_t size = sizeof(sockaddr_client);

char buf[TAILLE_BUFFER];
char * msg;
time_t date;

cout << "Serveur DayTime lancé sur le port " << port << endl;

fd_set readfds, writefds, exceptfds;

int max;

for(int i = 1 ; i < = NB_CLIENTS; i++)

{
FD_ZERO(&readfds);
};)