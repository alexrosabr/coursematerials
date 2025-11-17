/*
 * Exercicio: Torres de Hanoi
 * Este programa exibe tres pinos com N discos
 * O valor de N e' passado via linha de comando 
 */
#include <stdio.h>

#define MAX_DISCOS	10
#define CHAR_PINO	'|'
#define CHAR_DISCO	'@'

/*===== variaveis globais ===============================*/
int Pino[3][MAX_DISCOS+1];
int num_discos=0;
char disco[MAX_DISCOS+1];
char *msg[2]={
	"Nao ha' discos na origem",
	"Disco menor no destino" };

/*===== funcao mostra_pinos() ===========================*/
int mostra_pinos() {
int i,j,t;
for(i=0;i<=num_discos;i++) {
	for(j=0;j<3;j++) {
		t=Pino[j][i];
		disco[t]='\0';
		printf("%*s%c%-*s  ",num_discos,disco,
				(t>0)?CHAR_DISCO:CHAR_PINO,
				num_discos,disco );
		disco[t]=CHAR_DISCO;
		}
	printf("\n");
	}
for(j=0;j<3;j++)
	printf("%*s%d%*s  ",num_discos,"",j+1,num_discos,"");
printf("\n");
return 0;
}

/*===== funcao venceu() =================================*/
int venceu() {
int i,soma=0;
for(i=0;i<=num_discos;i++)
	soma+=Pino[0][i]+Pino[1][i];
return (soma>0)?0:1;
}

/*===== funcao move() ===================================*/
int move(int origem, int destino) {
int disco_orig=0, disco_dest=0,i;
int altura_orig, altura_dest;
/*--- consistencia ---*/
if(origem<1||origem>3) {
	printf("Pino de origem invalido!\n");
	return 0;
	}
if(destino<1||destino>3) {
	printf("Pino de destino invalido!\n");
	return 0;
	}
if(origem==destino) {
	printf("Movimento impossivel!\n");
	return 0;
	}
/*--- obtem tamanho do disco de origem ---*/
for(i=0;i<=num_discos;i++)
	if(Pino[origem-1][i]!=0) {
		disco_orig=Pino[origem-1][i];
		altura_orig=i;
		break;
		}
if(disco_orig==0) {
	printf("Pino %d vazio!\n",origem);
	return 0;
	}
/*--- obtem tamanho do disco de destino ---*/
for(i=0;i<=num_discos;i++)
	if(Pino[destino-1][i]!=0) {
		disco_dest=Pino[destino-1][i];
		altura_dest=i;
		break;
		}
if(disco_dest!=0 && disco_dest<disco_orig) {
	printf("Disco menor no pino %d!\n",destino);
	return 0;
	}
if(disco_dest!=0)
	Pino[destino-1][altura_dest-1]=disco_orig;
else
	Pino[destino-1][num_discos]=disco_orig;
Pino[origem-1][altura_orig]=0;
return 1;
}

/*===== funcao main() ===================================*/
int main (int argc, char*argv[]) {
char buffer[10];
int i, jogada, a, b, movimentos=0;

if(argc==2) num_discos=atoi(argv[1]);

if(num_discos<1||num_discos>MAX_DISCOS)
       	num_discos=4; /*--- valor default ---*/

/*--- inicializa os pinos ---*/
for(i=0;i<=num_discos;i++) {
	Pino[0][i]=i;
	Pino[1][i]=0;
	Pino[2][i]=0;
	disco[i]=CHAR_DISCO;
	}
disco[i]='\0';

mostra_pinos();
while (!venceu()) {
	printf("Digite sua jogada (12,13,21,23,31 ou 32):");
	fgets(buffer,5,stdin);
	if(buffer[0]=='q')return 0;
	jogada=atoi(buffer);
	a=jogada/10;
	b=jogada%10;
	if(move(a,b)) {
		movimentos++;
		mostra_pinos();
		}
	}
printf("Parabens! Voce resolveu em %d movimentos!\n",movimentos);
return 1;
}
