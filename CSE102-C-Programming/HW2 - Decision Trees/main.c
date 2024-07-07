#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/* Functions for printing the actual results of decision trees 1 and 3 to avoid code repeating. */
void problem1_result_printer(char result) {
    switch (result) {
    	case 's' :
    		printf("Setosa\n");
    		break;
    	case 'c' :
    		printf("Versicolor\n");
    		break;
    	case 'g' :
    		printf("Virginica\n");
    }
}

void problem3_result_printer(int result) {
	switch (result) {
		case 1 :
			printf("Ultra low resistancy\n");
			break;
		case 2 :
			printf("Very low resistancy\n");
			break;
		case 3 :
			printf("Low resistancy\n");
			break;
		case 4 :
			printf("Medium resistancy\n");
			break;
		case 5 :
			printf("High resistancy\n");
			break;
		case 6 :
			printf("Very high resistancy\n");
			break;
		case 7 :
			printf("Ultra high resistancy\n");
	}

}

int main() {

    /* Ask for the problem selection (1,2,3) .....  */

    /* Get the input from the user for the first problem, i.e., to test dt1a and dt1b */
    /* Compare performances and print results */

    /* Get the input from the user for the second problem, i.e., to test dt2a and dt2b */
    /* Compare performances and print results */

    /* Get the input from the user for the third problem, i.e., to test dt3a and dt3b */
    /* Compare performances and print results */
    
    int choice;
    int isValid;
    
    /* Do-while loop for getting the problem input right. */
    do{
    	isValid = 0;
    	printf("Please select the problem(1,2,3) : ");
    	scanf("%d", &choice);
    	
    	if(choice == 1 || choice == 2 || choice == 3) isValid = 1;
    	if(isValid == 0) printf("You entered an invalid number. Try again...\n");
    
    }while(!isValid);
    
    /* Problem 1 variables */
    double pl, pw, sl, sw;
    char result1a, result1b;
      	
    double x1, x2, x3;	/* for real numbers in problems 2 and 3 */
    int b1, b2; 	/* for binary values in problems 2 and 3 */
    double result2a, result2b, difference; /* Problem 2 variables */
    
    /* Problem 3 variables */
    int sensitivity;
    char quality; 
    int result3a, result3b;
    
    switch (choice) {
    	case 1 :
    		printf("Please enter PL (real number) : ");
    		scanf("%lf", &pl);
    		
    		printf("Please enter PW (real number) : ");
    		scanf("%lf", &pw);
    		
    		printf("Please enter SL (real number) : ");
    		scanf("%lf", &sl);
    		
    		printf("Please enter SW (real number) : ");
    		scanf("%lf", &sw);
    		
    		result1a = dt1a(pl, pw, sl, sw);
    		result1b = dt1b(pl, pw, sl, sw);
    		
    		/* If results are the same, then print that result. Print both of them otherwise.*/
    		if (result1a == result1b) {
    			printf("Result = ");
    			problem1_result_printer(result1a);
     		}
     		else {
     			printf("Result 1a = ");
    			problem1_result_printer(result1a);
    			
    			printf("Result 1b = ");
    			problem1_result_printer(result1b);
     		}
    		break;
    		
    	case 2 :
    		printf("Enter x1 (real number) : ");
    		scanf("%lf", &x1);
    		
    		printf("Enter x2 (real number) : ");
    		scanf("%lf", &x2);
    		
    		printf("Enter x3 (real number) : ");
    		scanf("%lf", &x3);
    		
    		/* Get and validate binary numbers. */
    		isValid = 0;
    		do {
 			
    			printf("Enter x4 (binary value -> 0 or 1): ");
    			scanf("%d", &b1);
    			
    			printf("Enter x5 (binary value -> 0 or 1): ");
    			scanf("%d", &b2);
    			
    			if ((b1 == 0 || b1 == 1) && (b2 == 0 || b2 == 1)) {
    				isValid = 1;
    			}
    			else {
    				printf("You entered an invalid binary number. Please enter 0 or 1\n");
    			}
    			
 		}while(!isValid);
   			
  		result2a = dt2a(x1, x2, x3, b1, b2);
    		result2b = dt2b(x1, x2, x3, b1, b2);
   	
   		/* If |difference of results| <= CLOSE_ENOUGH, print the average result. Print both of them otherwise. */
   		difference = result2a - result2b;
   		
  		if (-CLOSE_ENOUGH <= difference && difference <= CLOSE_ENOUGH) {
  			double avg = (result2a + result2b) / 2;
  			printf("Result = %.2f\n", avg);
 		}
    		else {
    			printf("Result 2a = %.2f\n", result2a);
    			printf("Result 2b = %.2f\n", result2b);
    		}
    		break;
    			
    	case 3 :
    		printf("Enter breaking rate (real number) : ");
    		scanf("%lf", &x1);
    		
    		printf("Enter corrosion rate (real number) : ");
    		scanf("%lf", &x2);
    		
    		/* Get and validate binary number. */
    		isValid = 0;
    		do {
 		
    			printf("Enter 1 (new-brand) or 0 (old-type) : ");
    			scanf("%d", &b1);
    			
    			if (b1 == 0 || b1 == 1) {
    				isValid = 1;
    			}
    			else {
    				printf("You entered an invalid number. Please enter 0 or 1\n");
    			}
    			
 		}while(!isValid);   		
    		
    		/* Get and validate sensitivity degree. */
    		isValid = 0;
    		do {
    		
    			printf("Enter sensitivity (numbers from 1 to 10) : ");
    			scanf("%d", &sensitivity);
    			if (1<=sensitivity && sensitivity<=10) {
    				isValid = 1;
    			}
    			else {
    				printf("You entered an invalid number. Please enter a number from 1 to 10\n");
    			}
    			
    		}while(!isValid);
    		
    		/* Get and validate quality degree. */
    		isValid = 0;
    		do {
    		
    			printf("Enter quality (letters from a to f) : ");
    			scanf(" %c", &quality);
    			if ('a'<=quality && quality<='f') {
    				isValid = 1;
    			}
    			else {
    				printf("You entered an invalid character. Please enter a character from a to f(lower case)\n");
    			}
    			
    		}while(!isValid);
    		
    		result3a = dt3a(x1, x2, b1, sensitivity, quality);
    		result3b = dt3b(x1, x2, b1, sensitivity, quality);
    		
    		if (result3a == result3b) {
    			printf("Result = ");
    			problem3_result_printer(result3a);
    		}
    		else {
    			printf("Result 3a = ");
    			problem3_result_printer(result3a);
    			
    			printf("Result 3b = ");
    			problem3_result_printer(result3b);
    			
    		}
    }

    return 0;
}
