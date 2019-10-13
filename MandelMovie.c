/*********************
**  Mandelbrot fractal movie generator
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include <sys/types.h>

void printUsage(char* argv[])
{
  printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
  printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so 
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, u_int64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, u_int64_t resolution, u_int64_t ** output){
    //YOUR CODE HERE
    double mult = pow(finalscale / initialscale, (1.0 / (framecount - 1)));
    double scale = initialscale;
   // printf("Input args\n");
    for (int i = 0; i < framecount; i ++) {
    	//printf("MandelMovie scale: %f", scale);
    	//printf("Input args\n");
    	Mandelbrot(threshold, max_iterations, center, scale, resolution, output[i]);
    	scale = scale * mult;
    	//printf("Input args\n");
    }
}

/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
	//Tips on how to get started on main function: 
	//MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
	//Mayke you complete the steps below in order. 

	//STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
	/*
	Check the spec for examples of invalid inputs.
	Remember to use your solution to B.1.1 to process colorfile.
	*/

	//YOUR CODE HERE 
	double threshold = atof(argv[1]);
	u_int64_t max_iterations = atoi(argv[2]);
	double re = atof(argv[3]);
	double im = atof(argv[4]);
	ComplexNumber* center = newComplexNumber(re, im);
	double initialscale = atof(argv[5]);
	double finalscale = atof(argv[6]);
	int framecount = atoi(argv[7]);
	u_int64_t resolution = atoi(argv[8]);
	char* outputfolder = argv[9];
	char* colorfile = argv[10];
	int sz = (int) 2 * resolution + 1;


	//printf("Input args %d \n", framecount);

	//STEP 2: Run MandelMovie on the correct arguments.
	/*
	MandelMovie requires an output array, so make sure you allocate the proper amount of space. 
	If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
	*/

	//YOUR CODE HERE 
	u_int64_t** outputarray = (u_int64_t**) malloc(framecount * sizeof(u_int64_t*));
	for (int i = 0; i < framecount; i++) {
		outputarray[i] = (u_int64_t*) malloc(sz * sz * sizeof(u_int64_t));
	}
	MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, outputarray);

	//printf("Input args\n");
	//STEP 3: Output the results of MandelMovie to .ppm files.
	/*
	Convert from iteration count to colors, and output the results into output files.
	Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
	Feel free to create your own helper function to complete this step.
	As a reminder, we are using P6 format, not P3.
	*/

	//YOUR CODE HERE 

	int numcolors = -1;
	uint8_t** colorarray = FileToColorMap(colorfile, &numcolors);
	if (numcolors == -1 || colorarray == NULL) {
		return 1;
	}

	char path[200];

	for (int k = 0; k < framecount; k ++) {
		sprintf(path, "%s/frame%05d.ppm", outputfolder, k);
		printf("%s\n",path);
		//sprintf(path,"tesxt.txt");
		FILE* outptr = fopen(path, "w");
		if (outptr == NULL) {
			printf("File can't be opened / created\n");
			return 1;
		}
		fprintf(outptr, "P6 %d %d %d\n", sz, sz, 255);

		u_int64_t* thisoutput = outputarray[k];
		int index = 0;
		uint8_t blackarray[3];
		blackarray[0] = 0;
		blackarray[1] = 0;
		blackarray[2] = 0;
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				int correctindex;
				if (thisoutput[index] == 0) {
					fwrite(blackarray, sizeof(uint8_t), 3, outptr);
				} else {
					fwrite(colorarray[(thisoutput[index] - 1)% numcolors], sizeof(uint8_t), 3, outptr);
				}
				//fwrite(&colorarray[(thisoutput[index] - 1)% numcolors][1], sizeof(uint8_t), 1, outptr);
				//fwrite(&colorarray[(thisoutput[index] - 1)% numcolors][2], sizeof(uint8_t), 1, outptr);
				index++;
			}
		}

		fclose(outptr);
	}

	printf("%s\n", argv[1]);
	printf("Thres: %f \n", threshold);



	//STEP 4: Free all allocated memory
	/*
	Make sure there's no memory leak.
	*/
	//YOUR CODE HERE 





	return 0;
}

