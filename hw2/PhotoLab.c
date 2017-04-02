/*********************************************************************/
/* PhotoLab.c: homework assignment #2, for EECS 22,  Fall 2014       */
/*                                                                   */
/* History:                                                          */
/* 10/07/14 Manjunath MV  updated for EECS22 assignment2 Fall2014    */
/* 10/03/13 Che-Wei Chang  updated for EECS22 assignment2 Fall2013   */
/* 10/02/12 Weiwei Chen  updated for EECS22 assignment2 Fall2012     */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*** global definitions ***/
#define WIDTH  640		/* Image width */
#define HEIGHT 500		/* image height */
#define SLEN    80		/* maximum length of file names and string*/
#define SHUFF_HEIGHT_DIV 4      /* Height division for shuffling */
#define SHUFF_WIDTH_DIV 4       /* Width division for shuffling */
/*** function declarations ***/

/* print a menu */
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
		int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) ; 

/* sharpen the image */
void	Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* edge detection */
void	Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* add border */
void	AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
		char color[SLEN]);

/* Test all functions */
void	AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int	main()
{
	/*
 	* Two dimensional arrays to hold the current image data. One array
 	* for each color component
 	* */
	int s=1;
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];
	int target_r=180; int target_g=180; int target_b=50; int threshold=70; int replace_r=0; int replace_g=255; int replace_b=0;
	/*  Please replace the following code with proper menu  */
	/*	with function calls for DIP operations		*/



	AutoTest(R, G, B);
	BlackNWhite(R,G,B);
	VFlip(R,G,B);
	HMirror(R,G,B);
        ColorFilter( R, G,  B, target_r, target_g, target_b,  threshold,  replace_r,  replace_g, replace_b);
	AddBorder(R,G,B,"black");
	Edge(R,G,B);
	Shuffle(R,G,B);
/*  end of replacing*/
}

int ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
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
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);

	return (0);
}


/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
  int x, y;

  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
      B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
      R[x][y] = (unsigned char) (B[x][y]*1.6);
      G[x][y] = (unsigned char) (B[x][y]*1.6);
  }
}

/* auto test*/
void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char fname[SLEN] = "RingMall";
  	char sname[SLEN];

	ReadImage(fname, R, G, B);
	Aging(R, G, B);
  	strcpy(sname, "aging");
	SaveImage(sname, R, G, B);
	printf("Aging tested!\n\n");

	/*
 	*	 	
 	* Filling this part with the call to your DIP functions
 	*/				
}



 void    BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
        char fname[SLEN] = "RingMall";
        char sname[SLEN] = "bw";
        ReadImage(fname, R, G, B);
		unsigned char average;
		 int x, y;
  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
      average= ( R[x][y]+G[x][y]+B[x][y] )/3;
	  R[x][y]= G[x][y]=B[x][y]= average;
  }
        SaveImage(sname, R, G, B);
        printf("bw tested!\n\n");
 }
VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
 {
        char fname[SLEN] = "RingMall";
        char sname[SLEN] = "VFlip";
        ReadImage(fname, R, G, B);
		unsigned char temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,tem5,tem6,tem7,tem8;
		 int x, y, temp;
		 SaveImage(sname, R, G, B);
        printf("VFlip tested!\n\n"); 
	for( y = 0; y < (HEIGHT/2); y++ )
    for( x = 0; x < WIDTH; x++ ) {
	temp1=R[x][y];
	temp2=temp1;
	temp3=R[x][(HEIGHT/2+y)];
	temp4=temp3;
	R[x][y]=temp4;
	R[x][(HEIGHT-y)]=temp2;

	temp5=G[x][y];
	temp6=temp5;
	temp7=G[x][(HEIGHT-y)];
	temp8=temp7;
	G[x][y]=temp8;
	G[x][HEIGHT-y]=temp6;
		
	tem5=B[x][y];
	tem6=tem5;
	tem7=B[x][HEIGHT-y];
	tem8=tem7;
	B[x][y]=tem8;
	B[x][HEIGHT-y]=tem6;
	}
}
void    HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
        char fname[SLEN] = "RingMall";
        char sname[SLEN] = "hmirror";
        ReadImage(fname, R, G, B);
		 int x, y;
  for( x = 0; x < (WIDTH/2); x++ )
    for( y = 0; y < HEIGHT; y++ ) {
	  R[x][y]= R[WIDTH-x][y]; 
	  G[x][y]= G[WIDTH-x][y];
	  B[x][y]= B[WIDTH-x][y];
  }
        SaveImage(sname, R, G, B);
        printf("hmirror tested!\n\n");
 }


