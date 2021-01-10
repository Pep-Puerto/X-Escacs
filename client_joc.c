#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define PORT 3490
#define MAXDATASIZE 256

int main(int argc, char *argv[]){
int i=1;
int sockfd,numbytes=0;
char buf[MAXDATASIZE];
struct hostent *he;
struct sockaddr_in their_addr;
int client;

	if (argc!=2){
		fprintf(stderr,"usar: client hostname\n");
		exit(1);
	}
	if ((he=gethostbyname(argv[1]))==NULL){
		perror("gethostbyname");
		exit(1);
	}
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(PORT);
	their_addr.sin_addr=*((struct in_addr*)he->h_addr);
	memset(&(their_addr.sin_zero),'\0',8);
	if (connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))==-1){
		perror("connect");
		exit(1);
	}
	//El client reb informació de qui es: numero de client
	if ((numbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1){perror("recv");exit(1);}
	buf[numbytes]='\0';
	printf("\nInicia client: Soc el client %s\n",buf);
	client=atoi(buf);
	while(1){
		if ((numbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1){perror("recv");exit(1);}
		buf[numbytes]='\0';
		printf("\nReb client:%s\n",buf);
		sprintf(buf,"(Missatge de client %d) %d",client,i++);
		if (send(sockfd,buf,MAXDATASIZE,0) == -1) {perror("send");exit(1);}
		getchar();
	}
	close(sockfd);
	return 0;
}
