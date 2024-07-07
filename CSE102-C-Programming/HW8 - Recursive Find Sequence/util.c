#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/*
	TO-DO-LIST:
		1) Check if *seq has already been filled according to currentlen and seqlen.
		2) If not, then fill the *seq with the current element and call the next function.
*/
void generate_sequence(int xs, int currentlen, int seqlen, int *seq) {
	if (currentlen != seqlen) {
		seq[currentlen] = xs;
		if (xs%2 == 0) generate_sequence(xs/2, currentlen+1, seqlen, seq);
		else generate_sequence(3*xs+1, currentlen+1, seqlen, seq);
	} 
}

/* Get the first digit of a given number. */
int get_first_digit(int num) {
	while(num/10 != 0) num = num / 10;
	return num;
}

/*
	TO-DO-LIST : 
		1) If the seqlen and digit are not 0, malloc and generate the *seq.
		2) Check how many times the digit occurs in the sequence.
		3) Call the function again for next digit.
*/
void hist_of_firstdigits(void (*f)(int xs, int currentlen, int seq_len, int *seq), int xs, int seqlen, int *h, int digit) {
	
	int second_element;
	if (seqlen != 0 && digit != 0) {
		int *seq = (int*)calloc(seqlen ,sizeof(int));
		f(xs, 0, seqlen, seq);
		
		int i;
		for(i=0; i<seqlen; i++) {
			if (get_first_digit(seq[i]) == digit) h[digit-1]++;
		}
		
		free(seq);
		hist_of_firstdigits(f, xs, seqlen, h, digit-1);
	}
}

/*
	TO-DO-LIST :
		1) Check if the given array's length is bigger than 2 times of looplen because it's impossible if it's not.
		2) If it is, iterate till the (n-2*looplen).index and check if there is a loop with given looplen.
		3) If loop is found, then update *ls and *le values.
*/

int has_loop(int *arr, int n, int looplen, int *ls, int *le) {
	int result_value;
	int i, j, k;
	int is_loop;
	
	if (n < looplen*2) result_value = 0;
	else {
	
		for(i=0, result_value=0; i<=n-2*looplen && result_value == 0; i++) {
		
			for(k=i+looplen, is_loop=1; k<=n-looplen && is_loop == 1; k+=looplen) {
			
				for(j=0; j<looplen && is_loop == 1; j++) {
					if (arr[i+j] != arr[k+j]) is_loop = 0;
				}
			}
			
			if (k != n) is_loop = 0;
			
			if (is_loop) {
				result_value = 1;
				*ls = i;
				*le = i + looplen;
			}
		}
	}
	
	return result_value;
}

/*
	TO-DO-LIST :
		1) If loop[0] == -1, then print the sequence. (to print the sequence only once)
		2) If looplen>=2, check if there is a loop with that looplen.
		   If it's not, then update *looplen as 0, since no loop is found till this function; and function is done.
		
		3) If there is a loop, then fill the loop, and function is done.
		4) If there is not, then call the next function with new *looplen.
*/
void check_loop_iterative(void (*f)(int xs, int currentlen, int seq_len, int *seq), int xs, int seqlen, int *loop, int *looplen) {
	
	int *seq = (int*)calloc(seqlen ,sizeof(int));
	f(xs, 0, seqlen, seq);
	
	int i;
	if (loop[0] == -1) {
		printf("\nSequence: {");
		for(i=0; i<seqlen-1; i++) {
			printf("%d, ", seq[i]);
		}
		
		if (seqlen != 0) {
			printf("%d}\n\n", seq[seqlen-1]);
		}
		else printf("}\n\n");
		
		loop[0] = 0;
	}

	if (*looplen >= 2) {
		printf("Checking if there is a loop of length %d...\n", *looplen);
		
		int ls, le, is_found;
		
		/* Check if there is a loop with that looplen. */	
		is_found = has_loop(seq, seqlen, *looplen, &ls, &le);
		
		if (is_found) {
			printf("\n\nLoop detected with a length of %d.\n", *looplen);
			printf("The indexes of the loop's first occurence: %d (first digit), %d (last digit)\n", ls, le);
			for(i=0; i<*looplen; i++) {
				loop[i] = seq[ls+i];
			}

			free(seq);
		}
		
		else {
			free(seq);
			*looplen = *looplen - 1;
			check_loop_iterative(f, xs, seqlen, loop, looplen);
		}
	}
	
	else {
		*looplen = 0;
		free(seq);
	}
}

