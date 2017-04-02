#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "FileIO.h"
#include "Advanced.h"
#include "DIPs.h"


/* print a menu */
void            PrintMenu();
IMAGE  *AutoTest(IMAGE *image);


int  main()
{
IMAGE *image;
image = NULL;	
#ifdef DEBUG
	IMAGE *AutoTest(IMAGE *image);
#else
	
	char            fname[SLEN],color[SLEN];
	int      k=0,       choice=0, width;
	int 	HEIGHT;
	int 	WIDTH;
	int	target_r ; 
	int	target_g ; 
	int	target_b ;
	int	threshold ; 
	double	factor_r ; 
	double 	factor_g ; 
	double	factor_b ;

	int 	ratio,per,bord;
	unsigned int x_offset, y_offset;
	unsigned int start_x, start_y, x_width, y_height, pasteNumber;
	unsigned char pbits;
	PrintMenu();
	image=ReadImage(fname);
	printf("Please make your choice: ");
	scanf("%d", &choice); 
	while (choice != 17) {
		switch (choice) {
		case 1:
			printf("Please input the file name to load: ");
			scanf("%s", fname); 
			
			printf(" After scanning "); 
			
			image = ReadImage("RingMall"); 
			printf("Image Read\n");
			
			break;
		case 2:
			printf("Please input the file name to save: ");
			scanf("%s", fname);
			SaveImage(fname, image);
			break;
		case 3:
			BlackNWhite(image);
	    		printf("\"Black & White\" operation is done!\n");
			DeleteImage(image);
			break;
		case 4:
      			VFlip(image);
			printf( "\"Vertically Flip\" operation is done!\n" );
			DeleteImage(image);	
			break;
		case 5:
			HMirror(image);
			printf("\"Horizontally Mirror\" operation is done!\n");
			DeleteImage(image);
			break;
		case 6:
			printf("Enter Red   component for the target color: ") ;
			scanf("%d", &target_r) ;
			printf("Enter Green component for the target color: ") ;
			scanf("%d", &target_g) ;
			printf("Enter Blue  component for the target color: ") ;
			scanf("%d", &target_b) ;
			printf("Enter threshold for the color difference: ") ;
			scanf("%d", &threshold) ;
			printf("Enter factor for Red   component in the target color: ") ;
			scanf("%lf", &factor_r) ;
			printf("Enter factor for Green component in the target color: ") ;
			scanf("%lf", &factor_g) ;
			printf("Enter factor for Blue  component in the target color: ") ;
			scanf("%lf", &factor_b) ;
			ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
			printf("\"Color Filter\" operation is done!\n");
			DeleteImage(image);
			break;
		case 7:
			Edge(image);
			printf("\"Edge\" operation is done!\n");
			DeleteImage(image);
			break;

		case 8:
			Shuffle(image);
			printf("\"Shuffle\" operation is done!\n");
			DeleteImage(image);
			break;
	
		case 9:
                        printf("Enter the number of posterization bits (1 to 8): ");
                        scanf("%hhu",&pbits);
                        Posterize(image,pbits);
                        printf("\"Posterization\" operation is done!\n");
			DeleteImage(image);
                     	
			   break;
	
		case 10:
			printf("Please input number of lights: ");
			scanf("%d",&ratio) ;		  
			printf("Please input the width of each light: ");
			scanf("%d", &width);
			FillLight(ratio,width,image);
			DeleteImage(image);
			printf("\"Fill Light\" operation is done!\n");
			break;
		case 11: 
			printf("Please input the file name to overlay: ");
    			scanf("%s", fname);
			printf("Please input x coordinate of the overlay image: ") ; 
			scanf("%d", &x_offset) ;
			printf("Please input y coordinate of the overlay image: ") ;
			scanf("%d", &y_offset) ;
			Overlay(fname,image, x_offset, y_offset);
			DeleteImage(image);

			break;
		case 12:
			printf("Give the start X coordinate for cutting:  ");
			scanf("%u",&start_x);
			printf("Give the start Y coordinate for cutting:  ");
			scanf("%u",&start_y);
			printf("Give the width for cutting:  ");
			scanf("%u",&x_width);
			printf("Give the height for cutting:  ");
			scanf("%u",&y_height);
			printf("Give the number of paste points:  ");
			scanf("%u",&pasteNumber);


			CutPaste(image, start_x, start_y, x_width, y_height, pasteNumber);
			DeleteImage(image);
			printf("Cut paste Operation completed \n \n");
			break;			
		case 15:
			AutoTest(image);
			DeleteImage(image);
			break;
		case 14:
			Rotate(image);
			
				break;
		
		case 13:
			
			printf("Enter the resizing percentage");
			scanf("%d",&per); 
			Resize( per, image);
			printf("Resizing works");
			DeleteImage(image);
			break;
			
		case 16:
			printf("Enter border width:") ;
			scanf("%d", &bord) ;
			printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
			printf("Select border color from the options: ");
			scanf("%s",color);
			AddBorder(image,color,bord);
			DeleteImage(image);
			break;
		default:
			
			printf("Invalid selection!\n");
			break;
		}

		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &choice);
	}

