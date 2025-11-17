#include <stdio.h>
#include <string.h>

struct Cartao
    {
    char palavra[30];
    unsigned cont;
    struct Cartao *proxima;
    };
struct Cartao *inicio, *nova, *anterior, *atual;

//---------------------------------------------------------------------------
void main ( int argc, char *argv[] )
{
//struct Cartao *aux;
char pal[500];
FILE *arq;

if ( argc != 2 )
    {
    printf ( "Sintaxe: CONTPAL2 <nome-do-arquivo>\n" );
    return;
    }

arq = fopen ( argv[1], "rt" );
if ( arq == NULL )
    {
    printf ( "Arquivo '%s' n„o encontrado!\n", argv[1] );
    return;
    }

anterior = inicio = NULL;
while ( !feof ( arq ) )
    {
    fscanf ( arq, "%s", pal );

    //----- verifica se nao eh muito grande
    if ( strlen ( pal ) > 29 )
	continue;

    //----- procura a palavra na lista
    atual = inicio;
    while ( atual != NULL )
	{
	if ( stricmp ( pal, atual->palavra ) == 0 ) // achou
	    { atual->cont++; break; }
	atual = atual->proxima;
	}

    //----- se nao achou
    if ( atual == NULL )
	{
	nova = new ( struct Cartao );
	if ( nova == NULL )
	    { printf ( "Sem mem¢ria!\n" ); return; }
	//----- preenche os dados
	strcpy ( nova->palavra, pal );
	nova->cont = 1;

	//----- procura o lugar da palavra
	atual = anterior = inicio;
	while ( atual != NULL )
	    {
	    if ( stricmp ( pal, atual->palavra ) < 0 ) // achou
		break;
	    anterior = atual;
	    atual = atual->proxima;
	    }

	if ( atual == inicio ) //----- e' no inicio
	    {
	    nova->proxima = inicio;
	    inicio = nova;
	    }
	else
	    {
	    if ( atual == NULL ) //----- e' no fim?
		{
		anterior->proxima = nova;
		nova->proxima = NULL;
		}
	    else //----- entao e' no meio.
		{
		anterior->proxima = nova;
		nova->proxima = atual;
		}
	    } // end if
	} //end if
    } //end while

fclose ( arq );

//----- imprime a relacao
atual = inicio;
while ( atual != NULL )
    {
    printf ( "%s(%d) ", atual->palavra, atual->cont );
    atual = atual->proxima;
    }

printf ( "\n" );

}
