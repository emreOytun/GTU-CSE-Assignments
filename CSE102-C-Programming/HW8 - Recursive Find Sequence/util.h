#ifndef _UTIL_H_
#define _UTIL_H_

#define CLOSE_ENOUGH 0.001

int get_first_digit(int num);
void generate_sequence(int xs, int currentlen, int seqlen, int *seq);
void hist_of_firstdigits(void (*f)(int xs, int currentlen, int seqlen, int *seq), int xs, int seqlen, int *h, int digit);
int has_loop(int *arr, int n, int looplen, int *ls, int *le);
void check_loop_iterative(void (*f)(int xs, int currentlen, int seqlen, int *seq), int xs, int seqlen, int *loop, int *looplen);


#endif /* _UTIL_H_ */
