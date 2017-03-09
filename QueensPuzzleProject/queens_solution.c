#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Translates the solution found by the solver into an understandable format and displays it at the console.
int main (int argc, char *argv[])
{
	FILE *file;

	int i, j, dim, variable, *js;

	if ( (file=fopen("results.txt", "r")) == NULL )
	{
		printf("Cannot open file. \n");
		exit(1);
	}

	// The "results.txt" file is assumed to contain the following:
	// A number of integers (positive and negative), separated by blank characters, ending with the (only) zero.
	// Each number, except the zero at the end, represents a variable:
	// if the number is positive (resp. negative), then the variable is set to be True (resp. False).

	// We could use the "fseek" function, if the "results.txt" file contained some initial characters,
	// which were not to be processed.
	// fseek (file, 13, SEEK_SET);

	// Go to the end of the file and find the vale of N using "sqrt(dim)".
	fscanf(file, "%d", &variable);
	while (variable != 0) {
		dim = variable;
		fscanf(file, "%d", &variable);
	}

	if (dim < 0) {
		dim = (-1) * dim;
	}

	dim = sqrt(dim);

	js = malloc (dim * sizeof(int));

	// Now, we use the "fseek" function, in order to get back to the beginning of the "results.txt" file.
	fseek (file, 0, SEEK_SET);
		
	printf("dimension is = %d \n \n", dim);
	//fscanf(file, "%d", &variable);
	//printf("Variable = %d \n", variable);
	//fscanf(file, "%d", &variable);
	//printf("Variable = %d \n", variable);

	// Print the numbers of the columns.
	printf("  ");
	for (i=1; i<=dim; i++) {
		printf("%d ", i);
	}

	for (i=1; i<=dim; i++)
	{
		// Print the numbers of the rows.
		printf("\n%d ", i);
		for (j=1; j<=dim; j++)
		{
			// Print a single row of the chessboard.
			// We assume that the numbers (variables) appear in ascending order in the "results.txt" file.
			fscanf(file, "%d", &variable);
			// Print a Queen.
			if (variable >= 0) {
				printf("Q ");
				js[i] = j;
			} else {
				// Print an empty square.
				printf("- ");
			}
		}
	}

	fclose(file);

	// Print the coordinates of the queens (positive value variables). 
	printf("\n\nQueens found at the following coordinates (num-of-row, num-of-column): \n");
	for (i=1; i<=dim; i++) {
		printf("(%d,%d) ", i, js[i]);
	}
	printf("\n\n");

	free(js);

	return 0;
}
