//---------------------------------------------------------------------------
// Programa para exibir as combinacoes de RGB
//---------------------------------------------------------------------------

#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>

//---------------------------------------------------------------------------
#define ESC	27

#define LEFT	75
#define	RIGHT	77
#define UP	72
#define	DOWN	80

#define HOME	71
#define	END	79
#define PGUP	73
#define	PGDN	81
#define	INS	82
#define	DEL	83

//---------------------------------------------------------------------------
int huge detectVGA256 ( void );
void checkerrors ( void );

//---------------------------------------------------------------------------
void main ( void )
{
int gdriver, gmode, i, tecla = 0, ext;
int red, green, blue, moveu, verm, verde, azul;
char buff[4];

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

cleardevice ( );
settextjustify ( CENTER_TEXT, CENTER_TEXT );
setwritemode ( COPY_PUT );

setrgbpalette ( 0, 0, 0, 0 );
setrgbpalette ( 1, 63, 63, 63 );
setrgbpalette ( 3, 63, 0, 0 );
setrgbpalette ( 4, 0, 63, 0 );
setrgbpalette ( 5, 0, 0, 63 );
setfillstyle ( SOLID_FILL, 1 );
bar ( 20, 10, 250, 140 );

red = green = blue = 63;
verm = verde = azul = 63;

setrgbpalette ( 2, 63, 63, 63 );
setcolor ( 2 );
rectangle ( 19, 9, 251, 141 );

setcolor ( 3 );
line ( 260, 8, 260, 140 );
strcpy ( buff, "R" );
outtextxy ( 260, 150, buff );

setcolor ( 4 );
line ( 280, 8, 280, 140 );
strcpy ( buff, "G" );
outtextxy ( 280, 150, buff );

setcolor ( 5 );
line ( 300, 8, 300, 140 );
strcpy ( buff, "B" );
outtextxy ( 300, 150, buff );

setcolor ( 2 );
strcpy ( buff, "0" );
outtextxy ( 310, 10, buff );
strcpy ( buff, "10" );
outtextxy ( 310, 30, buff );
strcpy ( buff, "20" );
outtextxy ( 310, 50, buff );
strcpy ( buff, "30" );
outtextxy ( 310, 70, buff );
strcpy ( buff, "40" );
outtextxy ( 310, 90, buff );
strcpy ( buff, "50" );
outtextxy ( 310, 110, buff );
strcpy ( buff, "63" );
outtextxy ( 310, 138, buff );

settextjustify ( LEFT_TEXT, CENTER_TEXT );
outtextxy ( 20, 170, "Use o teclado num‚rico:" );
outtextxy ( 261, 170, "7 8 9" );
outtextxy ( 261, 180, "4 5 6" );

setwritemode ( COPY_PUT );

for ( i = 0; i < 64; i++ )
    {
    setcolor ( 3 );
    if ( i % 5 )
	line ( 259, 10+i*2, 261, 10+i*2 );
    else
	line ( 258, 10+i*2, 262, 10+i*2 );

    setcolor ( 4 );
    if ( i % 5 )
	line ( 279, 10+i*2, 281, 10+i*2 );
    else
	line ( 278, 10+i*2, 282, 10+i*2 );

    setcolor ( 5 );
    if ( i % 5 )
	line ( 299, 10+i*2, 301, 10+i*2 );
    else
	line ( 298, 10+i*2, 302, 10+i*2 );
    }

setcolor ( 2 );

moveu = 0;

setwritemode ( XOR_PUT );
line ( 255, 136, 265, 136 );
line ( 275, 136, 285, 136 );
line ( 295, 136, 305, 136 );

while ( tecla != ESC )
    {
    ext = 1;
    tecla = getch ( );
    if ( tecla == 0 )
	ext = getch ( );

    if ( ext == LEFT && red < 63 )
	{
	red++;
	moveu = 1;
	}

    if ( ext == 76 && green < 63 )
	{
	green++;
	moveu = 1;
	}

    if ( ext == RIGHT && blue < 63 )
	{
	blue++;
	moveu = 1;
	}

    if ( ext == HOME && red > 0 )
	{
	red--;
	moveu = 1;
	}

    if ( ext == UP && green > 0 )
	{
	green--;
	moveu = 1;
	}

    if ( ext == PGUP && blue > 0 )
	{
	blue--;
	moveu = 1;
	}

    if ( moveu )
	{
	line ( 255, 10+verm*2, 265, 10+verm*2 );
	verm = red;
	line ( 255, 10+verm*2, 265, 10+verm*2 );

	line ( 275, 10+verde*2, 285, 10+verde*2 );
	verde = green;
	line ( 275, 10+verde*2, 285, 10+verde*2 );

	line ( 295, 10+azul*2, 305, 10+azul*2 );
	azul = blue;
	line ( 295, 10+azul*2, 305, 10+azul*2 );
	}

    setrgbpalette ( 1, red, green, blue );
    }

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
    printf ( "Erro gr fico: \"%s\"\n", grapherrormsg ( errorcode ) );
    printf ( "Pressione qualquer tecla para abortar..." );
    if ( getch ( ) == 0 ) getch ( );
    exit ( EXIT_FAILURE );
    }
}

