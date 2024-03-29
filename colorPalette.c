/*********************
**  Color Palette generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"

//You don't need to call this function but it helps you understand how the arguments are passed in 
void usage(char* argv[])
{
	printf("Incorrect usage: Expected arguments are %s <inputfile> <outputfolder> <width> <heightpercolor>", argv[0]);
}

//Creates a color palette image for the given colorfile in outputfile. Width and heightpercolor dictates the dimensions of each color. Output should be in P3 format
int P3colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE

	//Attempts to open outputfile first
	FILE* outptr = fopen(outputfile, "w");
	if (outptr == NULL) {
		printf("File can't be opened / created\n");
		return 1;
	}

	int numcolors = -1;
	uint8_t** colorarray = FileToColorMap(colorfile, &numcolors);
	if (numcolors == -1 || colorarray == NULL) {
		fclose(outptr);
		return 1;
	}

	fprintf(outptr, "P3 %d %d %d\n", width, heightpercolor * numcolors, 255);

	for (int i = 0; i < numcolors; i++) {
		for (int k = 0; k < heightpercolor; k++) {
			for (int j = 0; j < width; j++) {
				fprintf(outptr, "%d ", colorarray[i][0]);
				fprintf(outptr, "%d ", colorarray[i][1]);
				fprintf(outptr, "%d", colorarray[i][2]);
				if (j < (width - 1)) {
					fprintf(outptr, " ");
				}
			}
			fprintf(outptr, "\n");
		}
	}

	fclose(outptr);

	return 0;
}

//Same as above, but with P6 format
int P6colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE
	FILE* outptr = fopen(outputfile, "w");
	if (outptr == NULL) {
		printf("File can't be opened / created\n");
		return 1;
	}

	int numcolors = -1;
	uint8_t** colorarray = FileToColorMap(colorfile, &numcolors);
	if (numcolors == -1 || colorarray == NULL) {
		fclose(outptr);
		return 1;
	}
	
	fprintf(outptr, "P6 %d %d %d\n", width, heightpercolor * numcolors, 255);

	//printf("Reach here\n");

	for (int i = 0; i < numcolors; i++) {
		for (int k = 0; k < heightpercolor; k++) {
			for (int j = 0; j < width; j++) {
				fwrite(&colorarray[i][0], sizeof(uint8_t), 1, outptr);
				fwrite(&colorarray[i][1], sizeof(uint8_t), 1, outptr);
				fwrite(&colorarray[i][2], sizeof(uint8_t), 1, outptr);
			}
		}
		//fprintf(outptr, "\n");
	}

	fclose(outptr);

	return 0;
}


//The one piece of c code you don't have to read or understand. Still, might as well read it, if you have time.
int main(int argc, char* argv[])
{
	//int man[2];
	//printf("Here1\n");
	//FileToColorMap("defaultcolormap.txt", man);
	//printf("Here2\n");
	if (argc != 5)
	{
		usage(argv);
		return 1;
	}
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	char* P3end = "/colorpaletteP3.ppm";
	char* P6end = "/colorpaletteP6.ppm";
	char buffer[strlen(argv[2]) + strlen(P3end)];
	sprintf(buffer, "%s%s", argv[2], P3end);
	int failed = P3colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P3colorpalette");
		return 1;
	}
	sprintf(buffer, "%s%s", argv[2], P6end);
	failed = P6colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P6colorpalette");
		return 1;
	}
	printf("P3colorpalette and P6colorpalette ran without error, output should be stored in %s%s, %s%s", argv[2], P3end, argv[2], P6end);
	return 0;
}




