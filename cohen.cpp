/*----- Algoritmo de Cohen-Sutherland
        Recorte de retas

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

double xmin = 0.2, ymin = -.75, xmax = 6.0, ymax = .75; //----- window
double umin = 100.0, vmin = 100.0, umax = 540.0, vmax = 380.0; //----- viewport

//--------------------------------------------------------------------------
//----- Retorna o codigo do algoritmo de recorte de Cohen-Sutherland
//--------------------------------------------------------------------------
int Codigo ( double x, double y )
{
int valor = 0;
/* 8 4 2 1  valor (2^n)

   3 2 1 0  bit                         1001|1000|1010
   | | | |                              ----+----+----
   | | | |                              0001|0000|0010
   | | | +-> esquerda                   ----+----+----
   | | +---> direita                    0101|0100|0110
   | +-----> abaixo
   +-------> acima
*/
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
double u1, v1, u2, v2;

//----- faz a conversao window-viewport (para os dois pontos P1 e P2)
u1 = (x1-xmin) * (umax-umin)/(xmax-xmin) + umin;
v1 = (y1-ymin) * (vmin-vmax)/(ymax-ymin) + vmax;
u2 = (x2-xmin) * (umax-umin)/(xmax-xmin) + umin;
v2 = (y2-ymin) * (vmin-vmax)/(ymax-ymin) + vmax;

//----- desenha a linha
line ( u1, v1, u2, v2 );
}

//--------------------------------------------------------------------------
//-----
//--------------------------------------------------------------------------
void CohenSutherlandLineClipAndDraw ( double x0, double y0, double x1,
  double y1, int value )
{
int outcode0, outcode1, outcodeOut;
int accept = 0, done = 0;

outcode0 = Codigo(x0,y0);
outcode1 = Codigo(x1,y1);
do {
  if ( !(outcode0|outcode1) ) { //----- trivialmente aceita
    accept = 1;
    done = 1;
    }
  else
    if ( outcode0 & outcode1 ) //----- trivialmente rejeitada
      done = 1;
    else
      {
      //---- falhou em ambos os testes, entao calcula o segmento de
      //     linha a recortar: de um ponto externo a um ponto na
      //     "borda de recorte", ou seja, a window
      double x,y;
      //---- ao menos um ponto esta' fora do retangulo: pegue-o
      outcodeOut = outcode0 ? outcode0 : outcode1;
      //---- agora encontra o ponto de interseccao
      //---- usa formulas y=y0+slope*(x-x0),x=x0+(1/slope)*(y-y0)
      if ( outcodeOut & 8 ) { //----- divide a linha acima
	x = x0+(x1-x0)*(ymax-y0)/(y1-y0);
	y = ymax;
	} else
      if ( outcodeOut & 4 ) { //----- divide a linha abaixo
	x = x0+(x1-x0)*(ymin-y0)/(y1-y0);
	y = ymin;
	} else
      if ( outcodeOut & 2 ) { //----- divide a linha `a direita
	x = xmax;
	y = y0+(y1-y0)*(xmax-x0)/(x1-x0);
	} else { //----- divide a linha `a esquerda
	x = xmin;
	y = y0+(y1-y0)*(xmin-x0)/(x1-x0);
	}
      //----- agora vamos mover o ponto de fora para o ponto a recortar
      //      e nos preparar para a proxima "passada" do "do...while"
      if ( outcodeOut == outcode0 ) {
	x0=x;
	y0=y;
	outcode0=Codigo(x0,y0); }
      else {
	x1=x;
	y1=y;
	outcode1=Codigo(x1,y1); }
      }
  } while ( !done );
  if (accept) {
    setcolor(value);
    Linha(x0,y0,x1,y1); }
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
for ( ang = 0; ang < 2.1*M_PI; ang += M_PI_4/10.0 )
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
rectangle ( umin-1, vmin-1, umax+1, vmax+1 );
//----- escreve abaixo dela a palavra "WINDOW"
setcolor ( WHITE );
outtextxy ( umin, vmax+textheight("A"), "WINDOW" );

//----- desenha as linhas do poligono aberto
for ( i = 1; i < cont; i++ )
    CohenSutherlandLineClipAndDraw ( Poligono[i].x, Poligono[i].y,
	Poligono[i-1].x, Poligono[i-1].y, LIGHTBLUE );

//----- aguarda uma tecla
if ( !getch() ) getch();

//----- fecha o modo grafico
closegraph();
}

