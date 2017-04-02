#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
#define WIDTH  640		/* Image width */
#define HEIGHT 500		/* image height */
#define SLEN    80		/* maximum length of file names and string*/
#define SHUFF_HEIGHT_DIV 4      /* Height division for shuffleing */
#define SHUFF_WIDTH_DIV 4       /* Width division for shuffleing */
/*** function declarations ***/

/* print a menu */
void	PrintMenu();

/* read image from a file */
int	ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int	SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void	BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* flip image vertically */
void	VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* mirror image horizontally */
void	HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void 	ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
		int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b) ; 

/* sharpen the image */
void	Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* edge detection */
void	Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* add border */
void	AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
		char color[SLEN], int border_width);

/* Test all functions */
void	AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int	main()
{
	/*
 * 	 * Two dimensional arrays to hold the current image data. One array
 * 	 	 * for each color component
 * 	 	 	 */

	int		FileNotRead ; 
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	char		fname[SLEN];
	char		color[SLEN];
	int		choice;

	int		target_r ; 
	int		target_g ; 
	int		target_b ;
	int		threshold ; 
	double		factor_r ; 
	double		factor_g ; 
	double		factor_b ;

	int		border_width ; 

	FileNotRead = 1 ; 
	PrintMenu();
	printf("please make your choice: ");
	scanf("%d", &choice);

	while (choice != 11) {
		switch (choice) {
		case 1:
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			FileNotRead = ReadImage(fname, R, G, B);
			break;
		case 2:
			if (FileNotRead != 0)
			{
				printf("No Image Read Yet !!\n") ; 
			}
			else
			{
				printf("Please input the file name to save: ");
				scanf("%s", fname);
				SaveImage(fname, R, G, B);
			}
			break;
		case 3:
			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				BlackNWhite(R, G, B);
	    			printf("\"Black & White\" operation is done!\n");
			}
			break;
		case 4:
      			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				VFlip(R,G,B);
				printf( "\"Vertically Flip\" operation is done!\n" );
			}
			break;
		case 5:
			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				HMirror(R, G, B);
				printf("\"Horizontally Mirror\" operation is done!\n");
			}
			break;
		case 6:
			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				printf("Enter Red   component for the target color: ") ;
				scanf("%d", &target_r) ;
				printf("Enter Green component for the target color: ") ;
				scanf("%d", &target_g) ;
				printf("Enter Blue  component for the target color: ") ;
				scanf("%d", &target_b) ;
				printf("Enter threshold for the color difference: ") ;
				scanf("%d", &threshold) ;
				printf("Enter value for Red component in the target color: ") ;
				scanf("%lf", &factor_r) ;
				printf("Enter value for Green component in the target color: ") ;
				scanf("%lf", &factor_g) ;
				printf("Enter value for Blue  component in the target color: ") ;
				scanf("%lf", &factor_b) ;
			
				ColorFilter(R, G, B, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
				printf("\"Color Filter\" operation is done!\n");
			}
			break;
		case 8:
			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				Shuffle(R, G, B);
				printf("\"Shuffle\" operation is done!\n");
			}
			break;
		case 7:
			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				Edge(R, G, B);
				printf("\"Edge\" operation is done!\n");
			}
			break;
		case 9:
			if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
				printf("Enter border width:") ;
				scanf("%d", &border_width) ;
				printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
				printf("Select border color from the options: ");
				scanf("%s",color);
				AddBorder(R, G, B, color, border_width);
				printf("\"Border\" operation is done!\n");
			}
			break;
		case 10:
			AutoTest(R, G, B);
			FileNotRead = 0 ; 
			break;			
		default:
			printf("Invalid selection!\n");
			break;
		}

		PrintMenu();
		printf("please make your choice: ");
		scanf("%d", &choice);
	}

	return 0;
}

int
ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	char            Type[SLEN];
	int             Width, Height, MaxValue;
	int             x, y;
	char            ftype[] = ".ppm";
  	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/

  	strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);

	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("Cannot open file \"%s\" for reading!\n", fname);
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
		printf("\nUnsupported image width %d!\n", Width);
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
		printf("\nUnsupported image height %d!\n", Height);
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		return 5;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected!\n");
		return 6;
	}
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	if (ferror(File)) {
		printf("\nFile error while reading from file!\n");
		return 7;
	}
	printf("%s was read successfully!\n", fname_tmp);
	fclose(File);
	return 0;
}

int
SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE	*File;
	int	x, y;
	char	SysCmd[SLEN * 5];

	char	ftype[] = ".ppm";
	char	fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
  	char	fname_tmp2[SLEN];

	strcpy(fname_tmp, fname);
	strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("Cannot open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}

	if (ferror(File)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_tmp2);

	/*
 * 	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
 * 	 	 * and make it world readable
 * 	 	 	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);

	return (0);
}

/* print a menu */
void
PrintMenu()
{
	printf("--------------------------------\n");
	printf(" 1:  Load a PPM image\n");
	printf(" 2:  Save an image in PPM and JPEG format\n");
	printf(" 3:  Change a color image to Black & White\n");
	printf(" 4:  Flip an image vertically\n");
	printf(" 5:  Mirror an image horizontally\n");
	printf(" 6:  Color filter an image\n");
	printf(" 7:  Sketch the edge of an image\n");
	printf(" 8:  Shuffle an image\n");
	printf(" 9:  BONUS: Add Border to an image\n");
	printf(" 10: Test all functions \n");
	printf(" 11: Exit\n");
}


/* age the image to make it look like old picture */
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
void
BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
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
void
VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
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


/* auto test*/
void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char            fname[SLEN] = "RingMall";
	char            sname[SLEN];

	ReadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	printf("Black & White tested!\n\n");

	ReadImage(fname, R, G, B);
	VFlip(R, G, B);
	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	printf("VFlip tested!\n\n");

	ReadImage(fname, R, G, B);
	HMirror(R, G, B);
	strcpy(sname, "hmirror");
	SaveImage(sname, R, G, B);
	printf("HMirror tested!\n\n");

	ReadImage(fname, R, G, B);
	ColorFilter(R, G, B, 180, 180, 50, 70, 0, 255, 0);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color Filter tested!\n\n");

	ReadImage(fname, R, G, B);
	Shuffle(R, G, B);
	strcpy(sname, "shuffle");
	SaveImage(sname, R, G, B);
	printf("Shuffle tested!\n\n");

	ReadImage(fname, R, G, B);
	Edge(R, G, B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	printf("Edge Detection tested!\n\n");

	ReadImage(fname, R, G, B);
	AddBorder (R, G, B, "black", 10) ; 
	strcpy(sname, "border"); 
	SaveImage(sname, R, G, B) ; 
	printf("Border tested!\n\n");

}


