#include<stdio.h>
#include "ImageList.h"
#include<assert.h>

ILIST *NewImageList(void)
{ 

	ILIST *e;
	e =(ILIST *) malloc(sizeof(ILIST));
	if (! e)
		{ perror("Out of memory! Aborting...");
	exit(10);
	} /* fi */
	e->Length = 0;
	e->First = NULL;
	e->Last = NULL;
	return e;
}



void DeleteImageList(ILIST *l)
{ 
assert(l);
IENTRY *i, *next;
i= l->First;
while (i){
next= i->Next;
DeleteImage(i->Image);
free(i);
i= next;
	}
free(l);
} 
/*
void AppendImage(ILIST *l, IMAGE *image){
	IENTRY *i = NULL;
	i= (IENTRY *) malloc (sizeof(IENTRY));
	assert(l);
	assert(image);

	i->Image = image;

	if (l->Last)
	{	
		 i->List = l;
		i->Next = NULL;
		i->Prev = l->Last;
		l->Last->Next = i;
		l->Last = i;
	}
	else
	{	 i->List = l;
		i->Next = NULL;
		i->Prev = NULL;
		l->First = i;
		l->Last = i;
	}

}
*/

    void AppendImage(ILIST *l, IMAGE *image){

    IENTRY *e = NULL; 
e = (IENTRY *)malloc(sizeof(IENTRY)); 
assert(image); 
e->Image = image; 
if(l->Last){ e->List = l;
 e->Next = NULL; 
e->Prev = l->Last;
 l->Last->Next = e;
 l->Last = e; 
} else{ e->List = l; 
e->Next = NULL;
 e->Prev = NULL;
 l->First = e;
 l->Last = e;
 } l->Length++;

    }



void ReverseImageList(ILIST *l){
      
	IENTRY *i = NULL;
	i = l->First;
	IENTRY *temp=NULL; 
	IENTRY *temp1=NULL;
	while (i)
		{	
		temp = i->Prev;
		i->Prev = i->Next;
		i->Next = temp;
		i = i->Prev ;
	}

	temp1= l->First;
	l->First = l->Last;
	l->Last = temp1; 
}


void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame) {
IENTRY *now, *later;
int i;

int new = l->Length;
	now = l-> First;
	for (i=0;i < new ; i++ ) {
	later = now->Next;
	if (i < SFrame || i > EFrame ){
		DeleteImage(now->Image);
		free(now);
				}
	
	else if(i == SFrame){
	l->First = now;
	now->Prev = NULL;
			}
 	
	else if (i==EFrame){
	l->Last = now;
	now->Next = NULL;	
			}
	}
	now  = later; 
}

void ResizeImageList(ILIST *l, unsigned int percentage) {
/*
use the convert functions for the DIP ones. Covert from Yuv to RGB call ur function and then covnert RGB to YUV.
*/
}

unsigned int FastImageList(ILIST *l, unsigned int ff_factor) {
assert(l);
IENTRY *current, *next,*temp;
int i, count = l->Length;
	if(l->Last && ff_factor >1){
		current = l->First;
		temp = l->First;
		for (i=0;i < l->Length; i++){
		 next = current->Next;
			if (i % ff_factor != 0){
			DeleteImage(current->Image);
			free(current);
			count--;
			}
		else 
		{
		if(i!=0){
			current->Prev = temp;
			temp->Next = current;
			temp=current;
			}
			}
		current=next;


		}
temp->Next = NULL;


		}

l->Length = count;
printf("Fast operation complete");
return count;
}
