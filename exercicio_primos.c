#include <stdio.h>

int primo ( int x )
{
int i;
for(i=2;i<x;i++)
  if(x%i==0) return 0;
return 1;
}

int main ( int argc, char *argv[] )
{
FILE *arq;
int i;

if(argc!=2) {
  printf("Digite um nome de arquivo\n");
  return 0;
  }
arq=fopen(argv[1],"rb");     /*--- tenta abrir para leitura ---*/
if(arq){
  printf("Arquivo '%s' ja' existe. Abortando.\n",argv[1]);
  fclose(arq);
  return 0;
  }
arq=fopen(argv[1],"wt");     /*--- abre para gravar ---*/
if(!arq){
  printf("Impossivel criar arquivo '%s'.\n",argv[1]);
  return 0;
  }
for(i=2;i<1000;i++)          /*--- faz o laco de 2 ate' 1000 ---*/
  if(primo(i))               /*--- se for primo ---*/
    fprintf(arq,"%d\n",i);   /*--- grava no arquivo ---*/
fclose(arq);
return 1;
}
