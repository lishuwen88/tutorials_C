#include <stdlib.h>
#include <stdio.h>

//static
int my_var = 80;

int main(){

	//dynamic
	int *x = malloc(sizeof(int));	// give me space for 1 int
	int *arr = malloc(sizeof(int)*100);	// give me space for 100 ints

	*x = 120;
	arr[90] = 0xFEEDBEEF;
	//arr[101] = 8; // OUT OF BOUNDS, BAD
	
	free(arr);	// I dont want this memory anymore
	arr = NULL;	// accessing free block, freeing free block will crash program

	double *darr;
	darr = calloc(sizeof(double), 100);
	// is same as  -- darr = malloc(sizeof(double)*100);
	
	darr = realloc(darr, sizeof(double)*500);


}
