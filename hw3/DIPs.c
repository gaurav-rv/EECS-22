#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "DIPs.h"
#include "Constants.h"



void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int	x, y;

	for( y = 0; y < HEIGHT; y++ ){
		for( x = 0; x < WIDTH; x++ ) {
			B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
			R[x][y] = (unsigned char) (B[x][y]*1.6);
			G[x][y] = (unsigned char) (B[x][y]*1.6);
		}
	}
}

/* reverse image color */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int	x, y;

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = G[x][y] = B[x][y]
				= (R[x][y] + G[x][y] + B[x][y]) / 3;
		}
	}
}

/* flip image vertically */
void	VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int	x, y;
	unsigned char   r, g, b;
    
	for (y = 0; y < HEIGHT/2; y++) {
		for (x = 0; x < WIDTH; x++) {
			r = R[x][HEIGHT - 1 - y];
			g = G[x][HEIGHT - 1 - y];
			b = B[x][HEIGHT - 1 - y];

			R[x][HEIGHT - 1 - y] = R[x][y];
			G[x][HEIGHT - 1 - y] = G[x][y];
			B[x][HEIGHT - 1 - y] = B[x][y];
            
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

/* mirror image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int	x, y;
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			R[x][y] = R[WIDTH - 1 - x][y] ;
			G[x][y] = G[WIDTH - 1 - x][y] ;
			B[x][y] = B[WIDTH - 1 - x][y] ;
		}
	}
}

/* Color Filter */
void ColorFilter (unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
                  int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b)
{
	int x, y ; 
	int temp ; 
	
	for (y=0; y<HEIGHT; y++){
		for (x=0; x<WIDTH; x++){
	  		if ((R[x][y] < target_r + threshold)&&
			    (R[x][y] > target_r - threshold)&&
			    (G[x][y] < target_g + threshold)&&
			    (G[x][y] > target_g - threshold)&&
			    (B[x][y] < target_b + threshold)&&
			    (B[x][y] > target_b - threshold)) 
			{
	  			temp = factor_r; 
	  			R[x][y] = (temp > 255)? 255 : (temp <0)? 0 : temp ;
	  			temp = factor_g; 
	  			G[x][y] = (temp > 255)? 255 : (temp <0)? 0 : temp ;
	  			temp = factor_b; 
				B[x][y] = (temp > 255)? 255 : (temp <0)? 0 : temp ;
	  		}
		}
	}
}

/* Shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width = WIDTH/SHUFF_WIDTH_DIV;
	int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
	int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
	int i, j;
	

	srand(time(NULL));
	/* Initialize block markers to not done (-1) */
	for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
		for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
			block[i][j] = -1;
		}
	}

	while (block_cnt > 0) {
		/* Generate a random pair of blocks */
		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width = rand() % SHUFF_WIDTH_DIV;
		int src_height = rand() % SHUFF_HEIGHT_DIV;
		int src_width = rand() % SHUFF_WIDTH_DIV;

		/* Check if these blocks are already swaped, if not swap blocks */
		if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
			/* Swap blocks */
			for (i = 0; i < block_height; i++) {
				/* Init src and dest height offset */
				int h_dest = ((dest_height * block_height) + i) % HEIGHT;
				int h_src  = ((src_height * block_height) + i) % HEIGHT; 
				for (j = 0; j < block_width; j++) {
					int temp;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % WIDTH; 
					int w_dest = ((dest_width * block_width) + j) % WIDTH;

					temp = R[w_dest][h_dest];
					R[w_dest][h_dest] = R[w_src][h_src];
					R[w_src][h_src] = temp;

					temp = G[w_dest][h_dest];
					G[w_dest][h_dest] = G[w_src][h_src];
					G[w_src][h_src] = temp;

					temp = B[w_dest][h_dest];
					B[w_dest][h_dest] = B[w_src][h_src];
					B[w_src][h_src] = temp;
				}
			}
			/* Set marker as done */
			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}
		
	}


}

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int		x, y, m, n, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;
	
	unsigned char	R_tmp[WIDTH][HEIGHT];
	unsigned char	G_tmp[WIDTH][HEIGHT];
	unsigned char	B_tmp[WIDTH][HEIGHT];

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++) {
			R_tmp[x][y] = R[x][y];
			G_tmp[x][y] = G[x][y];
			B_tmp[x][y] = B[x][y];
		}
	}

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
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
						tmpR += 9*R_tmp[a][b] ; 
						tmpG += 9*G_tmp[a][b] ; 
						tmpB += 9*B_tmp[a][b] ; 
					}
					else
					{
						tmpR -= R_tmp[a][b] ; 
						tmpG -= G_tmp[a][b] ; 
						tmpB -= B_tmp[a][b] ; 
					}
				}
			}
			R[x][y] = (tmpR>255)? 255: (tmpR<0)? 0: tmpR ;
			G[x][y] = (tmpG>255)? 255: (tmpG<0)? 0: tmpG ;
			B[x][y] = (tmpB>255)? 255: (tmpB<0)? 0: tmpB ;
		  	tmpR = tmpG = tmpB = 0; 	
		}
	}
}

