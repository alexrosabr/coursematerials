#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
double pi=4.0,termo=3.0;
unsigned long int i, iteracoes;

if(argc!=2){
  printf("Digite o numero de iteracoes\n");
  return 0;
  }
iteracoes=atol(argv[1]);
printf("Calculando PI em %lu iteracoes...\n",iteracoes);
for(i=0;i<iteracoes;i++){
  if(i%2) /*-- impar */
    pi+=4.0/termo;
  else
    pi-=4.0/termo;
  termo+=2.0;
  }
printf("PI=%.17lf\n",pi);
return 1;
}
