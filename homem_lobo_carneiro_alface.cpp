//------- URCAMP - Universidade da Regiao da Campanha
//------- Centro de Ciencias da Economia e Informatica
//------- Curso de Informatica

//------------------------- Inteligencia Artificial -------------------------
//------------------------ Prof.  Alexsander da Rosa ------------------------

//------- Resolvedor de problemas
//------- (por busca em espaco de estados)
//------- Busca cega (sem heuristica) em profundidade

/*
*/

#include <stdio.h>
#include <stdlib.h>

#define HOMEM    8 //----- 1=Esquerda, 0=direita
#define LOBO     4
#define CARNEIRO 2
#define ALFACE   1

#define MostraEstado(x) {putchar('(');\
			if(x&HOMEM)putchar('H');\
			if(x&LOBO)putchar('L');\
			if(x&CARNEIRO)putchar('C');\
			if(x&ALFACE)putchar('A');\
			putchar(',');\
			if(!(x&HOMEM))putchar('H');\
			if(!(x&LOBO))putchar('L');\
			if(!(x&CARNEIRO))putchar('C');\
			if(!(x&ALFACE))putchar('A');\
			putchar(')');}

//------- estrutura geral do nodo
struct nodo
    {
    char estado;
    struct nodo *pai, *irmao, *filho; // parte "geral"
    };
struct nodo *raiz; //raiz da arvore de busca
unsigned int solucoes = 0;
int debug = 0;

//------- definicao do estado final
int EstadoFinal = 0x00;

