//---------------------------------------------------------------------------
// URCAMP - Universidade da Regiao da Campanha
// Curso de Informatica - Computacao Grafica I
// Prof. Alexsander da Rosa
// Programa exemplo para tracado de uma curva Bezier de 4 pontos
// Data: 03 Mai 97
//---------------------------------------------------------------------------
#include <graphics.h>   // initgraph, putpixel, rectangle, etc...
#include <math.h>       // pow, M_PI
#include <stdio.h>      // sprintf
#include <conio.h>      // getch
#include <dos.h>        // delay
#include <stdlib.h>     // randomize, random
#include <time.h>       // randomize

#define TAM         5
#define MAX_PONTOS 50

#define DESENHANDO  1
#define ZOOM        2

#define ELASTICO   if(i>0){setwritemode(XOR_PUT);DesenhaLinha(P[i-1].x,P[i-1].y,x,y,WHITE);setwritemode(COPY_PUT);}

//---------------------------------------------------------------------------
struct Ponto // estrutura para armazenar os 4 pontos da curva Bezier
    {
    double x, y;
    } P[MAX_PONTOS];

     double xmin = -10.0, ymin = -10.0, xmax = 10.0, ymax = 10.0, //window
     umin = 0.0, vmin = 0.0, umax = 640.0, vmax = 480.0; //viewport

//---------------------------------------------------------------------------
void DesenhaPonto ( double x, double y, int cor )
{
double u, v;

// conversao window-viewport (com inversao do eixo y)
u = ( x - xmin ) * ( umax - umin ) / ( xmax - xmin ) + umin;
v = ( y - ymin ) * ( vmin - vmax ) / ( ymax - ymin ) + vmax;
setfillstyle ( SOLID_FILL, LIGHTRED );
bar ( u-2, v-2, u+2, v+2 );
setcolor ( cor );
rectangle ( u-1, v-1, u+1, v+1 );
putpixel ( u, v, cor );
}

//---------------------------------------------------------------------------
void DesenhaCursor ( double x, double y )
{
double u, v;

// conversao window-viewport (com inversao do eixo y)
u = ( x - xmin ) * ( umax - umin ) / ( xmax - xmin ) + umin;
v = ( y - ymin ) * ( vmin - vmax ) / ( ymax - ymin ) + vmax;
setcolor ( WHITE );
setwritemode ( XOR_PUT );
line ( u, v-TAM, u, v+TAM );
line ( u-TAM, v, u+TAM, v );
setwritemode ( COPY_PUT );
}

//---------------------------------------------------------------------------
void DesenhaLinha ( double x1, double y1, double x2, double y2, int cor )
{
double u1, v1, u2, v2;

// conversao window-viewport (com inversao do eixo y) - primeiro ponto
u1 = ( x1 - xmin ) * ( umax - umin ) / ( xmax - xmin ) + umin;
v1 = ( y1 - ymin ) * ( vmin - vmax ) / ( ymax - ymin ) + vmax;
// conversao window-viewport (com inversao do eixo y) - segundo ponto
u2 = ( x2 - xmin ) * ( umax - umin ) / ( xmax - xmin ) + umin;
v2 = ( y2 - ymin ) * ( vmin - vmax ) / ( ymax - ymin ) + vmax;
setcolor ( cor );
line ( u1, v1, u2, v2 );
}

//---------------------------------------------------------------------------
void main ( void )
{
int driver=DETECT, modo, i, tecla;
double x, y, t;

// inicializa o modo grafico
initgraph ( &driver, &modo, "f:\\public\\tc\\bgi" );

// ajuste do texto (para exibir o numero ao lado dos pontos)
settextjustify ( LEFT_TEXT, CENTER_TEXT );
setfillstyle ( SOLID_FILL, LIGHTRED );

// "embaralha" os numeros aleatorios
randomize ( );

DeNovo: // rotulo para o "goto" (que horror!)

cleardevice ( ); // limpa a tela

x = y = 0.0;
i = 0;
DesenhaCursor ( x, y );
while ( i < MAX_PONTOS )
    {
    tecla = getch();
    if ( tecla == 0 )
	tecla = getch();

    if ( tecla == 27 )
	{
	closegraph();
	exit(0);
	}

    if ( tecla == 72 )
	{
	DesenhaCursor ( x, y );
	ELASTICO
	y = y + 0.1;
	ELASTICO
	DesenhaCursor ( x, y );
	}

    if ( tecla == 80 )
	{
	DesenhaCursor ( x, y );
	ELASTICO
	y = y - 0.1;
	ELASTICO
	DesenhaCursor ( x, y );
	}

    if ( tecla == 77 )
	{
	DesenhaCursor ( x, y );
	ELASTICO
	x = x + 0.1;
	ELASTICO
	DesenhaCursor ( x, y );
	}

    if ( tecla == 75 )
	{
	DesenhaCursor ( x, y );
	ELASTICO
	x = x - 0.1;
	ELASTICO
	DesenhaCursor ( x, y );
	}

    //----- F10 - fecha
    if ( tecla == 68 && i > 2 )
	{
	P[i].x = P[0].x;
	P[i].y = P[0].y;
	DesenhaCursor ( x, y );
	ELASTICO
	DesenhaPonto ( P[i].x, P[i].y, WHITE ); // mostra um por um
	if ( i > 0 ) // se nao e' o primeiro ponto
	    DesenhaLinha ( P[i-1].x, P[i-1].y, P[i].x, P[i].y, WHITE );
	DesenhaCursor ( x, y );
	break;
	}

    if ( tecla == 13 )
	{
	P[i].x = x;
	P[i].y = y;
	DesenhaCursor ( x, y );
	DesenhaPonto ( P[i].x, P[i].y, WHITE ); // mostra um por um
	if ( i > 0 ) // se nao e' o primeiro ponto
	    DesenhaLinha ( P[i-1].x, P[i-1].y, P[i].x, P[i].y, WHITE );
	DesenhaCursor ( x, y );
	i++;
	}
    }

if ( ( tecla = getch ( ) ) == 0 ) getch ( ); // aguarda uma tecla
if ( tecla != 27 ) // se nao for ESC, volta
    goto DeNovo;

closegraph ( );
}
