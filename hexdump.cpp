#include <stdio.h>
#include <ctype.h>

void main ( int argc, char *argv[] )
{
FILE *arq;
int i, tam;
unsigned long pos = 0L;
unsigned char linha[16];

if ( argc != 2 ) {
  printf ( "Sintaxe: HEXDUMP <arquivo>\n" );
  return;
  }
arq = fopen ( argv[1], "rb" );
if (arq==NULL) { 
  printf ( "Erro abrindo '%s'.\n", argv[1] );
  return;
  }
while ( !feof(arq) ) {
  tam = fread ( linha, 1, 16, arq );
  printf ( "%07lu ", pos );
  pos += 16;
  for ( i = 0; i < 16; i++ )
    if ( i < tam )
      printf ( "%02X ", linha[i] );
    else
      printf ( "   " );
  for ( i = 0; i < tam; i++ )
    printf ( "%c", isprint(linha[i])?linha[i]:'.' );
  printf ( "\n" );
  }
fclose (arq);
}
