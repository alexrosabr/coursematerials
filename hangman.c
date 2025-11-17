/* Urcamp/CCEI/Informatica/Prog.II
 * Prof. Alexsander da Rosa
 * Programa exemplo 2 (segunda parte):
 * Forca (hangman) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO	"palavras.txt"
#define MAX	100

int main() {
FILE *arq;
char palavra[MAX][40], secreta[40], buffer[40], letra;
int i, tam, total=0, sorteada, erros=0, achou;

/*--- carrega palavras ---*/
arq=fopen(ARQUIVO,"rt");
if (!arq) {
	printf("Arquivo '%s' nao encontrado.\n",ARQUIVO);
	return 0;
	}
while (!feof(arq)) {
	if(fscanf(arq,"%s",buffer)!=1)
		break;
	tam=strlen(buffer);
	for(i=0;i<tam;i++)
		if(buffer[i]=='_') buffer[i]=' ';
	strcpy(palavra[total],buffer);
	total++;
	}
fclose (arq);

/*--- sorteia uma palavra ---*/
srand(time(NULL));
sorteada = rand()%total;
tam=strlen(palavra[sorteada]);
for(i=0;i<tam;i++)
	if(palavra[sorteada][i]==' ')
		secreta[i]=' ';
	else
		secreta[i]='_';
secreta[i]='\0';

/*--- laco principal ---*/
while (erros<7) {
	printf("%s (%d)> ",secreta,erros);
	fgets(buffer,40,stdin);
	letra=toupper(buffer[0]);
	achou=0;
	for(i=0;i<tam;i++)
		if(palavra[sorteada][i]==letra) {
			secreta[i]=letra;
			achou=1;
			}
	if (!achou) erros++;
	if (strcmp(secreta,palavra[sorteada])==0) {
		printf("Parabens!\n");
		break;
		}
	}

return 1;
}
