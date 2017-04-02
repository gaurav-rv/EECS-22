#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

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
	printf(" 10: Posterize an image \n");
	printf(" 11.Fill Lights to an image \n");
	printf(" 12.Overlay an image \n");
	printf(" 13.Test all functions\n ");
	printf(" 14.EXIT \n ");
}

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
		int vari=7;	
	ReadImage(fname, R, G, B);
	Posterize(R,G,B,vari);
	strcpy(sname,"poster");
	SaveImage(sname,R,G,B);
	printf("Posterize tested");
	

	ReadImage(fname, R, G, B);
        FillLight(200,20,R,G,B);
        strcpy(sname,"light");
        SaveImage(sname,R,G,B);
        printf("FillLights tested");

	ReadImage(fname, R, G, B);
        Overlay("Peter",R,G,B,0,0);
        strcpy(sname,"overlay_peter");
        SaveImage(sname,R,G,B);
        printf("Overlay Peter tested");
	

        ReadImage(fname, R, G, B);
        Overlay("Spider",R,G,B,90,-10);
        strcpy(sname,"overlay_spider");
        SaveImage(sname,R,G,B);
        printf("Overlay Spider tested");
}

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
	unsigned int pbits;
	int number;
	int x_offset;
	int lightWidth;
	int y_offset;
	char fname2[SLEN];
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

	while (choice != 14) {
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
                       if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
                                printf("Enter the number of posterization bits") ;
                                scanf("%d", &pbits) ;
       
                                Posterize(R,G,B,pbits);
                    
		            printf("Posterize   operation is done!\n");
					
                        }
			break;
		case 11:
		           if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
                                printf("Please input number of lights") ;
                                scanf("%d", &number) ;
                                printf("Input the width of each light");
                                scanf("%d",&lightWidth);
                                FillLight(number,lightWidth,R,G,B);
                                printf("Fill Light operation is done!\n");
                        }
				break;
                case 12:
                           if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        }
                        else
                        {
                                printf("Please cofirm your second image") ;
                                scanf("%s", fname2) ;
                                printf("X cordinate offset?");
                                scanf("%d",&x_offset);
				printf("Y cordinate offset?");
				scanf("%d",&y_offset);
                                Overlay(fname2,R,G,B,x_offset,y_offset);
                                printf("Overlay operation is done!\n");
                        }
			break;




		case 13:
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