#endif
	

	return 0;
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
	printf(" 6:  Color-Filter an image\n");
	printf(" 7:  Sketch the edge of an image\n");
	printf(" 8:  Shuffle an image\n");
	printf(" 9:  Posterize the image\n");
	printf(" 10: Fill lights to an image\n");
	printf(" 11: Overlay an image \n");
	printf(" 12: Bonus, Cut and Paste operation on image \n");
	printf(" 13: Resize \n");
	printf(" 14: Rotate\n");
	printf(" 15. Autotest \n ");
	printf(" 16. Add Border \n");
	printf(" 17. Exit \n ");
}


/* auto test*/
IMAGE  *AutoTest(IMAGE *image)
{
	char fname[SLEN] = "RingMall";
	char sname[SLEN];

	image=ReadImage(fname);
	BlackNWhite(image);
	strcpy(sname, "bw");
	SaveImage(sname,image);
	DeleteImage(image);
	printf("Black & White tested!\n\n");

	image=ReadImage(fname);
	VFlip(image);
	strcpy(sname, "vflip");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("VFlip tested!\n\n");

	image=ReadImage(fname);
	HMirror(image);
	strcpy(sname, "hmirror");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("HMirror tested!\n\n");

	image=ReadImage(fname);
	ColorFilter(image, 180, 180, 50, 70, 0, 255, 0);
	strcpy(sname, "colorfilter");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("Color Filter tested!\n\n");

	image=ReadImage(fname);
	Edge(image);
	strcpy(sname, "edge");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("Edge Detection tested!\n\n");


	image=ReadImage(fname);
	Shuffle(image);
	strcpy(sname, "shuffle");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("Shuffle tested\n\n");

	image=ReadImage(fname);
	Posterize (image, 7) ; 
	strcpy(sname, "poster"); 
	SaveImage(sname, image) ;
	DeleteImage(image); 
	printf("Posterize tested!\n\n");

	image=ReadImage(fname);
	FillLight (200, 20,image) ; 
	strcpy(sname, "light"); 
	SaveImage(sname, image) ;
	DeleteImage(image); 
	printf("Fill Light  tested!\n\n");

	image=ReadImage(fname);
	strcpy(sname, "Peter");
	Overlay(sname, image, 350, 300);
	strcpy(sname, "overlay_peter");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("Overlay Tested!\n\n");

	image=ReadImage(fname);
	strcpy(sname, "Spider");
	Overlay(sname , image, 90, -10) ; 
	strcpy(sname, "overlay_spider"); 
	SaveImage(sname, image) ; 
	DeleteImage(image);	
	printf("overlay tested!\n\n");

	image=ReadImage(fname);
	CutPaste( image, 370, 20, 27, 57, 3);
	strcpy(sname, "cutPaste");
	SaveImage(sname, image);
	DeleteImage(image);	
	printf("Cut Paste Tested! \n\n");

        image = ReadImage(fname);
        Rotate(image);
        strcpy(sname,"rotate");
        SaveImage(sname, image);
        printf("Rotate Tested\n");
	DeleteImage(image);
	
	image=ReadImage(fname);
	Resize(175,image);
	strcpy(sname,"bigresize");
	SaveImage(sname, image);
	DeleteImage(image);
	printf("Resizing Large Tested \n");

        image=ReadImage(fname);
        Resize(60,image);
        strcpy(sname,"smallresize");
        SaveImage(sname, image);
        printf("Resizing Small Tested \n ");
	DeleteImage(image);

	image = ReadImage(fname);
	AddBorder(image, "black",10);
	strcpy(sname, "outerborder");
	SaveImage(sname, image);
	printf("Outer Border Tested\n");	
	DeleteImage(image);
	exit (0);
}
