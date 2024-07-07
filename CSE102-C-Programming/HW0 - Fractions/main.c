#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A fractional number: 13/7 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    
    /*
     TODO: Complete this code to read two fractional numbers and print their 
             multiplication and division results...
    */

    printf("Please enter the numerator of first number : ");
    scanf("%d", &num1);
    
    /* Since denominator can not be 0. We should check it while reading. */
    do{
   	printf("Please enter the denominator of second number : ");
    	scanf("%d", &den1); 
    	if(den1 == 0) printf("------ Denominator can not be 0. ------\n");   	
    }while(den1 == 0);
    
    printf("Please enter the numerator of first number : ");
    scanf("%d", &num2);
    
    do{
    	printf("Please enter the denominator of second number : ");
    	scanf("%d", &den2);    
    	if(den2 == 0) printf("------ Denominator can not be 0. ------\n");
    }while(den2 == 0);
    
    printf("First number you entered : ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number you entered : ");
    fraction_print(num2, den2);
    printf("\n");
    
    printf("Addition of numbers you entered : ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction of numbers you entered : ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    
    printf("Multiplication of numbers you entered : ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division of numbers you entered : ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");    
    
    return(0);
}
