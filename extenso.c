/*---------------------------------------------------------
EXTENSO.C - converte a entrada (via linha-de-comando) para
   uma reais, por extenso. Exercicio de Programacao II

Universidade da Regiao da Campanha
Centro de Ciencias da Economia e Informatica
Curso de Informatica
Programacao II
Prof. Alexsander da Rosa
---------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*----- potencia de 1000, ou seja, 1000 elevado a 6 -----*/
#define POT_MIL 6
#define MOEDA   "reais" /*---- descubra um bug aqui... -----*/

/*----- unidade: vai ate vinte, pois 15 = quinze, e nao dez e cinco */
char *unidade[] = { "zero", "um", "dois", "tres", "quatro",
    "cinco", "seis", "sete", "oito", "nove", "dez", "onze",
    "doze", "treze", "quatorze", "quinze", "dezesseis",
    "dezessete", "dezoito", "dezenove" };

/*----- dezena: normal, mas nao pode ser 0 nem 1 -----*/
char *dezena[] = { "-erro-", "-dez-", "vinte", "trinta", "quarenta",
    "cinquenta", "sessenta", "setenta", "oitenta", "noventa" };

/*----- centena: normal, mas nao pode se 0 (usado para o cem) -----*/
char *centena[] = { "cem", "cento", "duzentos", "trezentos",
    "quatrocentos", "quinhentos", "seiscentos", "setecentos",
    "oitocentos", "novecentos" };

/*----- milhar: normal, mas nao pode ser 0, e so' vai ate' o quintilhao,
        alem disso falta o "ao" (singular) ou o "oes" (plural), que
        serao acrecentados depois, em tempo de execucao -----*/
char *milhar[] = { "", "mil", "milh", "bilh", "trilh", "quatrilh",
    "quintilh" };

/*-------------------------------------------------------------------*/
void main ( argc, argv ) /*----- formato para compatibilidade c/ HP-UX */
int argc; /*----- contador de argumentos -----*/
char *argv[]; /*----- vetor de argumentos -----*/
{
double total, div;
char buffer[50], buff_cent[5];
unsigned short int i, j, k, mil, centavos, valor, aux;

/*----- se o usuario nao digitar o valor -----*/
if ( argc < 2 || argc > 3 )
    {
    printf ( "EXTENSO v0.02 - Gerador de valores por extenso\n" );
    printf ( "Sintaxe: %s <valor> [<moeda>]\n\n", argv[0] );
    return;
    }

/*----- varre a string de entrada separando inteiros de centavos */
centavos = 0;
for ( i = 0; i < strlen(argv[1]); i++ )
    {
    if ( argv[1][i] == '.' ) /*----- se tem ponto decimal -----*/
        {
        for ( k = 0, j = i+1; j < i+3; j++, k++ ) /* pega 2 digitos */
            if ( isdigit(argv[1][j]) )            /* dos centavos */
                buff_cent[k] = argv[1][j];
            else
                buff_cent[k] = '0';
        buff_cent[k] = '\0';
        break;
        }
    if ( isdigit(argv[1][i]) ) /*----- copia a parte inteira */
        buffer[i] = argv[1][i];
    }
buffer[i] = '\0';

/*----- evita overflow (acima de 9.999.999.999.999.999) ----*/
if ( strlen(buffer) > 16 )
    {
    printf ( "Erro E01: Overflow - numero muito grande.\n\n" );
    return;
    }

total = atof(buffer); /*----- a parte inteira vira um double */
centavos = atoi(buff_cent); /*----- e os centavos um short int */

/*----- calcula o divisor inicial = 1000 elevado a POT_MIL -----*/
mil = 1;
div = 1.0;
for ( i = 0; i < POT_MIL; i++ )
    {
    div *= 1000.0;
    mil++;
    }

/*----- laco principal (dos inteiros) -----*/
while ( div > 0.5 )
    {
    /*----- extrai milhares (de 3 em 3) */
    aux = (total/div)/1000.0;
    valor = (total/div) - aux*1000.0;
    div = div / 1000.0;
    mil--;
    if ( valor < 1 && div > 0.5 )
        continue; /*----- volta para o while */

    /*----- mostra o valor (em milhar) por extenso */
    if ( valor < 20 )
        {
        printf ( "%s", unidade[valor] );
        }
    else
        if ( valor < 100 )
            {
            printf ( "%s", dezena[valor/10] );
            if ( valor%10 ) /*----- se valor / 100 tiver resto != 0 */
                printf ( " e %s", unidade[valor%10] );
            }
        else
            if ( valor < 1000 )
                {
                if ( valor == 100 )
                    printf ( "%s", centena[valor%100] );
                else
                    printf ( "%s", centena[valor/100] );
                if ( valor%100 < 20 )
                    {
                    if ( valor%100 )
                        printf ( " e %s", unidade[valor%100] );
                    }
                else
                    {
                    printf ( " e %s", dezena[(valor%100)/10] );
                    if ( (valor%100)%10 )
                        printf ( " e %s", unidade[(valor%100)%10] );
                    }
                }

    /*----- se estivermos em uma case de milhar -----*/
    if ( mil > 0 )
        {
        printf ( " %s", milhar[mil] );
        if ( mil > 1 ) /*--- se for > 1 mil muda (senao fica "miloes") */
            {
            if ( valor == 1 )
                printf ( "ao " ); /* singular */
            else
                printf ( "oes " ); /* plural */
            }
        else
            printf ( " " );
        }

    }

if ( argc == 3 )
    printf ( " %s", argv[2] );
else
    printf ( " %s", MOEDA );

if ( centavos != 0 )
    {
    printf ( " e " );
    /*----- mostra os centavos por extenso */
    if ( centavos < 20 )
        {
        printf ( "%s", unidade[centavos] );
        }
    else
        {
        printf ( "%s", dezena[centavos/10] );
        if ( centavos%10 ) /*----- se centavos / 100 tiver resto != 0 */
            printf ( " e %s", unidade[centavos%10] );
        }
    printf ( " centavos" );
    }
printf ( "\n\n" );
}

/*----- Bugs conhecidos:
   - erros de arredondamento acima de 9 quatrilhoes
   - moeda apenas no singular (1 reais)
*/
