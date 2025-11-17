//---------------------------------------------------------------------------
// Programa para exibir a palheta 256 cores
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

//---------------------------------------------------------------------------
void MostraPalheta ( void );
int huge detectVGA256 ( void );
void checkerrors ( void );

//---------------------------------------------------------------------------
void main ( void )
{
int i;
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
MostraPalheta ( );
if ( getch ( ) == 0 ) getch ( );

//------- Palheta de 256 tons de cinza
for ( i = 0; i < 256; i++ )
    setrgbpalette ( i, i/4, i/4, i/4 );
if ( getch ( ) == 0 ) getch ( );

//------- Palheta de 64 tons de cinza, vermelho, verde e azul
for ( i = 0; i < 64; i++ )
    {
    setrgbpalette (     i, i, i, i ); //------- cinza    (64x0=0)
    setrgbpalette (  64+i, i, 0, 0 ); //------- vermelho (64x1=64)
    setrgbpalette ( 128+i, 0, i, 0 ); //------- verde    (64x2=128)
    setrgbpalette ( 192+i, 0, 0, i ); //------- azul     (64x3=192)
    }
if ( getch ( ) == 0 ) getch ( );

closegraph ( );
return;
}

//---------------------------------------------------------------------------
// Mostra a palheta
//---------------------------------------------------------------------------
void MostraPalheta ( void )
{
int i, x, y;

for ( i = 0; i < 256; i++ )
    {
    setfillstyle ( SOLID_FILL, i );

    x = 20*(i%16);
    y = 12*(i/16);
    bar ( x, y, x+20, y+12 );
    rectangle ( x, y, x+20, y+12 );
    }

rectangle ( 0, 0, 319, 199 );
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
    printf ( "Erro gr fico: \"%s\"\n", grapherrormsg ( errorcode ) );
    printf ( "Pressione qualquer tecla para abortar..." );
    if ( getch ( ) == 0 ) getch ( );
    exit ( EXIT_FAILURE );
    }
}

