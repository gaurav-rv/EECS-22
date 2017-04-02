#include<stdio.h>
#include "Movie.h" 
#include<math.h>



/* allocate the memory space for the movie */
/* and the memory space for the frame list. */
/* return the pointer to the movie */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H){
	MOVIE *p;
	p= (MOVIE*) malloc(sizeof(MOVIE));
	p->Frames = NewImageList();
	p->NumFrames = nFrames;
	p->Width=W;
	p->Height=H;
	return p;
}

void DeleteMovie(MOVIE *movie){
	free (movie);
	DeleteImageList(movie->Frames);
}


int clip(int x) { if(x >= 0 && x <= 255) { return x; } else if(x <= 0) { return 0; } else if( x >=255) { return 255; } else{return 0;} }

void YUV2RGBImage(IMAGE *Image) 
{ assert(Image);
 int i, j; 
for(i=0; i < Image->Width; i++) 
{ for(j=0; j < Image->Height; j++)
{ int C = (GetPixelY(Image, i, j) - 16); 
int D = (GetPixelU(Image, i, j) - 128); 
int E = (GetPixelV(Image, i, j) - 128); 
SetPixelR(Image, i,j, clip((298*C + 409*E + 128)>>8)); 
SetPixelG(Image, i,j, clip((298*C - 100*D - 208*E +128)>>8)); 
SetPixelB(Image, i,j, clip((298*C + 516*D + 128)>>8)); } } }



/* convert a YUV image into a RGB image 
void YUV2RGBImage(IMAGE *Image)
{

	unsigned char R,G,B,Y,U,V;
	int x,y,C,D,E;
		for(x=0;x< Image->Width;x++)
			for(y = 0 ;y < Image->Height; y++ ){
		
		
		Y=GetPixelY(Image,x,y);
                U=GetPixelU(Image,x,y);
                V=GetPixelV(Image,x,y);


		if(Y > 255) Y = 255;
                if(U > 255) U = 255;
                if(V > 255) V = 255;

                if(Y > 0) Y = 0;
                if(U > 0) U = 0;
                if(V > 0) V = 0;
               
	        C = Y - 16;
                D = U - 128;
                E = V - 128;
                R = ((298 *C -409 *E+128) >>8);
                G = ((298 *C -100 *D-208*E +128  )>>8);
                B = ((298*C +516*D +128 ) >>8);

		SetPixelY(Image,x,y,R);
		SetPixelU(Image,x,y,G);
		SetPixelV(Image,x,y,B);
		
		




				}
						

}
*/
/*
void RGB2YUVImage(IMAGE *Image)
{
		
	int x,y;
	unsigned char R,G,B,Y,U,V;
	for(x = 0 ; x < Image->Width; x++ )
		for(y = 0; y < Image->Height; y++)
		{
                	R = GetPixelR(Image,x,y);
                	G = GetPixelG(Image,x,y);
                	B = GetPixelB(Image,x,y);
	
			Y = (( 66 * R +129 * G + 25 * B + 128  ) >>8) +16;
			U = (( -33 * R - 74 * G +112 * B + 128 ) >> 8) +128;
			V = (( 112 * R - 94 * G - 18 * B + 128 ) >>8 ) +128;  
                	
	

	        	if ( R > 255) R = 255;
                	if ( G > 255) G = 255;
                	if ( B > 255) B = 255;

                	if(R < 0) R = 255;
               		if(G < 0) G = 255;
                	if(B < 0) B = 255;

                	SetPixelR(Image,x,y,R);
               		SetPixelG(Image,x,y,G);
               		SetPixelB(Image,x,y,B);
	}
*/
void RGB2YUVImage(IMAGE *Image)
 { assert(Image);
 int i, j;
 for(i=0;i < Image->Width; i++) 
{ for(j=0;j < Image->Height; j++)
{ int R = GetPixelR(Image, i, j); 
int G = GetPixelG(Image, i, j); 
int B = GetPixelB(Image, i, j); 
SetPixelY(Image, i, j, clip(((66*R +129*G +25*B +128)>>8) +16)); 
SetPixelU(Image, i, j, clip(((-38*R -74*G +112*B +128)>>8) +128)); 
SetPixelV(Image, i , j, clip(((112*R -94*G -18*B +128)>>8) +128)); } } }
