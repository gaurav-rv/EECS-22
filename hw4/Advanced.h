#ifndef ADVANCED_H
#define ADVANCED_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileIO.h"
#include "DIPs.h"
#include "Constants.h"
#include "Image.h"
#define MAX_COLOR 16


IMAGE *Posterize( IMAGE *image,unsigned int  pbits);

/* Add noise to image */
IMAGE *FillLight( int number, int lightWidth, IMAGE *image);

/* Overlay with another image */
IMAGE *Overlay(char fname[SLEN],IMAGE *image , int x_offset, int y_offset);

/* Perform Cut Paste operations on the image*/
IMAGE *CutPaste( IMAGE *image, unsigned int startX, unsigned int startY, unsigned int xWidth,unsigned int yWidth, unsigned int pasteNumber);			

IMAGE *Rotate(IMAGE *image);

IMAGE *Resize(unsigned int percentage, IMAGE *image);

/*

IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);
*/
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int bord );

#endif