//---------------------------------------------------------------------------
void Expande_Arvore ( struct nodo *atual )
{
int novo_estado;
int i, criou, ok;
struct nodo *novo, *anterior = NULL, *volta;
int sem_filhos = 1;

if ( debug ) //------- mostra todos os estados criados
    MostraEstado(atual->estado);

//------- verifica se o estado final foi atingido
if ( atual->estado == EstadoFinal )
    {
    if ( debug )
	printf ( "$\n" ); //----- indicador de nodo terminal (solucao)
    //------- percorre toda a arvore, voltando ateh o estado inicial
    volta = atual; // inicia no atual
    while ( volta != NULL ) // enquanto tem pai
	{
	//------- mostra estado por estado
	MostraEstado(volta->estado);
	putchar ( 0x1b );
	volta = volta->pai;
	}
    printf ( "\n" );
    solucoes++;
    }

//------ "for" que percorre todos os estados possiveis
//------ Neste caso, dos baldes, sao:
//     0: move H  p/ direita
//     1: move HL p/ direita
//     2: move HC p/ direita
//     3: move HA p/ direita
//     4: move H  p/ esquerda
//     5: move HL p/ esquerda
//     6: move HC p/ esquerda
//     7: move HA p/ esquerda

for ( i = 0; i < 8; i++ ) //------- nesse caso, sao 8
    {
    criou = 0;
    switch ( i )
	{
	case 0:                      //----- move H->
	    if ( atual->estado&HOMEM ) //----- 1xxx
		{
		novo_estado = atual->estado - HOMEM;
		criou = 1;
		}
	    break;
	case 1:                      //----- move HL->
	    if ( atual->estado&HOMEM && atual->estado&LOBO ) //----- 11xx
		{
		novo_estado = atual->estado - HOMEM - LOBO;
		criou = 1;
		}
	    break;
	case 2:                      //----- move HC->
	    if ( atual->estado&HOMEM && atual->estado&CARNEIRO ) //----- 1x1x
		{
		novo_estado = atual->estado - HOMEM - CARNEIRO;
		criou = 1;
		}
	    break;
	case 3:                      //----- move HA->
	    if ( atual->estado&HOMEM && atual->estado&ALFACE ) //----- 1xx1
		{
		novo_estado = atual->estado - HOMEM - ALFACE;
		criou = 1;
		}
	    break;
	case 4:                      //----- move <-H
	    if ( !(atual->estado&HOMEM) ) //----- 0xxx
		{
		novo_estado = atual->estado + HOMEM;
		criou = 1;
		}
	    break;
	case 5:                      //----- move HL->
	    if ( !(atual->estado&HOMEM) && !(atual->estado&LOBO) ) //----- 00xx
		{
		novo_estado = atual->estado + HOMEM + LOBO;
		criou = 1;
		}
	    break;
	case 6:                      //----- move HC->
	    if ( !(atual->estado&HOMEM) && !(atual->estado&CARNEIRO) ) //----- 0x0x
		{
		novo_estado = atual->estado + HOMEM + CARNEIRO;
		criou = 1;
		}
	    break;
	case 7:                      //----- move HA->
	    if ( !(atual->estado&HOMEM) && !(atual->estado&ALFACE) ) //----- 0xx0
		{
		novo_estado = atual->estado + HOMEM + ALFACE;
		criou = 1;
		}
	    break;
	}

    switch ( novo_estado ) //----- o que pode estar no lado esquerdo
	{
	case HOMEM:                //--- H,LCA
	case HOMEM+LOBO:           //--- HL,CA
	case HOMEM+ALFACE:         //--- HA,LC
	case LOBO+CARNEIRO:        //--- LC,HA
	case CARNEIRO+ALFACE:      //--- CA,HL
	case LOBO+CARNEIRO+ALFACE: //--- LCA,H
	  criou = 0;
	  break;
	}

    if ( criou ) // se foi encontrado um "movimento" valido
	{
	//------- testa se jah existe um antepassado igual
	ok = 1;
	volta = atual; // inicia no atual
	while ( volta != NULL ) // enquanto ainda tem pai
	    {
	    if ( volta->estado == novo_estado )
		{ ok = 0; break; } // se jah existe, ok=0
	    volta = volta->pai; // volta para o pai
	    }

	if ( ok ) //------- se tudo Ok (nao existe ainda)
	    {
	    //------- cria o novo nodo
	    novo = new (struct nodo);
	    if ( novo == NULL )
		{
		printf ( "Sem mem¢ria dispon¡vel!\n" );
		exit ( EXIT_FAILURE ); //----- aborta em caso de erro fatal
		}
	    novo->estado = novo_estado;
	    novo->pai = atual; //aponta para o pai
	    novo->irmao = NULL;
	    novo->filho = NULL;

	    if ( atual->filho == NULL ) //se eh o primogenito
		atual->filho = novo; // entao o pai aponta pra ele
	    else
		anterior->irmao = novo; // senao o irmao aponta pra ele


	    Expande_Arvore ( novo ); //------- busca em PROFUNDIDADE

	    anterior = novo; // move o "anterior"

	    if ( debug ) //---- somente para debug
		sem_filhos = 0;
	    }
	}
    }

if ( debug && sem_filhos ) // se for um nodo terminal mas nao for solucao
    printf ( "#\n" ); //----- indicador de nodo terminal (nao solucao)

return;
}

//---------------------------------------------------------------------------
void main ( int argc, char *argv[] )
{
printf ( "HLCA - Resolvedor de problemas espec¡ficos\n" );
printf ( "Busca em espa‡o de estados - Busca Cega em profundidade\n" );
if ( argc != 4 )
    {
    printf ( "Sintaxe: HLCA <tipo> <EI> <EF>\n" );
    printf ( "  onde <tipo> pode ser 'n' (normal) ou 'd' (debug)\n" );
    return;
    }

if ( ( argv[1][0] | 0x20 ) == 'd' )
    {
    debug = 1;
    printf ( "Modo DEBUG ativado.\n" );
    }

EstadoFinal = atoi ( argv[3] );

raiz = new (struct nodo);
raiz->estado = atoi ( argv[2] );
raiz->pai = raiz->irmao = raiz->filho = NULL;

Expande_Arvore ( raiz ); // cria a arvore de busca

printf ( "Total: %u solu‡%s.\n", solucoes, solucoes == 1 ? "„o" : "”es" );
}