/* blur the image */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
        int             x, y, m, n, a, b;
        int             tmpR = 0;
        int             tmpG = 0;
        int             tmpB = 0;

        unsigned char   R_tmp[WIDTH][HEIGHT];
        unsigned char   G_tmp[WIDTH][HEIGHT];
        unsigned char   B_tmp[WIDTH][HEIGHT];

        for (y = 0; y < HEIGHT; y++){
                for (x = 0; x < WIDTH; x++) {
                        R_tmp[x][y] = R[x][y];
                        G_tmp[x][y] = G[x][y];
                        B_tmp[x][y] = B[x][y];
                }
        }

        for (y = 0; y < HEIGHT; y++){
                for (x = 0; x < WIDTH; x++){
                        for (n = -1; n <= 1; n++){
                                for (m = -1; m <= 1; m++) {
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
                                                tmpR += 8*R_tmp[a][b] ;
                                                tmpG += 8*G_tmp[a][b] ;
                                                tmpB += 8*B_tmp[a][b] ;
                                        }
                                        else
                                        {
                                                tmpR -= R_tmp[a][b] ;
                                                tmpG -= G_tmp[a][b] ;
                                                tmpB -= B_tmp[a][b] ;
                                        }
				}
			}
			R[x][y] = (tmpR>255)? 255: (tmpR<0)? 0: tmpR ;
                        G[x][y] = (tmpG>255)? 255: (tmpG<0)? 0: tmpG ;
                        B[x][y] = (tmpB>255)? 255: (tmpB<0)? 0: tmpB ;
                        tmpR = tmpG = tmpB = 0;
                }
        }
}

/*add border*/
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
		char color[SLEN], int border_width)
{
	int x, y ;
	int border_r = 255;
	int border_g = 255;
	int border_b = 255;
 	if (!strcmp(color, "black")) {
                border_r = 0;
                border_g = 0;
                border_b = 0;
        } else if (!strcmp(color, "white")) {
                border_r = 255;
                border_g = 255;
                border_b = 255;
        } else if (!strcmp(color, "red")) {
                border_r = 255;
                border_g = 0;
                border_b = 0;
        } else if (!strcmp(color, "green")) {
                border_r = 0;
                border_g = 255;
                border_b = 0;
        } else if (!strcmp(color, "blue")) {
                border_r = 0;
                border_g = 0;
                border_b = 255;
        } else if (!strcmp(color, "yellow")) {
                border_r = 255;
                border_g = 255;
                border_b = 0;
        } else if (!strcmp(color, "cyan")) {
                border_r = 0;
                border_g = 255;
                border_b = 255;
        } else if (!strcmp(color, "pink")) {
                border_r = 255;
                border_g = 192;
                border_b = 203  ;
        } else if (!strcmp(color, "orange")) {
		border_r = 255;
                border_g = 165;
                border_b = 0;
        }
 
	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++) 
		{
			if ((y < border_width)||
			    (y > HEIGHT - border_width)||
			    (x < border_width)||
			    (x > WIDTH - border_width))
			{
				R[x][y] = border_r ; 
				G[x][y] = border_g ; 
				B[x][y] = border_b ; 
			}
		}
	}
}

