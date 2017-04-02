#include "Advanced.h"
#include "Image.h"

/* Posterization */
IMAGE *Posterize( IMAGE *image, unsigned int pbits)
{
	unsigned char maskzero[8] = {0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
        unsigned char maskone[8]  = {0x0     , 0x1     , 0x3     , 0x7     , 0xf      , 0x1f     , 0x3f     , 0x7f     };
	unsigned char tempR,tempG,tempB;
        int x, y;

        for(x = 0; x < image->Width; x ++)
        {
                for(y = 0; y < image->Height; y ++)
                {				tempR = GetPixelR(image,x,y);
						tempR = tempR & maskzero[pbits - 1];
						tempR = tempR | maskone[pbits - 1];
						SetPixelR(image,x,y,tempR);

						tempG = GetPixelG(image,x,y);
						tempG = tempG &  maskzero[pbits - 1];
						tempG = tempG |  maskone[pbits - 1];
						SetPixelG(image,x,y,tempG);

						tempB = GetPixelB(image,x,y);
						tempB = tempB & maskzero[pbits - 1];
						tempB = tempB | maskone[pbits - 1];
						SetPixelB(image,x,y,tempB);
                        
                              
                }
       }
		return NULL;
}

IMAGE *FillLight(  int number, int lightWidth,IMAGE *image)
{
    int x, y, i, h;
    int colorChoice;	
    
    srand( 0 );

    for ( i = 0; i < number; i++ )
    {
        x = ( rand()%((image->Width)-lightWidth)) + lightWidth/2;
        y = ( rand()%((image->Height)-lightWidth))+ lightWidth/2;
        
	colorChoice = (rand()%3)+1;

	int red_flag, blue_flag, green_flag;
	red_flag = blue_flag = green_flag = 0;
	if(colorChoice == 1)
		red_flag = 1;
	else if(colorChoice == 2)
		green_flag = 1;
	else 
		blue_flag = 1;
	
	for(h = -lightWidth/2; h < lightWidth/2; h++){
		SetPixelR(image,x+h,y,(255*red_flag));
		SetPixelR(image,x,y+h,(255*red_flag));
		SetPixelR(image,x+h,y+h,(255*red_flag));
		SetPixelR(image,x-h,y+h,(255*red_flag));
	
                SetPixelG(image,x+h,y,(255*green_flag));
                SetPixelG(image,x,y+h,(255*green_flag));
                SetPixelG(image,x+h,y+h,(255*green_flag));
                SetPixelG(image,x-h,y+h,(255*green_flag));

                SetPixelG(image,x+h,y,(255*blue_flag));
                SetPixelG(image,x,y+h,(255*blue_flag));
                SetPixelG(image,x+h,y+h,(255*blue_flag));
                SetPixelG(image,x-h,y+h,(255*blue_flag));
	
		
	}
    }
return NULL;
}



/* overlay with another image 
IMAGE  *Overlay(  char fname[SLEN],IMAGE *image, int x_offset, int y_offset)
{
                int xco,yco;
		unsigned char temp1,temp2,temp3;
		int i=0,j=0,a=0,b=0;
                xco=x_offset;
                yco=y_offset;
                if(strcmp (fname,  "Peter")== 0){
                image = ReadImage ("Peter");
                }
                else if (strcmp(fname, "Spider")==0){
                image = ReadImage("Spider");
                }
		unsigned char Red[image->Width][image->Height], Blue[image->Width][image->Height], Green[image->Width][image->Height];
                for(a=0;a<(image->Width);a++)
                for(b=0;b<(image->Height);b++){
                
		Red[a][b]=GetPixelR(image,a,b);
                Green[a][b]= GetPixelG(image,a,b);
                Blue[a][b]=GetPixelB(image,a,b);
                }

        image = ReadImage ("RingMall");
		int HEIGHT = image->Height;
		int WIDTH = image->Width; 
                for(i=0;i<(WIDTH);i++)
                        for(j=0;j<(HEIGHT);j++){
                                if ((Red[i][j]<250) && (Green[i][j] < 250) && (Blue[i][j]<250 )){
                                if(((i+xco)<(image->Width) ) && (j+yco)<(image->Height)){
                                
			        temp1=Red[i][j];
                                temp2=Green[i][j];
                                temp3=Blue[i][j];
				SetPixelR(image,(i+xco),(j+yco),temp1);
				SetPixelG(image,(i+xco),(j+yco),temp2);
				SetPixelB(image,(i+xco),(j+yco),temp3);

                                                }
                                }
                        }
return NULL;
} 
*/


IMAGE *Overlay(char fname[SLEN],IMAGE *image, int x_offset, int y_offset){

	int x, y;
	unsigned char temp1,temp2,temp3;
	IMAGE *overlay;
	overlay = ReadImage(fname); /* Read image to overlay */
	
	for (y = 0; y < overlay->Height; y++){
		for (x = 0; x < overlay->Width; x++){
			if(GetPixelR(overlay, x, y) <= 250 && GetPixelB(overlay, x, y) <= 250 && GetPixelG(overlay, x, y) <= 250){
				if ( x+x_offset < image->Width && y + y_offset < image->Height && x+x_offset > 0 &&  y +y_offset > 0 ){
					        temp1= GetPixelR(overlay,x,y);
        					temp2= GetPixelG(overlay,x,y);
	         				 temp3= GetPixelB(overlay,x,y);

					SetPixelR(image, x + x_offset, y + y_offset, temp1);
					SetPixelB(image, x + x_offset, y + y_offset, temp2);	
					SetPixelG(image, x + x_offset, y + y_offset, temp3);
				}
			}
		}
	}
return NULL;
free(overlay);
}



IMAGE *CutPaste(IMAGE *image, unsigned int startX, unsigned int startY, unsigned int x_width,unsigned int y_width, unsigned int pasteNumber)			
{
	unsigned char baseR[x_width][y_width];
	unsigned char baseG[x_width][y_width];
	unsigned char baseB[x_width][y_width];
	unsigned char temp1,temp2,temp3;
	
	int x, y, n;
	for(x = startX ; x < startX + x_width ; x++){
		for(y = startY ; y < startY + y_width ; y++){
			baseR[x-startX][y-startY] = GetPixelR(image,x,y);
			baseG[x-startX][y-startY] = GetPixelG(image,x,y);
			baseB[x-startX][y-startY] = GetPixelB(image,x,y);
	}}

	for( n = 1;  n <= pasteNumber ; n++){
		unsigned int  pasteX, pasteY;
		#ifdef DEBUG
			switch(n)
			{
				case 1:
					pasteX = 341;	
					pasteY = 19;
					break;
				case 2:
					pasteX = 315;
					pasteY = 18;
					break;
				case 3:
					pasteX = 288;
					pasteY = 16;
					break;
				default:
					break;
			}
		#else
			printf("Please input start x and y coordinates for paste no %d:   ", n);
			scanf("%u %u", &pasteX, &pasteY);
		#endif /* DEBUG */
		
		for(x = 0 ; x < x_width ; x++){
			for(y = 0 ; y < y_width ; y++){
				
				temp1 = baseR[x][y];
				temp2 = baseG[x][y];
				temp3 = baseB[x][y];
				SetPixelR(image,x+pasteX,y+pasteY,temp1);
				SetPixelG(image,x+pasteX,y+pasteY,temp2);
				SetPixelB(image,x+pasteX,y+pasteY,temp3);

				}	
		}
		
	}
return NULL;	
}




IMAGE *Rotate(IMAGE *image){

        int             x, y;
        unsigned char   r1[image->Width][image->Height],g1[image->Width][image->Height],b1[image->Width][image->Height];
	int Width,Height;
        for (y = 0; y < image->Height; y++) 
                for (x = 0; x < image->Width; x++) {

                       
                        r1[x][(image->Height)-y-1] = GetPixelR(image,x,y);
			g1[x][(image->Height)-y-1] = GetPixelG(image,x,y);
			b1[x][(image->Height)-y-1] = GetPixelB(image,x,y);
			Width= image->Width;
			Height=image->Height;
                   
}
	
	image->Height= Width;
	image->Width = Height;
        for (x = 0; x < image->Width; x++) 
                for (y = 0; y < image->Height; y++) {

                        SetPixelR(image,x,y,r1[y][x] );
                        SetPixelG(image,x,y,g1[y][x] );
                        SetPixelB(image,x,y,b1[y][x] );

                       /* SetPixelR(image,x,y,r);
                        SetPixelG(image,x,y,g);
                        SetPixelB(image,x,y,b); */
                }
        
return NULL;
}

IMAGE *Resize(unsigned int percentage, IMAGE *image){
        int new_width=(image->Width)*percentage/100.00;
        int new_height=(image->Height)*percentage/100.00;
        int x, y;
        IMAGE *resize = CreateImage(new_width,new_height);
        for(x=0;x<new_width;x++){
                for(y=0;y<new_height;y++){
                        SetPixelR(resize,x,y,GetPixelR(image,(x/(percentage/100.00)),y/(percentage/100.00)));
                        SetPixelG(resize,x,y,GetPixelG(image,(x/(percentage/100.00)),y/(percentage/100.00)));
                        SetPixelB(resize,x,y,GetPixelB(image,(x/(percentage/100.00)),y/(percentage/100.00)));
                }
        }
        image->Width=new_width;
        image->Height=new_height;
        image->R=resize->R;
        image->G=resize->G;
        image->B=resize->B;    
        return NULL;
}
/*
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration){

}
*/
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int bord)
{
        unsigned int x, y, border_R, border_G, border_B;
        int new_width = image->Width + (2*bord);
        int new_height = image->Height + (2*bord);
        IMAGE *border = CreateImage(new_width,new_height);
 
        if (strcmp(color, "black") == 0){
                border_R = 0;
                border_G = 0;
                border_B = 0;
        }
        else if (strcmp(color, "white") == 0){
                border_R = 255;
                border_G = 255;
                border_B = 255;
        }
        else if (strcmp(color, "red") == 0){
                border_R = 255;
                border_G = 0;
                border_B = 0;
        }
        else if (strcmp(color, "green") == 0){
                border_R = 0;
                border_G = 255;
                border_B = 0;
        }
        else if (strcmp(color, "blue") == 0){
                border_R = 0;
                border_G = 0;
                border_B = 255;
        }
        else if (strcmp(color, "yellow") == 0){
                border_R = 255;
                border_G = 255;
                border_B = 0;
        }
        else if (strcmp(color, "cyan") == 0){
                border_R = 0;
                border_G = 255;
                border_B = 255;
        }
        else if (strcmp(color, "pink") == 0){
                border_R = 255;
                border_G = 0;
                border_B = 127;
        }
        else if (strcmp(color, "orange") == 0){
                border_R = 255;
                border_G = 127;
                border_B = 0;
        }
 
        for (y = 0; y < bord; y++){
                for (x = 0; x < border->Width; x++){
                        SetPixelR(border, x, y, border_R);
                        SetPixelG(border, x, y, border_G);
                        SetPixelB(border, x, y, border_B);
                }
        }
        for (y = bord; y < border->Height - bord; y++){
                for (x = 0; x < bord; x++){
                        SetPixelR(border, x, y, border_R);
                        SetPixelG(border, x, y, border_G);
                        SetPixelB(border, x, y, border_B);
                }
                for (x = bord; x < border->Width - bord; x++){
                        SetPixelR(border, x, y, GetPixelR(image, x-bord, y - bord));
                        SetPixelG(border, x, y, GetPixelG(image, x-bord, y - bord));
                        SetPixelB(border, x, y, GetPixelB(image, x-bord, y - bord));
                }
                for (x = border->Width - bord; x < border->Width; x++){
                        SetPixelR(border, x, y, border_R);
                        SetPixelG(border, x, y, border_G);
                        SetPixelB(border, x, y, border_B);     
                }
        }
        for (y = border->Height - bord - 1; y < border->Height; y++)
                for (x = 0; x < border->Width; x++){
                        SetPixelR(border, x, y, border_R);
                        SetPixelG(border, x, y, border_G);
                        SetPixelB(border, x, y, border_B);
                }
 
        image->Width = new_width;
        image->Height = new_height;
        image->R = border->R;
        image->G = border->G;
        image->B = border->B;
	        return NULL;
}
