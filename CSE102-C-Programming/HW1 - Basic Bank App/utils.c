#include <stdio.h>
#include <stdlib.h>

/*********** PART 1 : *************/

int find_divisible(int x, int y, int z) {
	int f_i;
	int is_found = 0;
	
	/* Divisior(z) can not be 0, so check it first. */
	if(z == 0) {
		return -1;
	}
	
	/* Check if there is a number between x and y which is divisible by z. */
	for(int i = x+1; i<y; i++) {
		if(i % z == 0) {
			f_i = i;
			is_found = 1;
			break;
		}
	}
	if(is_found == 0) {
		return -1;
	}
	else {
		return f_i;
	}
}

int find_nth_divisible(int n, int f_i, int z) {
	/* If n is negative, then nth_divisible can not be found. */
	if(n < 0) {
		return -1;
	}
	
	/* If divisor(z) is negative, then we need to take its absolute value to find Nth divisible. */
	if(z < 0) {
		z = z*-1; 
	}
	
	/* Since f_i is divisible by z, we can add n*z and f_i to find the next Nth number after f_i. */
	int nth_divisible = f_i + n*z;
	return nth_divisible;
}

/*********** PART 2 : *************/

int validate_identity_number(char identity_number[]) {
	int length = 0;
	int sum_all = 0;
	int sum_odd = 0;
	int sum_even = 0;
	
	if(identity_number[0] == '0') {
		return 0;
	}
	
	/* Count characters till the end of identity_number array. */
	for(int i = 0; identity_number[i] != '\0'; i++) {
		/* If a character is not a digit then return 0.*/
		if( !('0'<=identity_number[i] && identity_number[i]<='9') ) {
			return 0;
		}
		
		/* We need to find even and odd sums till the 9th digit. */
		/* If index(i) % 2 = 0, then it's an odd numbered digit. */
		if(i < 9) {
			/* The reason to subract '0' character from the characters is to get the character as integer.*/	
			if(i%2 == 0) sum_odd += (identity_number[i] - '0');
			else sum_even += (identity_number[i] - '0');
		}
		
		sum_all += (identity_number[i] - '0');
		length++;
	}
	
	if(length != 11) {
		return 0;
	}
	
	/* If we subtract the last number from the sum of all digits, then we get sum of first 10 digits.*/
	int sum_first_10_digit = sum_all - (identity_number[10] - '0'); 
	if( (sum_first_10_digit % 10) != (identity_number[10] - '0') ) {
		return 0;
	}
	
	if( ((sum_odd*7) - sum_even) % 10 != (identity_number[9] - '0') ) {
		return 0;
	} 
	
	return 1;
}

int create_customer(char identity_number [ ], int password) {
	FILE *customerFile = fopen("customeraccount.txt", "w");
	if(customerFile == 0) {
		return 0;
	}
	
	fprintf(customerFile, "%s,%d", identity_number, password);
	fclose(customerFile);
	return 1;
}

/*********** PART 3 : *************/

int check_login(char identity_number [ ], int password) {
	FILE *customerFile = fopen("customeraccount.txt", "r");
	if(customerFile == 0) {
		fclose(customerFile);
		return 0;
	}
	
	char actual_identity_num[12];
	int actual_password;
	fscanf(customerFile, "%[^,],%d", actual_identity_num, &actual_password);
	
	/* Compare the password. */
	if(actual_password != password) {
		fclose(customerFile);
		return 0;
	}
	
	/* Compare the identity numbers. */
	int identity_number_length = 0;
	
	/* Check character by character whether they're equal until end of strings, and meanwhile count the length. */
	int i = 0;
	while(actual_identity_num[i] != '\0' && identity_number[i] != '\0') {
		if(actual_identity_num[i] != identity_number[i]) {
			fclose(customerFile);
			return 0;
		}
		identity_number_length++;
		i++;
	}
	
	if(identity_number_length != 11) {
		fclose(customerFile);
		return 0;
	}
	
	return 1;	
}

int withdrawable_amount(float cash_amount) {
	int withdrawable_amount = 0;
	int decimal_amount = (int) cash_amount;
	
	/* Find how much money can be withdrawn by using 50s. */
	withdrawable_amount += ((decimal_amount / 50) * 50);
	decimal_amount = decimal_amount % 50;
	
	/* Find how much money can be withdrawn by using 20s. */
	withdrawable_amount += ((decimal_amount / 20) * 20);
	decimal_amount = decimal_amount % 20;
	
	/* Find how much money can be withdrawn by using 10s. */
	withdrawable_amount += ((decimal_amount / 10) * 10);
	
	return withdrawable_amount;
}
