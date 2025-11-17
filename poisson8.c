//----- Problema das Jarras de Vinho (Simeon Poisson)
// Enunciado: Dividir entre dois amigos uma jarra de vinho de 8 litros (A),
//   usando apenas outras duas jarras - uma de 5 litros (B) e outra com
//   3 litros (C). Nenhuma delas apresenta marcas ou divisoes.
// 
// (Publicado na revista SUPERINTERESSANTE 151 - Ano 14 No. 4, Abril/2000)
//
//              A          B         C
//           |     |
//           |     |    |     |    |   |
//           |  8  |    |  5  |    | 3 |
//           \_____/    \_____/    \___/
//
// Copyleft (C) 2000 por Alexsander da Rosa <alexsand@urcamp.tche.br>
// Home-Page: http://www.urcamp.tche.br/~alexsand/
//
// Este programa esta' licenciado pela GPL - GNU General Public License
// Para maiores detalhes veja em:
// http://www.gnu.org/copyleft/gpl.html (original)
// http://lie-br.conectiva.com.br/licenca_gnu.html (em portugues)
//
// Desenvolvido usando vi e gcc (egcs 2.91.66) num Linux 2.2.14 e 
// testado no Borland Turbo C++ 3.0 num MS-Windows 98.
//-----
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OPS 6

//----- estrutura nodo da arvore de busca
struct Nodo {
  int depth, op, j8, j5, j3;
  struct Nodo *pai;
  }*volta;
char *DescOp[7] = {
  "Estado Inicial (A,B,C)",
  "Transferiu de A para B",
  "Transferiu de A para C",
  "Transferiu de B para A",
  "Transferiu de B para C",
  "Transferiu de C para A",
  "Transferiu de C para B" };
int solucoes=0, debug=0;

//----- funcao que mostra a solucao
void MostraSolucao(struct Nodo *s)
{
if(!s)return;
MostraSolucao(s->pai);
printf("%d-%s (%d,%d,%d)\n",s->op,DescOp[s->op],s->j8,s->j5,s->j3);
}

//----- Busca cega em profundidade (algoritmo recursivo padrao)
// (com controle de nodos repetidos por verificacao de antecessores)
//----- funcao de expansao de nodo
void Expande(struct Nodo *n)
{
int i, ok, criou, transf, b8, b5, b3, oper;
struct Nodo *novo;

if(n->j8==4&&n->j5==4){ //----- goal test
  printf("----- SOLUCAO %d:\n",++solucoes);
  MostraSolucao(n);
  printf("----- Profundidade: %d\n\n",n->depth);
  return;
  }
if(debug) { //----- debug mode
  printf("%*s%d - (%d) %s [%d,%d,%d]\n",2*n->depth,"",n->depth,n->op,
    DescOp[n->op],n->j8,n->j5,n->j3);
  }
for (i=0;i<NUM_OPS;i++) {
  criou=0;
  b8=n->j8;
  b5=n->j5;
  b3=n->j3;
  switch(i) {
    case 0: //---- transfere de b8 para b5
      if(b8>0&&b5<5) {
        transf = 5-b5;
        if(transf>b8)transf=b8;
        b5+=transf;
        b8-=transf;
        oper=i+1;
        criou=1;
        }
      break;
    case 1: //---- transfere de b8 para b3
      if(b8>0&&b3<3) {
        transf = 3-b3;
        if(transf>b8)transf=b8;
        b3+=transf;
        b8-=transf;
        oper=i+1;
        criou=1;
        }
      break;
    case 2: //---- transfere de b5 para b8
      if(b5>0&&b8<8) {
        transf = 8-b8;
        if(transf>b5)transf=b5;
        b8+=transf;
        b5-=transf;
        oper=i+1;
        criou=1;
        }
      break;
    case 3: //---- transfere de b5 para b3
      if(b5>0&&b3<3) {
        transf = 3-b3;
        if(transf>b5)transf=b5;
        b3+=transf;
        b5-=transf;
        oper=i+1;
        criou=1;
        }
      break;
    case 4: //---- transfere de b3 para b8
      if(b3>0&&b8<8) {
        transf = 8-b8;
        if(transf>b3)transf=b3;
        b8+=transf;
        b3-=transf;
        oper=i+1;
        criou=1;
        }
      break;
    case 5: //---- transfere de b3 para b5
      if(b3>0&&b5<5) {
        transf = 5-b5;
        if(transf>b3)transf=b3;
        b5+=transf;
        b3-=transf;
        oper=i+1;
        criou=1;
        }
      break;
    default:break;
    }
  if(criou) {
    volta=n->pai; //------- testa se jah existe um antepassado igual
    ok = 1;
    while(volta) {
      if ( volta->j8==b8 && volta->j5==b5 && volta->j3==b3 ) {
	ok = 0; break;
        } // se jah existe, ok=0
      volta = volta->pai; // volta para o pai
      }
    if(ok) { //----- ok, aloca nodo e o expande em seguida
      novo=malloc((size_t)sizeof(struct Nodo));
      if(!novo){printf("Programa abortado!\n");exit(EXIT_FAILURE);}
      novo->pai=n;
      novo->j8=b8;
      novo->j5=b5;
      novo->j3=b3;
      novo->op=oper;
      novo->depth = n->depth+1;
      Expande(novo);
      }
    }
  }
return;
}

//----- programa principal
int main (int argc, char *argv[])
{
struct Nodo *raiz;
if(argc==2&&!strcmp(argv[1],"-d"))debug=1;
raiz=malloc((size_t)sizeof(struct Nodo));
if(!raiz){printf("Programa abortado!\n");exit(EXIT_FAILURE);}
raiz->pai = NULL;
raiz->j8 = 8;
raiz->j5 = raiz->j3 = 0;
raiz->op = raiz->depth = 0;
Expande(raiz);
printf("Encontrou %d solucoes.\n",solucoes);
return 1;
}
