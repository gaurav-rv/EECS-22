#include<stdio.h>
#include<stdlib.h>
#include "Image.h"


unsigned char GetPixelR(IMAGE *image, unsigned int x,  unsigned int y)
	{ unsigned char tempR;
	if(image->R)
	 tempR = *(image->R+(x + (y * (image->Width))));
	return tempR;
	}

unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y)
	{
	unsigned char tempG;
	if(image->G)
	 tempG = *(image->G+(x + (y * (image->Width))));
	return tempG;
	}

unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y)
	{
	unsigned char tempB;
	if (image->B)
	 tempB = *(image->B+(x + (y * (image->Width))));
	return tempB;
}


	void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){
	
	 *(image->R +(x + (y * (image->Width)))) = r;
		
		}

	void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){
		*(image->G +(x + (y * (image->Width)))) = g;

		}

	void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){
		*(image->B +(x + (y * (image->Width)))) = b;	
			}

/* allocate the memory space for the image structure         */
/* and the memory spaces for the color intensity values.     */
/* return the pointer to the image, or NULL in case of error */

	IMAGE *CreateImage(unsigned int Width, unsigned int Height){
 	IMAGE *image;
        image = (IMAGE *)malloc(sizeof(IMAGE));
        image->Height = Height;
        image->Width  = Width;
	image->R = (unsigned char *)malloc(Width * Height * sizeof(unsigned char)+300);
	image->G = (unsigned char *)malloc(Width * Height * sizeof(unsigned char)+300 );
	image->B = (unsigned char *)malloc(Width * Height * sizeof (unsigned char )+300 );
	
        return image;

}

/* release the memory spaces for the pixel color intensity values */
/* deallocate all the memory spaces for the image                 */
	void DeleteImage(IMAGE *image){
	free(image->R);
	free(image->G);
	free(image->B);
	free (image);
	}

