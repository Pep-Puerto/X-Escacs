#include "include/f_sockets.h"

int crea_socket(){
int sockfd;
int yes=1;
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	//Per permetre reutilitzar el port...
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1){
		perror("setsockopt");
		exit(1);
	}
	return sockfd;
}

void init_addres(struct sockaddr_in *addr){
	addr->sin_family=AF_INET;
	addr->sin_port=htons(NUMPORT);
	addr->sin_addr.s_addr=INADDR_ANY;
	memset(&(addr->sin_zero),'\0',8);
}

void port_socket(int sockfd,struct sockaddr_in addr){
	if (bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}
}

void espera_socket(int sockfd){
	if (listen(sockfd,BACKLOG) == -1){
		perror("listen");
		exit(1);
	}
}

int acepta_socket(int sockfd,struct sockaddr_in *addr){
int sin_size,new_fd;
	sin_size=sizeof(struct sockaddr_in);
	if ((new_fd=accept(sockfd,(struct sockaddr *)addr,&sin_size))==-1){
		perror("accept");
		return -1;
	}
	return new_fd;
}

int enviar(int socket,char buffer[MAXDATASIZE]){
	if (send(socket,buffer,MAXDATASIZE,0) == -1) perror("send");
}

int rebre(int socket,char buffer[MAXDATASIZE]){
int numbytes;
	if ((numbytes=recv(socket,buffer,MAXDATASIZE,0))==-1){perror("recv");exit(1);}
	buffer[numbytes]='\0';

}