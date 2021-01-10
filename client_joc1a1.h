typedef struct{
	int f;
	int c;
	char m[8][8];
}t_coord;

int empaquetar(char *d,t_coord *fc,int tam);
int desempaquetar(char *d,t_coord **fc);
