/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
    //YOUR CODE HERE
    //printf("MandelbrotIterations \n");
    //printf("Max iters: %u \n", maxiters);
    //printf("Threshold: %e \n", threshold);
    ComplexNumber* Z = newComplexNumber(0.0, 0.0);
    ComplexNumber* temp1, *temp2;
    u_int64_t iter = 1;
    //printf("Center Re: %f\n",Re(point));
    //printf("Center Re: %f\n",Re(point));
    while (iter < maxiters) {
    	temp1 = ComplexProduct(Z, Z);
    	temp2 = ComplexSum(temp1, point);
    	freeComplexNumber(temp1);
    	freeComplexNumber(Z);
    	Z = temp2;
        //printf("real: %f \n", Re(Z));
        //printf("im: %f \n", Im(Z));
        //printf("complexabs: %f\n", ComplexAbs(Z));
    	if (ComplexAbs(Z) >= threshold) {
    		freeComplexNumber(Z);
    		return iter;
    	}
    	iter++;
    }
    freeComplexNumber(Z);
  	return 0;
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //YOUR CODE HERE
    //Output just needs to be filled in
    double invres = 1.0 / ((int) resolution);
    int index = 0;

    printf("\n\nscale: %f\n resolution: %d\n", scale, resolution);
    //printf("Startingngngngngn\n");
    for (int j = ((int) resolution); j >= -1 * ((int) resolution); j--) {
    	//printf("Reach %d \n", j);
    	for (int i =  -1 * ((int) resolution); i <= ((int) resolution); i++) {
    		//printf("Reachin\n");
    		ComplexNumber* offset = newComplexNumber(i * scale * invres, j * scale * invres);
    		ComplexNumber* newC = ComplexSum(center, offset);
    		//printf("\n\nIndex: %d\nComplex Number \n", index);
    		//printf("x: %f \n", Re(newC));
    		//printf("y: %f \n", Im(newC));
            //printf("threshold: %f \n", threshold);
    		freeComplexNumber(offset);
    		u_int64_t iternum = MandelbrotIterations(max_iterations, newC, threshold);
            //printf("iternum: %d \n", iternum);
    		freeComplexNumber(newC);
    		output[index] = iternum;
    		index++;
	    }
    }
}


