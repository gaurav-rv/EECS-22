#include "Advanced.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
#include <string.h>


void FillLight( int number , int lightWidth, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
     
        int vert=0,hori=0,newb,wid=0,centre1=0,centre2=0,i=0,j=0,k=0,l=0,color1=0,value1=0,value2=0,value3=0;
        
        wid=lightWidth;
        while(number!=0){
        for(i=wid;i<(WIDTH-wid);i++)
                for(j=wid;j<(HEIGHT-wid);j++){
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
        hori++; }
                vert++;}}
                number--;
        
}
	
}


void Posterize( unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],  unsigned char B[WIDTH][HEIGHT],unsigned int pbits)
{
	{
        int i=0,j=0,k=0,x=0,newb=255;
        
        
       for(k=0;k<pbits;k++){

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
                
}
}

void Overlay( char fname2[SLEN],  unsigned char R[WIDTH][HEIGHT],  unsigned char G[WIDTH][HEIGHT],  unsigned char B[WIDTH][HEIGHT],  int x_offset, int y_offset)

                {
                
                int xco,yco,Red[WIDTH][HEIGHT], Green[WIDTH][HEIGHT], Blue[WIDTH][HEIGHT],i=0,j=0,a=0,b=0;
                xco=x_offset;
		yco=y_offset;
                if(strcmp (fname2,  "Peter")== 0){
                ReadImage ("Peter", R, G, B);
                }
                else if (strcmp(fname2, "Spider")==0){ 
		ReadImage("Spider",R,B,G);
		}
                for(a=0;a<WIDTH;a++)
                for(b=0;b<HEIGHT;b++){
                Red[a][b]=R[a][b];
                Green[a][b]=G[a][b];
                Blue[a][b]=B[a][b];
                }

        ReadImage ("RingMall", R, G, B);
        
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




