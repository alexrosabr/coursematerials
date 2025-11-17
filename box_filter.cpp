//---------------------------------------------------------------------------
// Universidade da Regiao da Campanha
// Prof. Alexsander da Rosa
// Programa para aplicar um "box filter"
//---------------------------------------------------------------------------

#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>

//---------------------------------------------------------------------------
unsigned char aux;
int filtro[3][3] = {
  1, 1, 1,
  1, 1, 1,
  1, 1, 1 };

//---------------------------------------------------------------------------
int huge detectVGA256 ( void );
void checkerrors ( void );

//---------------------------------------------------------------------------
void main ( void )
{
unsigned char *imagem;
int i, x, y, val;
int gdriver, gmode;

//------- instala um 'device driver' externo
gdriver = installuserdriver ( "VGA256", detectVGA256 );

//------- tem que usar a rotina de 'auto-detect'
gdriver = DETECT;

//------- verifica os erros da ultima operacao grafica
checkerrors ( );

//------- inicializa modo grafico
initgraph ( &gdriver, &gmode, "" );

//------- verifica os erros da ultima operacao grafica
checkerrors ( );

//------- Palheta 'default'
setcolor ( 0x0f ); //--- branco na palheta 'default'
cleardevice ( );

setrgbpalette ( 255, 63, 0, 0 );
setcolor ( 255 );
circle ( 160, 100, 50 );

//------- Palheta de 256 tons de cinza
for ( i = 0; i < 256; i++ )
    setrgbpalette ( i, i/4, i/4, i/4 );

//----- Aloca memoria para a imagem
imagem = (char*)malloc(64000);
if ( imagem == NULL ) {
  printf ( "Imagem muito grande!\n" );
  exit(1);
  }
//----- limpa a imagem
for ( x = 0; x < 320; x++ )
  for ( y = 0; y < 200; y++ )
    imagem[x+320*y] = 0;

for ( x = 1; x < 319; x++ )
  {
  for ( y = 1; y < 199; y++ )
    {
    val = 0;
    val += getpixel ( x-1, y-1 ) * filtro[0][0];
    val += getpixel ( x-1, y )   * filtro[0][1];
    val += getpixel ( x-1, y+1 ) * filtro[0][2];

    val += getpixel ( x  , y-1 ) * filtro[1][0];
    val += getpixel ( x  , y )   * filtro[1][1];
    val += getpixel ( x  , y+1 ) * filtro[1][2];

    val += getpixel ( x+1, y-1 ) * filtro[2][0];
    val += getpixel ( x+1, y )   * filtro[2][1];
    val += getpixel ( x+1, y+1 ) * filtro[2][2];
    val = val / 6;

    imagem[x+320*y] = val;
    }
  putpixel(x-1,199,0);
  putpixel(x,199,255);
  }

for ( x = 0; x < 320; x++ )
  for ( y = 0; y < 200; y++ )
    putpixel ( x, y, imagem[x+320*y] );

if ( getch ( ) == 0 ) getch ( );

closegraph ( );
return;
}

//---------------------------------------------------------------------------
// Detecta placas VGA com capacidade para 256 cores
//---------------------------------------------------------------------------
int huge detectVGA256 ( void )
{
int driver, mode, sugmode = 0;

detectgraph ( &driver, &mode );
if ( driver == VGA )
    return ( sugmode ); //------- retorna numero do modo de video sugerido
else
    return ( grError ); //------- retorna um codigo de erro
}

//---------------------------------------------------------------------------
// Verifica (e mostra) a ocorrencia de erros graficos
//---------------------------------------------------------------------------
void checkerrors ( void )
{
int errorcode;

errorcode = graphresult ( ); //------- resultado da ultima operacao grafica
if ( errorcode != grOk )
    {
    printf ( "Erro gr fico: \"%s\"\n", grapherrormsg ( errorcode ) );
    printf ( "Pressione qualquer tecla para abortar..." );
    if ( getch ( ) == 0 ) getch ( );
    exit ( EXIT_FAILURE );
    }
}
