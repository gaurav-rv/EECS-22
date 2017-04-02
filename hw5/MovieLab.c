
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "DIPs.h"
#include "Image.h"
#include "ImageList.h"
#include "Movie.h" 

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
IMAGE* ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function	*/
typedef void MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP);
/*
( go through the entire list and use the convert functions )
*/


int main(int argc, char *argv[])
{
	int x = 0;
	int W=0;
	int H=0,nFrames,nfact;
	int bw,vflip,hmirror,edge,poster,cut,resize,fast,rvs,m;
	char *fin = NULL, *fout = NULL;
	MOP_F *func_ptr;
	MOVIE *movie =NULL;
	ILIST *l;
	char fname[100];
 /*entering while loop to check options entered*/
	while(x < argc)
	{
		/*specify input video*/
		if(0 == strcmp(&argv[x][0], "-i")) 
		{
			if(x < argc - 1)
			{
				fin = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fin, argv[x + 1]);
				strcat( fin, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for input name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify output video*/
		if(0 == strcmp(&argv[x][0], "-o")) 
		{
			if(x < argc - 1)
			{
				fout = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fout, argv[x + 1]);
				strcat( fout, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for output name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/
		
	       if(0 == strcmp(&argv[x][0], "-s"))
               		 {
                        	if(x < argc - 1)
                        	{
                           		if(sscanf(argv[x+1], "%dx%d", &W, &H) !=2)
						{
							 
                        				  printf(" \n The value of Width and Height is %d,%d \n ", W, H );
						}
				}
		
			else 	{
                                         printf("Missing argument for WIDTH!");
                            		 free(fin);
                               		 free(fout);
                               		 return 9;
		      		}
			x +=2;
			continue;
			 }
		
		
                if(0 == strcmp(&argv[x][0], "-f"))
                {
                    if(x < argc - 1)
                        {
                           if(sscanf(argv[x+1], "%d", &nFrames) !=1)
                                {
                		  printf(" \n The value of Nframes is %d \n", nFrames );
		    	          printf("Please input 2 arguments");
                        	  return 9;
                                }
                        }
                    else 
				{
                        		printf("Please input 1 arguments");
			
                                         

				        }
                x +=2;
                continue;
                }

        movie = CreateMovie(nFrames,W,H);
        ReadMovie(fin,nFrames,W,H,movie);
	
                if(nFrames && W && H && fin){
                        movie = CreateMovie(nFrames, W, H);
                        printf("Creating Movie is complete!\n");
                        ReadMovie(fin, nFrames, W, H, movie);
                        printf("Reading Movie is complete!\n");
                }
	 
			if(0 == strcmp(&argv[x][0], "-posterize")){

			func_ptr = &Posterize;
			 Movie_DIP_Operation(movie, func_ptr); 
			printf("Posterize operation is complete!\n"); 
			SaveMovie(fout, movie);

			x+= 1;
			 continue; 
		}	
		
		     if(0 == strcmp(&argv[x][0], "-bw")){

                        func_ptr = &BlackNWhite;
                         Movie_DIP_Operation(movie, func_ptr);
                        printf("Black N White  operation is complete!\n");
                        SaveMovie(fout, movie);

                        x+= 1;
                         continue;
                }
	
                if(0 == strcmp(&argv[x][0], "-fast"))
                {
                    if(x < argc - 1)
                        {
                           if(sscanf(argv[x+1], "%d", &nfact) !=1)
                                {
                                  printf(" \n The value of Nframes is %d \n", nfact );
                                  printf("Please input 2 arguments");
                                  return 9;
                                }
                        }
                    else
                                {
                                        printf("Please input 1 arguments");



                                        }
		FastImageList(movie->Frames,nfact);
                x +=2;
                continue;
                }
/*
                if(0 == strcmp(&argv[x][0], "-cut"))
                {
                    if(x < argc - 1)
                        {
                           if(sscanf(argv[x+1], "%d-%d", &SFrame, &EFrame) !=1)
                                {
                                  printf(" \n The value of Nframes is %d \n", nfact );
                                  printf("Please input 2 arguments");
                                  return 9;
                                }
                        }
                    else
                                {
                                        printf("Please input 1 arguments");



                                        }
                CropImageList(movie->Frames,SFrame,EFrame);
                x +=2;
                continue;
                }

*/


		     if(0 == strcmp(&argv[x][0], "-edge")){

                        func_ptr = &Edge;
                         Movie_DIP_Operation(movie, func_ptr);
                        printf("Edge operation is complete!\n");
                        SaveMovie(fout, movie);

                        x+= 1;
                         continue;
                }

		     if(0 == strcmp(&argv[x][0], "-VFlip")){

                        func_ptr = &VFlip;
                         Movie_DIP_Operation(movie, func_ptr);
                        printf("VFlip operation is complete!\n");
                        

                        x+= 1;
                         continue;
                }
    		        if(0 == strcmp(&argv[x][0], "-hmirror")){
 
                        func_ptr = &HMirror;
                        Movie_DIP_Operation(movie, func_ptr);
                        printf("Hmirror operation is complete!\n");
                        
 
                x+= 1;
                continue;
                }

		        if(0 == strcmp(&argv[x][0], "-rvs")){
 
                        ReverseImageList(movie->Frames);
                        printf("Reverse video operation is complete!\n");
                        SaveMovie(fout, movie);
 
                x+= 1;
                continue;
                }		

		
	if(0 == strcmp(&argv[x][0], "-h")) 
		{ 
			PrintUsage();
			free(fin);
			free(fout);
			return 0;
		}
		x++;
	}
	
	if(!fin)
		{
			printf("Missing argument for input name!\n");
			PrintUsage();	
			free(fin);
			free(fout);
			return 5;
		}

	
	 if(!W)
	{
                printf("Missing argument for Width name!\n");
                PrintUsage();
                free(fin);
                free(fout);
                return 5;
        }

        if(!fout)
	{
                printf("Missing argument for output name!\n");
                PrintUsage();
                free(fin);
                free(fout);
                return 5;
        }
	/*
        
		if(bw==1){
	                 Movie_DIP_Operation(movie,BlackNWhite);
			 }      
		if(rvs==1){
			  ReverseImageList(movie->Frames);
			 }
		if(vflip==1)
			{
			Movie_DIP_Operation(movie,VFlip);	
			}
			*/
	SaveMovie(fout,movie); 
	DeleteMovie(movie); 
	free(fin);
	free(fout);
	fin = NULL;
	fout = NULL;
	return 0;
}

void PrintUsage()
{
	printf("\nFormat on command line is:\n"
	"MovieLab [option]\n"
	"-i [file_name]    to provide the input file name\n"
	"-o [file_name]    to provide the	output file name\n"
	"-f [no_frames]    to determine how many frames desired in the input stream\n"
	"-s [WidthxHeight] to set resolution of the input stream (widthxheight)\n"
	"-j                to generate the movie with JuliaSet sequences\n"
	"-bw               to activate the conversion to black and white\n"
	"-vflip            to activate vertical flip\n"
	"-hmirror          to activate horizontal flip\n"
	"-edge             to activate edge filter\n"
	"-poster           to activate posterize filter\n"
	"-cut [Start-End]  to crop the frame from the video from frame Start to frame End\n"  
	"-resize [factor]  to resize the video with the provided factor [1-100]\n"
	"-fast   [factor]  to fast forward the video with the provided factor [1+]\n"
	"-rvs              to reverse the frame order of the input stream\n"
	"-h                to show this usage information\n"
	);
}

IMAGE* ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H)
{
        /*defining local variables*/
        FILE *file;

        unsigned int x, y;
        unsigned char ch;
        IMAGE* image ;

        /*checking error*/
        assert(fname);
        assert(nFrame >= 0);

        image = CreateImage(W, H) ;
        assert(image) ;

        /*opening file stream*/
        file = fopen(fname, "r");
        assert(file) ;

        /*find desired frame*/
        fseek(file, 1.5 * nFrame * W * H, SEEK_SET);

        for(y = 0; y < H; y ++){
                for(x = 0; x < W; x ++){
                        ch = fgetc(file);
                        SetPixelY(image, x, y, ch);
                }/*rof*/
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelU(image, x, y, ch);
                        SetPixelU(image, x + 1, y, ch);
                        SetPixelU(image, x, y + 1, ch);
                        SetPixelU(image, x + 1, y + 1, ch);
                }
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelV(image, x, y, ch);
                        SetPixelV(image, x + 1, y, ch);
                        SetPixelV(image, x, y + 1, ch);
                        SetPixelV(image, x + 1, y + 1, ch);
                }
        }

        /*checking for error*/

        assert(ferror(file) == 0) ;

        /*closing stream and terminating*/
        fclose(file);
        file = NULL;
        return image;
}


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int i ; 
	int x, y;
	FILE *file;
	IENTRY *currFrame;

	 /*opening file stream*/
	 if(!(file = fopen(fname, "w"))){
			return 1;
	 }
	 
	 i = 0 ; 
	 printf("start savemovie, total frame %d\n", movie->NumFrames) ; 
	 currFrame = movie->Frames->First;
	 while(currFrame){
		for(y = 0; y < movie->Height; y ++){ 
			for(x = 0; x < movie->Width; x ++){
				fputc(GetPixelY(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelU(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelV(currFrame->Image, x, y), file);
			}
		}
		currFrame = currFrame->Next;	 
		i++ ; 
	 }

	 fclose(file);
	 file = NULL;

	 printf("The movie file %s has been written successfully! \n", fname);
	 printf("%d frames are written to the file %s in total \n", i, fname); 
	 return 0;
}



int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie){
        int x;
        IMAGE *image;
 
        for (x = 0; x < nFrame; x++)
        	{
    
                	image = ReadOneFrame(fname, x, W, H);
                	assert(image);
                	AppendImage(movie->Frames, image);
        	}
        return 0;

}


void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP){

	IENTRY *e, *n;
	e = movie->Frames->First;
	
		while(e)
			{
				YUV2RGBImage(e->Image);
				n= e->Next;
				MovieOP(e->Image);
				RGB2YUVImage(e->Image);				
				e = n;
			}	
}
