
#ifndef DIPS_H
#define DIPS_H

#include <stdio.h>
#include <string.h>
#include "Image.h"

/* change color image to black & white */
void BlackNWhite(IMAGE *image);

/* mirror image horizontally */
void HMirror(IMAGE *image);

/* Add a border to the image */
void AddBorder(IMAGE *image, char color[80], int border_width);

/* flip image vertically */
void VFlip(IMAGE *image);

/* edge detection */
void Edge(IMAGE *image);

/*Posterize  Image*/
void Posterize( IMAGE *image);

/* Add noise to image */
void FillLight(  IMAGE *image, int number, int lightWidth);

/* Mandelbrot						*/
void Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);

#endif

