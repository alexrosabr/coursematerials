/*----- Algoritmo de Cohen-Sutherland
        Visualizacao das retas a recortar

        URCAMP - Universidade da Regiao da Campanha
        Prof. Alexsander da Rosa
*/

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

typedef struct
    {
    double x, y;
    } PONTO;

double xmin = -1.0, ymin = -.75, xmax = 7.0, ymax = .75; //----- window
double umin = 100.0, vmin = 100.0, umax = 540.0, vmax = 380.0; //----- viewport

//--------------------------------------------------------------------------
//----- Retorna o codigo do algoritmo de recorte de Cohen-Sutherland
//--------------------------------------------------------------------------
int Codigo ( double x, double y )
{
int valor = 0;
if ( x < xmin ) //----- testar o bit 0 (esquerda)
    valor |= 1;
if ( x > xmax ) //----- testar o bit 1 (direita)
    valor |= 2;
if ( y < ymin ) //----- testar o bit 2 (abaixo)
    valor |= 4;
if ( y > ymax ) //----- testar o bit 3 (acima)
    valor |= 8;
return valor;
}

//--------------------------------------------------------------------------
//-----
//--------------------------------------------------------------------------
void Linha ( double x1, double y1, double x2, double y2 )
{
int cod1,cod2;
double u1,v1,u2,v2;

//----- calcula os codigos do algoritmo Cohen-Sutherland
cod1 = Codigo ( x1, y1 );
cod2 = Codigo ( x2, y2 );

//----- faz a conversao window-viewport (para os dois pontos P1 e P2)
u1 = (x1-xmin) * (umax-umin)/(xmax-xmin) + umin;
v1 = (y1-ymin) * (vmin-vmax)/(ymax-ymin) + vmax;
u2 = (x2-xmin) * (umax-umin)/(xmax-xmin) + umin;
v2 = (y2-ymin) * (vmin-vmax)/(ymax-ymin) + vmax;

//----- desenha as "bolinhas" nas juncoes das linhas
setcolor ( LIGHTRED );
circle ( u1, v1, 2 );
circle ( u2, v2, 2 );

if ( cod1&cod2 ) //----- todo fora (cod1 AND cod2 diferente de zero)
  setcolor ( DARKGRAY );
else
  if ( !(cod1|cod2) ) //----- esta' todo dentro (cod1 OR cod2 igual a zero)
    setcolor ( YELLOW );
  else
    setcolor ( LIGHTBLUE ); //----- esta' parcialmente dentro e fora
			    //      (tem que recortar)

//----- desenha a linha
line ( u1, v1, u2, v2 );
}

//--------------------------------------------------------------------------
//-----
//--------------------------------------------------------------------------
void main ( void )
{
PONTO Poligono[100];
int driver = DETECT, modo;
int i, cont;
double ang;

//----- definir o poligono
cont = 0;
for ( ang = 0; ang < 2.1*M_PI; ang += M_PI_4/2.0 )
    {
    Poligono[cont].x = ang;
    Poligono[cont].y = sin(ang);
    cont++;
    }

//----- abre o modo grafico
initgraph ( &driver, &modo, "f:\\public\\tc\\bgi" );

//----- escreve o titulo centralizado
settextjustify ( CENTER_TEXT, TOP_TEXT );
outtextxy ( 320, 10, "RECORTE (Cohen-Sutherland)" );

//----- desenha a window (em vermelho)
setcolor ( LIGHTRED );
rectangle ( umin, vmin, umax, vmax );
//----- escreve abaixo dela a palavra "WINDOW"
setcolor ( WHITE );
outtextxy ( umin, vmax+textheight("A"), "WINDOW" );

//----- escreve o texto das legendas (acima, `a esquerda)
settextjustify ( LEFT_TEXT, CENTER_TEXT );
outtextxy ( 40, 10, "Toda dentro" );
outtextxy ( 40, 20, "Com recorte" );
outtextxy ( 40, 30, "Toda fora" );

//----- faz o retangulo e desenha as linhas coloridas da legenda
rectangle ( 5, 5, 35, 35 );
setlinestyle ( SOLID_LINE, 0, THICK_WIDTH );
setcolor ( YELLOW ); line ( 10, 10, 30, 10 );
setcolor ( LIGHTBLUE ); line ( 10, 20, 30, 20 );
setcolor ( DARKGRAY ); line ( 10, 30, 30, 30 );

//----- desenha as linhas do poligono aberto
for ( i = 1; i < cont; i++ )
    Linha ( Poligono[i].x, Poligono[i].y, Poligono[i-1].x, Poligono[i-1].y );

//----- aguarda uma tecla
if ( !getch() ) getch();

//----- fecha o modo grafico
closegraph();
}
