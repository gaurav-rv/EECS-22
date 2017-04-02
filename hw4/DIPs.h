#ifndef DIPS_H
#define DIPS_H
#include <stdio.h>
#include <string.h>
#include "Constants.h"
#include "FileIO.h"
#include <time.h>
#include "Image.h"

/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* flip image vertically */

IMAGE	*VFlip(IMAGE *image);

/* mirror image horizontally */
IMAGE	*HMirror(IMAGE *image);

/* color filter */
IMAGE 	*ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b); 

/* edge detection */
IMAGE	*Edge(IMAGE *image);

/* shuffle the image */
IMAGE *Shuffle(IMAGE *image);

#endif
