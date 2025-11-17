//------- URCAMP - Universidade da Regiao da Campanha
//------- Centro de Ciencias da Economia e Informatica
//------- Curso de Informatica

//------------------------- Inteligencia Artificial -------------------------
//------------------------ Prof.  Alexsander da Rosa ------------------------

//------- Resolvedor de problemas
//------- (por busca em espa‡o de estados)
//------- Busca cega (sem heuristica) em profundidade

/*
*/

#include <stdio.h>
#include <stdlib.h>

//------- estrutura geral do nodo
struct nodo
    {
    int m, c, b; // (3,3,1) -> (0,0,0)
    struct nodo *pai, *irmao, *filho; // parte "geral"
    };
struct nodo *raiz; //raiz da arvore de busca
unsigned int solucoes = 0;
int debug = 0;

//------- definicao do estado final
int EstadoFinalm = 0; //----- nenhum missionario, nenhum canibal e
int EstadoFinalc = 0; //      nenhum barco do lado onde eles comecaram
int EstadoFinalb = 0;

//---------------------------------------------------------------------------
void Expande_Arvore ( struct nodo *atual )
{
int nm, nc, nb;
int i, criou, ok;
struct nodo *novo, *anterior = NULL, *volta;
int sem_filhos = 1;

if ( debug ) //------- mostra todos os estados criados
    printf ( "(%d,%d,%d) ", atual->m, atual->c, atual->b );

//------- verifica se o estado final foi atingido
if ( atual->m == EstadoFinalm && atual->c == EstadoFinalc
     && atual->b == EstadoFinalb )
    {
    if ( debug )
	printf ( "$\n" ); //----- indicador de nodo terminal (solucao)
    //------- percorre toda a arvore, voltando ateh o estado inicial
    volta = atual; // inicia no atual
    while ( volta != NULL ) // enquanto tem pai
	{
	//------- mostra estado por estado
	printf ( "(%d,%d,%d)", volta->m, volta->c, volta->b );
	putchar ( 0x1b );
	volta = volta->pai;
	}
    printf ( "\n" );
    solucoes++;
    }

//------ "for" que percorre todos os estados possiveis
//------ Neste caso, sao:
//     0: move C ->
//     1: move CC ->
//     2: move M ->
//     3: move MM ->
//     4: move MC ->

//     5: move <- C
//     6: move <- CC
//     7: move <- M
//     8: move <- MM
//     9: move <- MC

for ( i = 0; i < 10; i++ ) //------- nesse caso, sao 10
    {
    criou = 0;
    nm = atual->m;
    nc = atual->c;
    nb = atual->b;
    switch ( i )
	{
	case 0:                      //----- move C->
	    if ( atual->b > 0 && atual->c >= 1 )
		{
		nc = atual->c - 1; //---- vai um C para a dir.
		nb = atual->b - 1;
		criou = 1;
		}
	    break;
	case 1:                      //----- move CC->
	    if ( atual->b > 0 && atual->c >= 2 )
		{
		nc = atual->c - 2; //---- vai dois C para a dir.
		nb = atual->b - 1;
		criou = 1;
		}
	    break;
	case 2:                      //----- move M->
	    if ( atual->b > 0 && atual->m >= 1 )
		{
		nm = atual->m - 1; //---- vai um M para a dir.
		nb = atual->b - 1;
		criou = 1;
		}
	    break;
	case 3:                      //----- move MM->
	    if ( atual->b > 0 && atual->m >= 2 )
		{
		nm = atual->m - 2; //---- vai dois M para a dir.
		nb = atual->b - 1;
		criou = 1;
		}
	    break;
	case 4:                      //----- move MC->
	    if ( atual->b > 0 && atual->m >= 1 && atual->c >= 1 )
		{
		nm = atual->m - 1; //---- vai um M para a dir.
		nc = atual->c - 1; //---- vai um C para a dir.
		nb = atual->b - 1;
		criou = 1;
		}
	    break;

	case 5:                      //----- move <-C
	    if ( atual->b == 0 && atual->c < 3 )
		{
		nc = atual->c + 1; //---- vai um C para a esq.
		nb = atual->b + 1;
		criou = 1;
		}
	    break;
	case 6:                      //----- move <-CC
	    if ( atual->b == 0 && atual->c < 2 )
		{
		nc = atual->c + 2; //---- vai dois CC para a esq.
		nb = atual->b + 1;
		criou = 1;
		}
	    break;
	case 7:                      //----- move M->
	    if ( atual->b == 0 && atual->m < 3 )
		{
		nm = atual->m + 1; //---- vai um M para a esq.
		nb = atual->b + 1;
		criou = 1;
		}
	    break;
	case 8:                      //----- move MM->
	    if ( atual->b == 0 && atual->m < 2 )
		{
		nm = atual->m + 2; //---- vai dois M para a esq.
		nb = atual->b + 1;
		criou = 1;
		}
	    break;
	case 9:                      //----- move MC->
	    if ( atual->b == 0 && atual->m < 3 && atual->c < 3 )
		{
		nm = atual->m + 1; //---- vai um M para a esq.
		nc = atual->c + 1; //---- vai um C para a esq.
		nb = atual->b + 1;
		criou = 1;
		}
	    break;
	}

    //----- testa se e' valido
    if ( nc > 0 && nm > 0 && nc > nm ) //---- tem C na esq. e NCesq > NMesq?
	criou = 0;
    if ( nc < 3 && nm < 3 && nc < nm ) //---- tem C na dir. e NCdir > NMdir?
	criou = 0;

    if ( criou ) // se foi encontrado um "movimento" valido
	{
	//------- testa se jah existe um antepassado igual
	ok = 1;
	volta = atual; // inicia no atual
	while ( volta != NULL ) // enquanto ainda tem pai
	    {
	    if ( volta->m == nm && volta->c == nc && volta->b == nb )
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
	    novo->c = nc;
	    novo->m = nm;
	    novo->b = nb;
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
printf ( "CANIBAIS - Resolvedor de problemas espec¡ficos\n" );
printf ( "Busca em espa‡o de estados - Busca Cega em profundidade\n" );

if ( ( argv[1][0] | 0x20 ) == 'd' )
    {
    debug = 1;
    printf ( "Modo DEBUG ativado.\n" );
    }

raiz = new (struct nodo);
raiz->m = 3;
raiz->c = 3;
raiz->b = 1;
raiz->pai = raiz->irmao = raiz->filho = NULL;

Expande_Arvore ( raiz ); // cria a arvore de busca

printf ( "Total: %u solu‡%s.\n", solucoes, solucoes == 1 ? "„o" : "”es" );
}
