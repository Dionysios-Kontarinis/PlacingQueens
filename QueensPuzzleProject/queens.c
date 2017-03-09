#include <stdlib.h>
#include <stdio.h>

// Creates the rules.txt file for the N queens problem (N is provided by the user).
int main (int argc, char *argv[])
{
	// The file where we will write the rules (constraints) which will be passed to the SAT solver.
	FILE *file;	

	int i, j, k, l, dim, **chessboard, counter = 0;
	
	// The dimension of the chessboard is a parameter entered by the user.
	dim = atoi(argv[1]);

	// Create an array where each element has a different number, from 1 to N*N.
	// These N*N numbers will represent our variables:
	// each one will be set to "True" or "False" by the SAT solver, depending on whether it places there a Queen or not.
	chessboard = (int **) malloc (dim * sizeof(int *));
	for (i=0; i<dim; i++)
		chessboard[i] = (int *) malloc (dim * sizeof(int));

	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
			chessboard[i][j] = (i*dim) + (j+1);
	
	// Create and open the file where we'll write the rules.
	if ( (file=fopen("rules.txt", "w")) == NULL )
	{
		printf("Cannot open file. \n");
		exit(1);
	}

	/*
	Rules file example (DIMACS format):

	p cnf 5 3
	1 -5 4 0
	-1 5 3 4 0
	-3 -4 0

	The line "p cnf nbvar nbclauses" indicates that the instance is in CNF format;
	"nbvar" is the number of variables in the file;
	"nbclauses" is the number of clauses in the file.
	The clauses follow: each clause is a sequence of distinct non-null numbers,
	between -nbvar and nbvar, ending with 0 on the same line;
	it cannot contain the opposite literals i and -i simultaneously.
	Positive numbers denote the corresponding variables.
	Negative numbers denote the negations of the corresponding variables.
	*/

	// Write a first line of space characters.
	// It will be substituted, at the end, by the proper "p cnf #vars #clauses" line.
	fprintf(file, "                                       \n");

	// Write the rules in the file.
	// The variable "counter" keeps track of the number of rules written.
	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
		{
			// Rules for the rows (no two queens on the same row):
			for (l=j+1; l<dim; l++)
			{
				fprintf(file, "-%d -%d 0\n", chessboard[i][j], chessboard[i][l]);
				counter++;
			}
			// Rules for the columns (no two queens on the same column):
			for (k=i+1; k<dim; k++)
			{
				fprintf(file, "-%d -%d 0\n", chessboard[i][j], chessboard[k][j]);
				counter++;
			}
			// Rules for the diagonals (no two queens on the same diagonal):
			for (k=i+1, l=j+1; (k<dim) && (l<dim); k++, l++)
			{
				fprintf(file, "-%d -%d 0\n", chessboard[i][j], chessboard[k][l]);
				counter++;
			}
			for (k=i+1, l=j-1; (k<dim) && (l>=0); k++, l--)
			{
				fprintf(file, "-%d -%d 0\n", chessboard[i][j], chessboard[k][l]);
				counter++;
			}
		}	
	
	// Add rules stating that, at each line, we should have at least 1 queen,
	// so that we have, at the end, at least N queens on the board.
	for (i=0; i<dim; i++)
	{
		for (j=0; j<dim; j++)
			fprintf (file, "%d ", chessboard[i][j]);
		fprintf(file, "0\n");
		counter++;
	}
	
	// Properly set the first line of the rules file according to the Dimacs format.
	rewind(file);      // or: fseek(file, 0, SEEK_SET);
	fprintf(file, "p cnf %d %d", dim*dim, counter);
	fclose(file);

	for (i=0; i<dim; i++)
		free(chessboard[i]);
	free(chessboard);
	
	return 0;
} 
