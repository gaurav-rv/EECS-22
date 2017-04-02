#ifndef Movieh
#define Movieh
#include<stdio.h>
#include "Image.h"
#include "ImageList.h"  
typedef struct{
unsigned int Width; /* movie frame width */
unsigned int Height; /* movie frame height */
unsigned int NumFrames; /* total number of frames */
ILIST *Frames; /* the pointer to the frame list */
}MOVIE;


MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H);

void DeleteMovie(MOVIE *movie);

void YUV2RGBImage(IMAGE *Image);

void RGB2YUVImage(IMAGE *Image);

#endif
