#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define NUMPORT 3490
#define BACKLOG 10
#define MAXDATASIZE 256

int crea_socket();
void init_addres(struct sockaddr_in *addr);
void port_socket(int sockfd,struct sockaddr_in addr);
void espera_socket(int sockfd);
int acepta_socket(int sockfd,struct sockaddr_in *addr);
int enviar(int socket,char buffer[MAXDATASIZE]);
int rebre(int socket,char buffer[MAXDATASIZE]);