void    ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
                int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
        char fname[SLEN] = "RingMall";
        char sname[SLEN] = "colorfilter";
        ReadImage(fname, R, G, B);
		 int x, y, z, i, j, k;
		unsigned char a,b,c;
	 for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
	i= (int) R[x][y];
	j= (int) G[x][y];
	k= (int) B[x][y];
	
	
	if (target_g+threshold > i){
		if(i > target_g-threshold){
		if(target_r+threshold > j ){
		if(target_r-threshold < j ){
		if(target_b+threshold > k){
		if(target_b-threshold<k){
		R[x][y]=replace_r;
		G[x][y]=replace_g;
		B[x][y]=replace_b;
}}
}
}
}
}
}


        SaveImage(sname, R, G, B);
        printf("color filter tested!\n\n");
 }







/*
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
                char fname[SLEN] = "RingMall";
        ReadImage(fname, R, G, B);

        int vert=0,hori=0,newb,number=0,wid=0,centre1=0,xL,yL,centre2=0,i=0,j=0,k=0,l=0,color1=0,value1=0,value2=0,value3=0;

        printf("Enter the number of lights you require");
    scanf("%d",&number);
        printf("Enter the width of each light ");
        scanf("%d",&wid);
        while(number!=0){

        for(i=wid;i<(HEIGHT-wid);i++)
                for(j=wid;j<(WIDTH-wid);j++){
        srand(time(NULL));
        centre1 = (rand() % HEIGHT ) +1;
        centre2 = (rand() % WIDTH )+1;
        color1= (rand() %3)+1;
        if(color1==1){
        value1=255;
        value2=0;
        value3=0;
        }
        if(color1==2){
        value1=0;
        value2=255;
        value3=0;
        }
        if(color1==3){
        value1=0;
        value2=0;
        value3=255;
                }
        newb=wid/2;
vert=0;
        for(k=centre1;k<(centre1+wid);k++){
        hori=0;
	for(l=centre2;l<(centre2+wid);l++){
        if(( k==(centre1+wid/2)) || (l==(centre2+wid/2))  ||(vert == centre1+(wid/2)) || (hori==centre2+(wid/2))|| (vert-hori==0)|| (vert- (wid-hori)==0)  ){
                R[k][l]=value1;
                G[k][l]=value2;
                B[k][l]=value3;
}

	hori++;	}
		vert++;}}


                printf("\nEnd of while loop");
        }
                SaveImage("shuffle", R, G, B);
        printf("Shuffle tested!\n\n");

}








void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
        char fname[SLEN] = "RingMall";
        ReadImage(fname, R, G, B);
        int number=0,i=0,j=0,pos=0,k=0,x=0,numbe,numbe2,newb=255;
        unsigned char numbe3;
        printf("Enter the number of posterizing bits (1-8)");
        scanf("%d",&pos);
       for(k=0;k<pos;k++){
				
				x=x+ (1<<k);
				newb<<=1;
				}
for (i=0;i<WIDTH; i++)
	for(j=0;j<HEIGHT;j++){
	R[i][j]  &=newb;
	G[i][j]  &=newb;
	B[i][j]  &=newb;
	R[i][j]  |= x ;
	G[i][j]  |= x ;
	B[i][j]  |= x ;
	
	}
                SaveImage("shuffle", R, G, B);
        printf("Shuffle tested!\n\n");

}
*/



void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
		{
	        char sname[20];
		int xco,yco,Red[WIDTH][HEIGHT], Green[WIDTH][HEIGHT], Blue[WIDTH][HEIGHT],i=0,j=0,a=0,b=0;
		printf("Enter Image you prefer, Spider or Peter");
		scanf("%s",&sname);
		if(strcmp (sname,  "Peter")== 0){
		ReadImage ("Peter", R, G, B);
		}
		else ReadImage("Spider",R,B,G);
		for(a=0;a<WIDTH;a++)
		for(b=0;b<HEIGHT;b++){
		Red[a][b]=R[a][b];
		Green[a][b]=G[a][b];
		Blue[a][b]=B[a][b];
		}
	
	ReadImage ("RingMall", R, G, B); 
	printf("Enter the x cordinates");
		scanf("%d",&xco);
		printf("Enter the y cordinate");
		scanf("%d",&yco);
		for(i=0;i<WIDTH;i++)
			for(j=0;j<HEIGHT;j++){
				if ((Red[i][j]<250) && (Green[i][j] < 250) && (Blue[i][j]<250 )){
				if(((i+xco)<WIDTH ) && (j+yco)<HEIGHT){	
				R[i+xco][j+yco]=Red[i][j];
				G[i+xco][j+yco]=Green[i][j];
				B[i+xco][j+yco]=Blue[i][j];
				
						}
				}
			}
	}
