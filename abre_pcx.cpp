// I N C L U D E S ///////////////////////////////////////////////////////////
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>


// D E F I N E S  ////////////////////////////////////////////////////////////

#define SCREEN_WIDTH      (unsigned int)320
#define SCREEN_HEIGHT     (unsigned int)200

// S T R U C T U R E S ///////////////////////////////////////////////////////

// this structure holds a RGB triple in three bytes

typedef struct RGB_color_typ
	{

	unsigned char red;    // red   component of color 0-63
	unsigned char green;  // green component of color 0-63
	unsigned char blue;   // blue  component of color 0-63

	} RGB_color, *RGB_color_ptr;

typedef struct pcx_header_typ
	{
	char manufacturer;
	char version;
	char encoding;
	char bits_per_pixel;
	int x,y;
	int width,height;
	int horz_res;
	int vert_res;
	char ega_palette[48];
	char reserved;
	char num_color_planes;
	int bytes_per_line;
	int palette_type;
	char padding[58];

	} pcx_header, *pcx_header_ptr;


typedef struct pcx_picture_typ
	{
	pcx_header header;
	RGB_color palette[256];
	char far *buffer;

	} pcx_picture, *pcx_picture_ptr;


// P R O T O T Y P E S ///////////////////////////////////////////////////////
int huge detectVGA256 ( void );
void checkerrors ( void );


void Plot_Pixel_Fast(int x,int y,unsigned char color);
void PCX_Init(pcx_picture *image);
void PCX_Delete(pcx_picture *image);
void PCX_Load(char *filename, pcx_picture_ptr image,int enable_palette);
void PCX_Show_Buffer(pcx_picture_ptr image);

// G L O B A L S  ////////////////////////////////////////////////////////////

unsigned char far *video_buffer = (char far *)0xA0000000L; // vram byte ptr

// F U N C T I O N S /////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////////////////////

void PCX_Init(pcx_picture_ptr image)
{
// this function allocates the buffer region needed to load a pcx file

if (!(image->buffer = (char far *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT + 1)))

   printf("\ncouldn't allocate screen buffer");

} // end PCX_Init

//////////////////////////////////////////////////////////////////////////////

void Plot_Pixel_Fast(int x,int y,unsigned char color)
{
// plots the pixel in the desired color a little quicker using binary shifting
// to accomplish the multiplications

// use the fact that 320*y = 256*y + 64*y = y<<8 + y<<6

video_buffer[((y<<8) + (y<<6)) + x] = color;

} // end Plot_Pixel_Fast

//////////////////////////////////////////////////////////////////////////////

void PCX_Delete(pcx_picture_ptr image)
{
// this function de-allocates the buffer region used for the pcx file load

free((void*)image->buffer);

} // end PCX_Delete

//////////////////////////////////////////////////////////////////////////////

void PCX_Load(char *filename, pcx_picture_ptr image,int enable_palette)
{
// this function loads a pcx file into a picture structure, the actual image
// data for the pcx file is decompressed and expanded into a secondary buffer
// within the picture structure, the separate images can be grabbed from this
// buffer later.  also the header and palette are loaded

FILE *fp;
int num_bytes,index;
long count;
unsigned char data;
char far *temp_buffer;

// open the file
fp = fopen(filename,"rb");

// load the header
temp_buffer = (char far *)image;

for (index=0; index<128; index++)
    {
    temp_buffer[index] = getc(fp);
    } // end for index

// load the data and decompress into buffer
count=0;
while(count<=SCREEN_WIDTH * SCREEN_HEIGHT)
     {
     // get the first piece of data
     data = getc(fp);

     // is this a rle?
     if (data>=192 && data<=255)
	{
	// how many bytes in run?
	num_bytes = data-192;

	// get the actual data for the run
	data  = getc(fp);

	// replicate data in buffer num_bytes times
	while(num_bytes-->0)
	     {
	     image->buffer[count++] = data;
	     } // end while

	} // end if rle
     else
	{
	// actual data, just copy it into buffer at next location
	image->buffer[count++] = data;
	} // end else not rle

     } // end while

// move to end of file then back up 768 bytes i.e. to begining of palette
fseek(fp,-768L,SEEK_END);

// load the pallete into the palette
for (index=0; index<256; index++)
    {
    // get the red component
    image->palette[index].red   = (getc(fp) >> 2);

    // get the green component
    image->palette[index].green = (getc(fp) >> 2);

    // get the blue component
    image->palette[index].blue  = (getc(fp) >> 2);
    } // end for index

fclose(fp);

// change the palette to newly loaded palette if commanded to do so
if (enable_palette)
   {
   for (index=0; index<256; index++)
       {
       setrgbpalette(index,
	  image->palette[index].red,
	  image->palette[index].green,
	  image->palette[index].blue );
       } // end for index
   } // end if change palette
} // end PCX_Load

//////////////////////////////////////////////////////////////////////////////

void PCX_Show_Buffer(pcx_picture_ptr image)
{
// just copy he pcx buffer into the video buffer

_fmemcpy((char far *)video_buffer,
	 (char far *)image->buffer,SCREEN_WIDTH*SCREEN_HEIGHT);

} // end PCX_Show_Picture


//---------------------------------------------------------------------------
// M A I N ///////////////////////////////////////////////////////////////////
void main ( int argc, char *argv[] )
{
long index;
pcx_picture imagem;
int gdriver, gmode, i;
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


//----- aqui

// set video mode to 320x200 256 color mode

// load in background
PCX_Init((pcx_picture_ptr)&imagem);
PCX_Load(argv[1], (pcx_picture_ptr)&imagem,1);

PCX_Show_Buffer((pcx_picture_ptr)&imagem);


//----- aguarda uma tecla
if ( getch()==0 ) getch();
PCX_Delete((pcx_picture_ptr)&imagem);

// make a cool clear screen, disolve screen, in one line, eye might add!
for (index=0; index<=300000L; index++,Plot_Pixel_Fast(rand()%320, rand()%200, 0));

// go back to text mode
closegraph();

return;
}
