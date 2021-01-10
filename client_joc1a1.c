#include "include/client_joc1a1.h"
#include "include/f_sockets.h"
#include "include/4enRatlla.h"

int main(int argc, char *argv[]){
int sockfd;
char buf[MAXDATASIZE];
struct hostent *he;
struct sockaddr_in their_addr;
int jugador,i=1,j;
t_coord coord,*coord_dest;
char *dades;

	if (argc!=2){
		fprintf(stderr,"usar: client hostname\n");
		exit(1);
	}
	if ((he=(struct hostent *)gethostbyname(argv[1]))==NULL){
		perror("gethostbyname");
		exit(1);
	}
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(NUMPORT);
	their_addr.sin_addr=*((struct in_addr*)he->h_addr);
	memset(&(their_addr.sin_zero),'\0',8);
	if (connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))==-1){
		perror("connect");
		exit(1);
	}

	fi_partida=FALSE;
	jugada_valida=FALSE;
	jugador=JUG_2;
	inicialitzar();

	while(1){
		rebre(sockfd,buf);
		coord_dest=(t_coord *)malloc(sizeof(t_coord));
		desempaquetar(buf,&coord_dest);
		i=coord_dest->f;
		j=coord_dest->c;
		tab[i][j]='*';
		printf("\nf:%d c:%d \n",i,j);
		X_imprimir();
		//jugar
		do{
			X_torn(jugador);
			jugada_valida=jugar(simbol_jugador(jugador),&i,&j);
		}while (!jugada_valida);
		X_imprimir();
		if (evaluar_enratlla(i,j,RATLLA)){
			X_msg_guanyador(jugador);
			fi_partida=TRUE;
		}

		//empaquetar jugada i enviar
		coord.f=i;
		coord.c=j;
		dades=(char *)malloc(sizeof(t_coord));
		empaquetar(dades,&coord,sizeof(t_coord));
		enviar(sockfd,dades);

	}
	close(sockfd);
	return 0;
}
int empaquetar(char *d,t_coord *fc,int tam){
char *orig,*dest;
int i;
	orig=(char *)fc;
	dest=(char *)d;
	for(i=0;i<tam;i++) {*dest=*orig;dest++;orig++;};
}

int desempaquetar(char *d,t_coord **fc){
	(*fc)=(t_coord *)d;
}
