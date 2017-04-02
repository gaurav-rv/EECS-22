#ifndef ADVANCED_H
#define ADVANCED_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include "Constants.h"


void Overlay( char fname[SLEN], 
 unsigned char R[WIDTH][HEIGHT], 
 unsigned char G[WIDTH][HEIGHT], 
 unsigned char B[WIDTH][HEIGHT], 
 int x_offset, int y_offset);


void FillLight( int number , int lightWidth, 
 unsigned char R[WIDTH][HEIGHT], 
 unsigned char G[WIDTH][HEIGHT], 
 unsigned char B[WIDTH][HEIGHT]);


void Posterize( unsigned char R[WIDTH][HEIGHT], 
 unsigned char G[WIDTH][HEIGHT], 
 unsigned char B[WIDTH][HEIGHT],
 unsigned int pbits);

#endif

