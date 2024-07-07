#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = d1*n2; 	
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    int dividend, divider, remainder;
    int absVal_n, absVal_d;
    
    /* If either n=0 or d=0, GCD can not be found. Therefore, program must check it first. */
    /* Numbers could be negative, therefore we must find GCD by means of their absolute values. */
    if(*n != 0 && *d != 0) {
    	if(*n < 0) absVal_n = *n * -1;
    	else absVal_n = *n;
    	
    	if(*d < 0) absVal_d = *d * -1;
    	else absVal_d = *d;
    	
    	/* We need to find big and small ones of the absolute values to determine which one will be dividend and divider.  */
    	if(absVal_n <= absVal_d) {	
    	    dividend = absVal_d;
    	    divider = absVal_n;
    	}
    	else if(absVal_d < absVal_n) {
    	    dividend = absVal_n;
    	    divider = absVal_d;
    	}
    	
   	remainder = dividend % divider;
   	while(remainder != 0) {
   	    dividend = divider;
   	    divider = remainder;
   	    remainder = dividend % divider;
   	}
   	
    	*n = *n / divider;
    	*d = *d / divider;
    }
} /* end fraction_div */
