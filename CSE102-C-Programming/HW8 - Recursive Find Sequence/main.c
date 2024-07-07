#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main () {

	int i;
	int seq_len;
	int first_element;
	
	printf("Please enter the sequence length: ");
	scanf("%d", &seq_len);
	printf("Please enter the first element: ");
	scanf("%d", &first_element);
	
	/* Initialize looplen and loop with the maximum loop length. */
	int looplen = seq_len/2;
	int *loop = (int*)calloc(looplen, sizeof(int));
	/* Initialize loop[0] with -1 to print the word in recursive function only once. */
	loop[0] = -1;
	
	
	check_loop_iterative(generate_sequence, first_element, seq_len, loop, &looplen);
	if (looplen == 0) {
		printf("No loop found.\n"); 
	}
	else {
		printf("Loop: {");
		for(i=0; i<looplen-1; i++) {
			printf("%d, ", loop[i]);
		}
		printf("%d}\n\n", loop[looplen-1]);
	}
	
	
	/* Create histogram array by using calloc to initialize the arr with 0s. */
	int *histogram = (int*)calloc(9, sizeof(int));
	hist_of_firstdigits(generate_sequence, first_element, seq_len, histogram, 9);
	
	printf("\n");
	printf("Histogram of the sequence: {");
	for(i=0; i<8; i++) {
		printf("%d, ", histogram[i]);
	}
	printf("%d}\n", histogram[8]);
	
	
	free(histogram);
	free(loop);

	return 0;
}
