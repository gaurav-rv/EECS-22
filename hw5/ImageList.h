#ifndef ImageListh
#define ImageListh
#include "Image.h" 

typedef struct ImageList ILIST;
typedef struct ImageEntry IENTRY;
struct ImageEntry
{
ILIST *List; /* pointer to the list which this entry belongs to */
IENTRY *Next; /* pointer to the next entry, or NULL */
IENTRY *Prev; /* pointer to the previous entry, or NULL */
IMAGE *Image; /* pointer to the struct for the image */
};
struct ImageList
{
unsigned int Length; /* Length of the list */
IENTRY *First; /* pointer to the first entry, or NULL */
IENTRY *Last; /* pointer to the last entry, or NULL */
};

ILIST *NewImageList(void);

void DeleteImageList(ILIST *l);

void AppendImage(ILIST *l, IMAGE *image);

void ReverseImageList(ILIST *l);

void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame) ;

void ResizeImageList(ILIST *l, unsigned int percentage) ;

unsigned int FastImageList(ILIST *l, unsigned int ff_factor) ;
#endif
