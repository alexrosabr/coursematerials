/*----- Exemplo de Classe
        Classe Recordes

        URCAMP - Universidade da Regiao da Campanha
        Prof. Alexsander da Rosa
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>

//----- definicao da classe
#define MAX 5           //----- a constante "MAX" define o numero de recordes
class Recordes {
  struct Dados {
    int pontos;
    char nome[11];      //----- ex.: strcpy(tabela[i].nome,"Aluno");
    } tabela[MAX];      //           tabela.pontos = 0;
  public:
  Recordes(void);
  ~Recordes(void);
  void Testar(int valor);
  void Mostrar(void);
  };

//----- implementacao -----
//----- construtor
Recordes::Recordes(void)
{
FILE *arq;
int i;
arq = fopen("RECORDES.DAT","rb"); //----- tenta abrir para leitura
if ( arq == NULL ) 
  {
  for ( i = 0; i < MAX; i++ ) //----- se nao existe, cria um 
    {
    tabela[i].pontos = MAX-i;
    strcpy(tabela[i].nome,"Vazio");
    }
  }
else //----- senao (se conseguiu abrir)
  {
  for ( i = 0; i < MAX; i++ )
    fscanf(arq,"%d %s",&tabela[i].pontos,tabela[i].nome);
  fclose(arq);
  }
}

//----- destrutor
Recordes::~Recordes(void)
{
FILE *arq;
int i;
arq = fopen("RECORDES.DAT","wb"); //----- abre para escrita (sobrepondo)
if ( arq != NULL ) //----- se deu certo
  {
  for ( i = 0; i < MAX; i++ )
    fprintf(arq,"%d %s\n",tabela[i].pontos,tabela[i].nome);
  fclose(arq);
  }
}

//----- Mostrar
void Recordes::Mostrar(void)
{
int i;
printf("Recordes:\n");
for ( i = 0; i < MAX; i++ )
  printf("%2d%c %5d %s\n", i+1, 167, tabela[i].pontos, tabela[i].nome );
return;
}

//----- Testar
void Recordes::Testar(int valor)
{
int i, j;
for ( i = 0; i < MAX; i++ ) //----- percorre a tabela de cima p/ baixo
  {
  if ( valor > tabela[i].pontos ) //----- se valor for maior
    {
    for ( j = MAX-1; j > i; j-- ) //---- vai do fim pro inicio
      {
      tabela[j].pontos = tabela[j-1].pontos; //----- empurro para baixo
      strcpy(tabela[j].nome,tabela[j-1].nome);
      }
    tabela[i].pontos = valor;
    printf ( "Voce bateu o %d%c recorde! Digite seu nome:", i+1, 167 );
    scanf("%s",tabela[i].nome); //----- pede o nome (sem consistencia...)
    break; //----- sai do for
    }
  }
return;
}
//----- fim da implementacao da classe -----




void main ( )
{
int pontos;
Recordes melhores; //----- cria um objeto (chamado "melhores") que e' uma
                   //      instancia da classe "Recordes"

clrscr(); //---- da conio.h (limpa a tela)

melhores.Mostrar(); //----- mostra a tabela atual

printf ("Quantos pontos voce fez?\n" ); //----- solicita os pontos
scanf("%d",&pontos);

melhores.Testar(pontos); //----- testa e imprime a tabela atualizada
melhores.Mostrar();

getch(); //---- da conio.h (espera uma tecla)
}
