
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Image.h"
#include "DIPs.h"

/* reverse image color */
void BlackNWhite(IMAGE *image)
{
	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	unsigned int tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y= 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
		tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			if(GetPixelR(image,x,y)>255) SetPixelR(image,x,y,255);
                        if(GetPixelG(image,x,y)>255) SetPixelG(image,x,y,255);
                        if(GetPixelB(image,x,y)>255) SetPixelB(image,x,y,255);
                        if(GetPixelR(image,x,y) <0 ) SetPixelR(image,x,y,0);
                        if(GetPixelG(image,x,y) <0 ) SetPixelB(image,x,y,0);
                        if(GetPixelB(image,x,y) <0 ) SetPixelB(image,x,y,0);
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);
		}

	}

/* flip image vertically */
void VFlip(IMAGE *image)
{
	int             x, y;
	unsigned char   r, g, b;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;
    
	for (y = 0; y < HEIGHT/2; y++) {
		for (x = 0; x < WIDTH; x++) {
			r = GetPixelR(image, x, HEIGHT - 1 - y);
			g = GetPixelG(image, x, HEIGHT - 1 - y);
			b = GetPixelB(image, x, HEIGHT - 1 - y);

			SetPixelR(image, x, HEIGHT - 1 - y, GetPixelR(image, x, y));
			SetPixelG(image, x, HEIGHT - 1 - y, GetPixelG(image, x, y));
			SetPixelB(image, x, HEIGHT - 1 - y, GetPixelB(image, x, y));

			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}

	}

/* mirror image horizontally */
void HMirror(IMAGE *image)
{
	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			SetPixelR(image, x, y, GetPixelR(image, WIDTH - 1 - x, y));
			SetPixelG(image, x, y, GetPixelG(image, WIDTH - 1 - x, y));
			SetPixelB(image, x, y, GetPixelB(image, WIDTH - 1 - x, y));
		}
	}

	}

/* Find the edges in the image */
void Edge(IMAGE *image)
{
	int	x, y, m, n, a, b;
	int	tmpR = 0;
	int	tmpG = 0;
	int	tmpB = 0;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	image_tmp = CreateImage(WIDTH, HEIGHT);

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			SetPixelR(image_tmp, x, y, GetPixelR(image, x, y));
			SetPixelG(image_tmp, x, y, GetPixelG(image, x, y));
			SetPixelB(image_tmp, x, y, GetPixelB(image, x, y));
		}

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) 
		{
			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					a = x + m;
					b = y + n;
					if (a > WIDTH - 1)
						a = WIDTH - 1;
					if (a < 0)
						a = 0;
					if (b > HEIGHT - 1)
						b = HEIGHT - 1;
					if (b < 0)
						b = 0;

					if ((n==0)&&(m==0))
					{
						tmpR += 8*GetPixelR(image_tmp, a, b);
						tmpG += 8*GetPixelG(image_tmp, a, b);
						tmpB += 8*GetPixelB(image_tmp, a, b);
					}
					else
					{
						tmpR -= GetPixelR(image_tmp, a, b);
						tmpG -= GetPixelG(image_tmp, a, b);
						tmpB -= GetPixelB(image_tmp, a, b);
					}
				}
		SetPixelR(image, x, y, ((tmpR > 255)? 255 : (tmpR <0)? 0 : tmpR));
		SetPixelG(image, x, y, ((tmpG > 255)? 255 : (tmpG <0)? 0 : tmpG));
		SetPixelB(image, x, y, ((tmpB > 255)? 255 : (tmpB <0)? 0 : tmpB));

		tmpR = tmpG = tmpB = 0;
		}

	DeleteImage(image_tmp);
	}

/* Posterization */
void Posterize( IMAGE *image)
{
	unsigned int WIDTH;
	unsigned int HEIGHT;
	int pbits=5;
	unsigned char maskzero[8] = {0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
        unsigned char maskone[8]  = {0x0     , 0x1     , 0x3     , 0x7     , 0xf      , 0x1f     , 0x3f     , 0x7f     };
        int x, y;
	unsigned char temp;


	assert(image);
	WIDTH = image->Width;
	HEIGHT = image->Height;

        for(x = 0; x < WIDTH; x ++)
        {
                for(y = 0; y < HEIGHT; y ++)
                {
			temp = GetPixelR(image, x, y);
                        temp &= maskzero[pbits - 1];
                        temp |= maskone[pbits - 1];
			SetPixelR(image, x, y, temp);

			temp = GetPixelG(image, x, y);
                        temp &= maskzero[pbits - 1];
                        temp |= maskone[pbits - 1];
			SetPixelG(image, x, y, temp);

			temp = GetPixelB(image, x, y);
                        temp &= maskzero[pbits - 1];
                        temp |= maskone[pbits - 1];
			SetPixelB(image, x, y, temp);
                }
        }
}
/* 
void Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration)
{
	float x0, y0, x, y, xtemp;
	unsigned int row, column;
	unsigned int iteration;
	unsigned int color;
    	const unsigned char palette[16][3] = {
	
	{   0,   0,   0 },
	{ 127,   0,   0 },
	{ 255,   0,   0 },
	{ 255, 127,   0 },
	{ 255, 255,   0 },
	{ 127, 255,   0 },
	{   0, 255,   0 },
	{   0, 255, 127 },
	{   0, 255, 255 },
	{ 127, 255, 255 },
	{ 255, 255, 255 },	
	{ 255, 127, 255 },	 		
	{ 255,   0, 255 },	
	{ 127,   0, 255 },	
	{   0,   0, 255 },	
	{   0,   0, 127 }   };	

	IMAGE *image;
	image = CreateImage(W, H);

	for(row = 0; row < image->Width; row ++)
	{
		for(column = 0; column < image->Height; column ++)
		{
			x0 = ((float)row / image->Width * 3.5 - 2.5)/(zoom); 
			y0 = ((float)column / image->Height * 2.0 - 1.0)/zoom;
			
			x = 0;
			y = 0;
			iteration = 0;

		  	while ( x*x + y*y < 2*2  &&  iteration < max_iteration )
		  	{
		    	xtemp = x*x - y*y + x0;
		    	y = 2*x*y + y0;
		    	x = xtemp;
		    	iteration = iteration + 1;
		  	}

  			color = iteration % 16;

			SetPixelR(image, row, column, palette[color][0]);
			SetPixelG(image, row, column, palette[color][1]);
			SetPixelB(image, row, column, palette[color][2]);
		}
	}
	return image;
}
 */




