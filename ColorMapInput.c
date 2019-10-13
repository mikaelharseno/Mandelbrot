/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
	//YOUR CODE HERE
	//printf("Before anything else\n");
	FILE* fileptr = fopen(colorfile, "r");
	//printf("%x \n",fileptr);
	if (fscanf(fileptr, "%d", colorcount) == 0) {
		printf("Error error \n");
		return NULL;
	} else {
		//printf("Open succeeded \n");
	}

	uint8_t buf[10]; 
	//printf("Not called \n");
	uint8_t** colorarray = (uint8_t**) malloc((*colorcount) * sizeof(uint8_t*));
	int index = 0;
    while (fscanf(fileptr,"%d %d %d", buf, &buf[1], &buf[2])==3) {
    	uint8_t* tricolorbox = (uint8_t*) malloc(3 * sizeof(uint8_t));
    	//printf("%u ", buf[0]);
    	//printf("%u ", buf[1]);
    	//printf("%u \n", buf[2]);
    	tricolorbox[0] = buf[0];
    	tricolorbox[1] = buf[1];
    	tricolorbox[2] = buf[2];
    	colorarray[index] = tricolorbox;
    	index++;
    }
    fclose(fileptr);

    return colorarray;
        
}


