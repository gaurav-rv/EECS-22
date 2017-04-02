#ifndef FILEIO_H
#define FILEIO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Constants.h"

int SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


#endif
