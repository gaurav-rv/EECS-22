#include "DIPs.h"
#include <stdio.h>
#include <stdlib.h>

/* Reverse Image Color */
IMAGE * BlackNWhite(IMAGE *image)
{
	int             x, y;
	unsigned char temp;
	for (y = 0; y < image->Height; y++) {
		for (x = 0; x < image->Width; x++) {
			temp = (GetPixelR(image,x,y)  + GetPixelB(image,x,y)  + GetPixelG(image,x,y))  / 3;
			SetPixelR(image,x,y,temp);
			SetPixelG(image,x,y,temp);
			SetPixelB(image,x,y,temp);	
		}
	}
return NULL;
}




/* Flip Image Vertically */
IMAGE *VFlip(IMAGE *image)
{
	int             x, y;
	unsigned char   r, g, b,r1,g1,b1;
    
	for (y = 0; y < image->Height/2; y++) {
		for (x = 0; x < image->Width; x++) {
			
			r = GetPixelR(image,x,((image->Height)-1-y));
			r1 = GetPixelR(image,x,y);			
			g = GetPixelG(image,x,((image->Height)-1-y));
			g1= GetPixelG(image,x,y);
            		b = GetPixelB(image,x,((image->Height)-1-y));
			b1=GetPixelB(image,x,y);
			SetPixelR(image,x,image->Height -1-y,r1 );
			SetPixelG(image,x,image->Height -1-y,g1 );
			SetPixelB(image,x,image->Height -1-y,b1 );
            		SetPixelR(image,x,y,r);
			SetPixelG(image,x,y,g);
			SetPixelB(image,x,y,b);
			
		}
	}
return NULL;
}


/* Mirror Image Horizontally */
IMAGE *HMirror(IMAGE *image)
{
	int       tempR,tempG,     tempB,x, y;

	for (y = 0; y < image->Height; y++) {
		for (x = 0; x < image->Width / 2; x++) {
			tempR=GetPixelR(image,( (image->Width)-1-x),y);
			SetPixelR(image,x,y,tempR);
                        tempG=GetPixelG(image,((image->Width)-1-x),y);
                        SetPixelG(image,x,y,tempG);
                        tempB=GetPixelB(image,((image->Width)-1-x),y);
                        SetPixelB(image,x,y,tempB);
		}
	}
return NULL;
}



IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, double factor_r, double factor_g, double factor_b)
{
	int x, y ; 
	int temp,tempR,tempG,tempB ; 		
	for (y=0; y<image->Height; y++)
	{
	for (x=0; x<image->Width; x++)
	{
		tempR= GetPixelR(image,x,y);
		tempG= GetPixelG(image,x,y);
		tempB= GetPixelB(image,x,y);
		if ((tempR < target_r + threshold)&&
			  (tempR > target_r - threshold)&&
			  (tempG < target_g + threshold)&&
			  (tempG > target_g - threshold)&&
			  (tempB < target_b + threshold)&&
			  (tempB > target_b - threshold))
		{
			temp = factor_r * tempR ; 
			if(temp>255) temp=255;
			else if(temp<0) temp=0;
			SetPixelR(image,x,y,temp);
				
	                temp = factor_g * tempG ;
                        if(temp>255) temp=255;
                        else if(temp<0) temp=0;
                        SetPixelG(image,x,y,temp);

                        temp = factor_r * tempB ;
                        if(temp>255) temp=255;
                        else if(temp<0) temp=0;
                        SetPixelB(image,x,y,temp);

			
		}
		}
	}
return NULL;
}


IMAGE *Edge(IMAGE *image){
              
        int x=0; int  y=0;
                 int Ar,Br,Cr;
                unsigned char tempr[image->Width][image->Height],tempb[image->Width][image->Height],tempg[image->Width][image->Height];
  for( y = 0; y < (image->Height); y++ )
    for( x = 0; x < (image->Width); x++ ) {
                tempr[x][y]=GetPixelR(image,x,y);
                tempg[x][y]=GetPixelG(image,x,y);
                tempb[x][y]=GetPixelB(image,x,y);
}

for(y=1;y<((image->Height)-1);y++)
for(x=1;x<((image->Width)-1);x++){

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
SetPixelR(image,x,y,Ar);
SetPixelG(image,x,y,Br);
SetPixelB(image,x,y,Cr);
}
      
return NULL;
}





/*Shuffle the image*/
IMAGE *Shuffle(IMAGE *image)
{
	int block_cnt = (SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV);
	int block_width = ((image->Width)/SHUFF_WIDTH_DIV);
	int block_height = (image->Height)/SHUFF_HEIGHT_DIV;
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
				int h_dest = ((dest_height * block_height) + i) % image->Height;
				int h_src  = ((src_height * block_height) + i) % image->Height; 
				for (j = 0; j < block_width; j++) {
				 	unsigned char temp,temp1;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % (image->Width); 
					int w_dest = ((dest_width * block_width) + j) % (image->Width);
					
					temp= GetPixelR(image,w_dest,h_dest);
					temp1 = GetPixelR(image,w_src,h_src);
					SetPixelR(image,w_dest,h_dest,temp1);
					SetPixelR(image,w_src,h_src,temp);

                                        temp= GetPixelG(image,w_dest,h_dest);
                                        temp1 = GetPixelG(image,w_src,h_src);
                                        SetPixelG(image,w_dest,h_dest,temp1);
                                        SetPixelG(image,w_src,h_src,temp);

                                        temp= GetPixelB(image,w_dest,h_dest);
                                        temp1 = GetPixelB(image,w_src,h_src);
                                        SetPixelB(image,w_dest,h_dest,temp1);
                                        SetPixelB(image,w_src,h_src,temp);


				}
			}
			/* Set marker as done */
			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}
		
	}

return NULL;
}



