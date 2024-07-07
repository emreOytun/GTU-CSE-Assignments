#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int validate_password(char password[]) {
	
	/* Check if the password is valid : -All of characters must be digit. -It must have 4 character. */
	int password_length = 0;
	
	for(int i = 0; password[i] != '\0'; i++) {	
		if(!('0'<=password[i] && password[i]<='9')) {
			return 0;
		}
		password_length++;
	}
	
	if(password_length != 4) {
		return 0;
	}
	
	return 1;
}

int main() {

	/*********** PART 1 : *************/
	
	int num1;
	int num2;
	int divisor;
	int f_i;
	
	char ordinal_numbers[10][3] = {"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"};
	
	printf("Enter the first integer: ");
	scanf("%d", &num1);
	
	printf("Enter the second integer: ");
	scanf("%d", &num2);
	
	printf("Enter the divisor: ");
	scanf("%d", &divisor);
	
	f_i = find_divisible(num1, num2, divisor);
	if(f_i == -1) {
		printf("There is not any integer between %d and %d can be divided by %d\n", num1, num2, divisor);
	}
	else {
		int n;
		printf("The first integer between %d and %d divided by %d is %d\n", num1, num2, divisor, f_i);
		printf("Enter the number how many next: ");
		scanf("%d", &n);
		
		int nth_divisible = find_nth_divisible(n, f_i, divisor);
		if(nth_divisible == -1) {
			printf("No possible to find %d%s divisible between %d and %d divided by %d\n", n+1, ordinal_numbers[n+1], num1, num2, divisor);
		}
		/* Check if nth_divisible is out of the range. */
		else if(nth_divisible >= num2) {
			printf("No possible to find %d%s divisible between %d and %d divided by %d\n", n+1, ordinal_numbers[n+1], num1, num2, divisor);
		}
		else{
			printf("The %d%s integer between %d and %d divided by %d is %d\n", n+1, ordinal_numbers[n+1], num1, num2, divisor, nth_divisible);
		}
	}
	
	/*********** PART 2: *************/
	
	printf("\n");
	int is_validated;
	
	do{
		is_validated = 1;
		char identity_number[15];
		char password[10];
		
		printf("Enter your identity number: ");
		scanf("%s", identity_number);
	
		printf("Enter the password you want to create: ");
		scanf("%s", password);
		
		/* Check if the password is valid. */
		if(validate_password(password) == 0) {
			is_validated = 0;
		}
		
		/* If the password is valid, then check if identity_number is valid. */
		else if(validate_identity_number(identity_number) == 0) {
			is_validated = 0;
		}
		
		if(is_validated == 0) {
			printf("Invalid identity number or password\n");
		}
		else {
			if(create_customer(identity_number, atoi(password)));	
		}
	
	}while(!is_validated);
	
	/*********** PART 3 : *************/
	
	printf("\n");
	char identity_number[15];
	int password;
	
	printf("Enter your identity number: ");
	scanf("%s", identity_number);
	
	printf("Enter your password: ");
	scanf("%d", &password);
	
	if(check_login(identity_number, password) == 0) {
		printf("Invalid identity number or password\n");
	}
	else {
		float cash_amount;
		printf("Login Successful\n");
		
		printf("Enter your withdraw amount: ");
		scanf("%f", &cash_amount);
		
		int withdrawable_Amount = withdrawable_amount(cash_amount);
		printf("Withdrawable amount is: %d\n", withdrawable_Amount);
	}
		
	
	
	return 0;	
}