SaveImage("shuffle", R, G, B);
        printf("Shuffle tested!\n\n");
}


void    AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
		char color[SLEN]){
 char fname[SLEN] = "RingMall";
	int border_width;
	int value1=0,value2=0,value3=0,choice;
        char sname[SLEN] = "border";
        ReadImage(fname, R, G, B);
	printf("Enter Border length");
	scanf("%d",&border_width);
	printf("\nWhich color would you prefer?\n");
	printf("\n Type 1.Black,2.White,3.Red,4.Green,5.Blue,6.Yellow,7. Cyan, 8.Pink, 9. Orange ");
	scanf("%d",&choice);
	if(choice==1){
	value1=0;
	value2=0;
	value3=0;
	}
	if(choice==2){
	value1=255;
	value2=255;
	value3=255;
	}
	if(choice==3){
	value1=255;
	value2=0;
	value3=0;
	}
	if(choice==4){
	value1=0;
	value2=255;
	value3=0;
	}
	if(choice==5){
	value1=0;
	value2=0;
	value3=255;
	}
	if(choice==6){
	value1=255;
	value2=255;
	value3=0;
	}
	if(choice==7){
	value1=0;
	value2=255;
	value3=255;
	}
	if(choice==8){
	value1=255;
	value2=0;
	value3=255;
	}
	if(choice==9){
	value1=255;
	value2=165;
	value3=0;
	}
		 int x, y;
		 int j,k=0;
  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < border_width; x++ ) {
		R[x][y]=value1;
		G[x][y]=value2;
		B[x][y]=value3;
		R[WIDTH-(x+1)][y]=value1;
		G[WIDTH-(x+1)][y]=value2;
		B[WIDTH-(x+1)][y]=value3;
	}
	for( y = 0; y < border_width; y++ )
    for( x = 0; x < WIDTH; x++ ) {
		R[x][y]=value1;
		G[x][y]=value2;
		B[x][y]=value3;
		R[x][HEIGHT-(y+1)]=value1;
		G[x][HEIGHT-(y+1)]=value2;
		B[x][HEIGHT-(y+1)]=value3;
	}
	        SaveImage(sname, R, G, B);
        printf("border tested!\n\n");
 }


void    Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
		char fname[SLEN] = "RingMall";
        char sname[SLEN] = "edge";
        ReadImage(fname, R, G, B);
	int x=0; int  y=0;
		 int new,new2,new3,Ar,Br,Cr;
		unsigned char tempr[WIDTH][HEIGHT],tempb[WIDTH][HEIGHT],tempg[WIDTH][HEIGHT];
  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
		tempr[x][y]=R[x][y];
		tempg[x][y]=G[x][y];
		tempb[x][y]=B[x][y];
}
printf("end loop1");
for(y=1;y<(HEIGHT-1);y++)
for(x=1;x<(WIDTH-1);x++){

Ar = (8*tempr[x][y]-(tempr[x][y-1] + tempr[x-1][y-1]+tempr[x+1][y-1]+tempr[x-1][y]+tempr[x+1][y] + tempr[x-1][y+1]+tempr[x][y+1]+tempr[x+1][y+1]));
if(Ar>255){
Ar=255;
}
else if (Ar<0){
Ar=0;
}
Br=(8*tempg[x][y]-(tempg[x][y-1] + tempg[x-1][y-1]+tempg[x+1][y-1]+tempg[x-1][y]+tempg[x+1][y] + tempg[x-1][y+1]+tempg[x][y+1]+tempg[x+1][y+1]));
if(Br>255){
Br=255;
}
else if (Br<0){
Br=0;

}
Cr=8*tempb[x][y]-(tempb[x][y-1] + tempb[x-1][y-1]+tempb[x+1][y-1]+tempb[x-1][y]+tempb[x+1][y] + tempb[x-1][y+1]+tempb[x][y+1]+tempb[x+1][y+1]);
if(Cr>255){
Cr=255;
}
else if(Cr<0){
Cr=0;

}

R[x][y]=Ar;
G[x][y]=Br;
B[x][y]=Cr;
}
	 SaveImage(sname, R, G, B);
        printf("edge tested!\n\n");

}
