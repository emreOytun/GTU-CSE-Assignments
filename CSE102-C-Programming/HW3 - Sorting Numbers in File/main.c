#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Part 1 and Part 2 Functions : */
int sum(int n1, int n2, int flag);
int multi(int n1, int n2, int flag);
int isprime(int a);

/* File Operation Functions : */
void print_file(void);
void write_file(int num);
void write_result(int result);
int length_result(void);
void copy_temp_to_result(void);

/* Functions related to sorting function : */
int frequency_at_sorted_file(int num);
int is_number_unsorted(int num, int frequency_at_sorted_list);
void sort_file(void);	

void clear_buffer(void);

int main () {

	int choice;
	printf("Select Operation :\n");
	printf("1. Calculate sum/multiplication between two numbers\n");
	printf("2. Calculate prime numbers\n");
	printf("3. Show number sequence in file\n");
	printf("4. Sort number sequence in file\n");
	printf("---------------------------------\n");
	
	
	/* Check if choice is entered truely. */
	int is_valid_choice;
	char ch;
	do {	
		/* Check if the reading is successful. */
		if (scanf("%d%c", &choice, &ch) == 2 && ch == '\n') {
			if (1<=choice && choice<=4) is_valid_choice = 1;
			else printf("You entered a wrong number. Enter a number between 1-4 : ");
		}
		
		else {
			is_valid_choice = 0;
			printf("You entered a wrong character. Enter a number between 1-4 : ");
			clear_buffer();
		}
		
	}while(!is_valid_choice);
	
	
	/* Part 1 Variables : */
	int operation_flag, number_type_flag;
	int num1, num2;
	
	/* Part 2 Variables : */
	int n;
	int i;
	
	int is_reading_successful;
	switch(choice) {
	
		case 1 :				
			printf("Select operation\n");
			
			/* Get operation flag. */
			do {
				is_reading_successful = 1;
				printf("Please enter '0' for sum, '1' for multiplication.\n");		
				
				/* Check if the input is appropriate so to avoid false inputs like characters. */
				if (! (scanf("%d%c", &operation_flag, &ch) == 2 && ch == '\n')) {
					printf("Error : You entered an invalid input. Please try again...\n\n");
					is_reading_successful = 0;						
					clear_buffer();
				}
		
				else if (operation_flag!=0 && operation_flag!=1) {
					printf("Error : You entered an invalid operation flag.\n\n");
					is_reading_successful = 0;
				}		
				
			}while(is_reading_successful == 0);
			
			/* Get number type. */
			do {
				is_reading_successful = 1;
				printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
				
				if (! (scanf("%d%c", &number_type_flag, &ch) == 2 && ch == '\n') ) {
					printf("Error : You entered an invalid input. Please try again...\n\n");
					is_reading_successful = 0;
					clear_buffer();
				}
				
				else if (number_type_flag!=0 && number_type_flag!=1) {
					printf("Error : You entered an invalid number type flag.\n\n");
					is_reading_successful = 0;
				}
					
			}while(is_reading_successful == 0);
			
			/* Get numbers correctly such that result can be found. */	
			do {				
				printf("Please enter two different number:\n");
				
				/* Get number 1. */
				do {
					is_reading_successful = 1;
					printf("Number 1: ");
				
					if (! (scanf("%d%c", &num1, &ch) == 2 && ch == '\n') ) {
						printf("Error : You entered an invalid input. Please try again...\n\n");
						is_reading_successful = 0;				
						clear_buffer();
					}
					
					else if (num1 < 0) {
						printf("Error : Numbers can not be negative. Please try again...\n\n");
						is_reading_successful = 0;
					}
					
				}while(is_reading_successful == 0);
					
				/* Get number 2. */
				do {
					is_reading_successful = 1;
					printf("Number 2: ");
					
					if (! (scanf("%d%c", &num2, &ch) == 2 && ch == '\n') ) {
						printf("Error : You entered an invalid input. Please try again...\n\n");	
						is_reading_successful = 0;			
						clear_buffer();	
					}
					
					else if (num2 < 0) {
						printf("Error : Numbers can not be negative. Please try again...\n\n");
						is_reading_successful = 0;
					}
					
				}while(is_reading_successful == 0);
					
				/* Check if the numbers are appropriate for operations. */
				
				if (num1 > num2) {
					printf("Warning : Number 1 should not be bigger than Number 2. They are rearranged automatically by the program.\n\n");
					
					int temp = num1;
					num1 = num2;
					num2 = temp;
				}
				
				else if (num1 == num2) {
					is_reading_successful = 0;
					printf("Error : Number 1 and Number 2 can not be the same.\n\n");
				}
				
				
				/* If there are not any numbers between num1 and num2, then get numbers again. */
				if (is_reading_successful == 1 && num2 == num1 + 1) {
					printf("Error : There are not any numbers between %d and %d.\n\n", num1, num2);
					is_reading_successful = 0;
				}
				
				/* If there is just 1 number between N1 and N2, then check if result can be found */
				else if (is_reading_successful == 1 && num2 == num1 + 2) {
					/* 
						If numbers are even and user wants to work on even numbers
						while there is just 1 number between them, then print an error message, so do the same for odd numbers.
					*/
					   
					if (number_type_flag == 0 && num1%2 == 0) {
						printf("Error : There are not any even numbers between %d and %d.\n\n", num1, num2);
						is_reading_successful = 0;
					}
					
					else if (number_type_flag == 1 && num1%2 == 1) {
						printf("Error : There are not any odd numbers between %d and %d.\n\n", num1, num2);
						is_reading_successful = 0;
					}  
				}
				
			}while(is_reading_successful == 0);
			
			int result;
			switch(operation_flag) {
					
				case 0 :
					result = sum(num1, num2, number_type_flag);
					write_result(result);
					printf("The result is written to the results.txt file.\n");
					break;
			
				case 1 :
					result = multi(num1, num2, number_type_flag);
					write_result(result);
					printf("The result is written to the results.txt file.\n");
			}
			break;
	
		case 2 :
			
			/* Get N. */
			do {
				is_reading_successful = 1;
				printf("Please enter an integer: ");
				
				if (! (scanf("%d%c", &n, &ch) == 2 && ch == '\n') ) {
					printf("Error : You entered an invalid input. Please try again...\n\n");
					is_reading_successful = 0;
					clear_buffer();
				} 
				
				else {
					/* Since program will check numbers from 2 to N, N can not be smaller or equal than 2. */
					if (n <= 2) {
						printf("Error : You entered a number which is smaller or equal than 2.\n"); 
						is_reading_successful = 0;
					}
				}
			
			}while(is_reading_successful == 0);
			
			for(i=2; i<n; i++) {
				int is_prime = isprime(i);
			
				if (is_prime == 1) {
					printf("%d is a prime number.\n", i);
				}
			
				else {
					printf("%d is not a prime number, it is divisible by %d.\n", i, is_prime);	
				}
			}	
			break;
		
		case 3 :
			printf("Result :\n");
			print_file();
			break;
	
		case 4 :
			sort_file();
			printf("Sorting is complete.\n");
			printf("Result :\n");
			print_file();
	}
		
	return 0;
}

void clear_buffer(void) {
	char ch;
	while (ch = getchar() != '\n');
}

int sum(int n1, int n2, int flag) {
	int sum = 0;
	int i;
	
	int result_is_found;
	printf("Result\n");
	
	switch(flag) {
		
		/* For each case, iterate starting from the next number(n1+1) upto n2. */
		case 0 :
			for(i=n1+1; i<n2; i++) {
			
				/* Check if number is even. */
				if (i%2 == 0) {
					printf("%d + ", i);
					sum += i;
				}	
			}
			
			printf("\b\b \b= %d\n", sum);
			break;
		
		case 1 :
			for(i=n1+1; i<n2; i++) {
			
				/* Check if number is odd */
				if (i%2 != 0) {
					printf("%d + ", i);
					sum += i;
				}
			}
			
			printf("\b\b \b= %d\n", sum);
	}
	
	return sum;
}

int multi(int n1, int n2, int flag) {
	int product = 1;
	int i;
	printf("Result\n");
	
	switch(flag) {
	
		/* For each case, iterate starting from the next number(n1+1) upto n2. */
		case 0 :
			for(i=n1+1; i<n2; i++) {
				if (i%2 == 0) {
					printf("%d * ", i);
					product *= i;
				}
			}
			printf("\b\b \b= %d\n", product);
			break;

		case 1 :
			for(i=n1+1; i<n2; i++) {
				if (i%2 != 0) {
					printf("%d * ", i);
					product *= i;
				}
			}
			printf("\b\b \b= %d\n", product);
	}
	return product;
}

/* Return 1 if number is prime, or the least divisior. */
int isprime(int a) {
	int i;
	int is_prime = 1;
	double square_root_a = sqrt((double)a);
	
	/* Iterate from 2 to square root of a. If the number a is divisible by a number, then stop iterating */ 
	for(i=2; i<=square_root_a && is_prime==1; i++) {
		if (a%i == 0) {
			is_prime = i;
		}
	}
	return is_prime;
}

void print_file(void) {
	FILE *result_file = fopen("results.txt", "r");
	int input;
	
	/* If the file can not be opened, then print an error message. */ 
	if (result_file == NULL) printf("Error : There is not such a file called 'results.txt' yet.\n");
	
	else {
		while (!feof(result_file)) {
			fscanf(result_file, "%d ", &input);
			printf("%d ", input);	
		}
		printf("\n");
		fclose(result_file);	
	}
}

void write_file(int num) {
	FILE *file = fopen("temp.txt", "a");
	fprintf(file, "%d ", num);
	fclose(file);
}

/* Function to write numbers into the "results.txt" file. */
void write_result(int result) {
	FILE *file = fopen("results.txt", "a");
	fprintf(file, "%d ", result);
	fclose(file); 
}

/* Find the length of the numbers at "results.txt" file. */
int length_result(void) {
	FILE *file = fopen("results.txt", "r");
	
	int length = 0;
	int num;	
	
	if (file != NULL) {
		while(!feof(file)) {
			fscanf(file, "%d ", &num);
			length++;	
		}
		fclose(file);
	}
	
	/* Return -1 meaning there is not such a file. */
	else {
		length = -1;
	}

	return length;
}

/* Copy the numbers from "temp.txt" to the "results.txt". */
void copy_temp_to_result(void) {

	FILE *result_file = fopen("results.txt", "w");
	FILE *temp_file = fopen("temp.txt", "r");
	
	int input;
	while(!feof(temp_file)) {
		fscanf(temp_file, "%d ", &input);
		fprintf(result_file, "%d ", input);
	}
	
	fclose(result_file);
	fclose(temp_file);
	
}

/* Find how many times a number occurs at "temp.txt". */	
int frequency_at_sorted_file(int num) {
	int frequency = 0;
	FILE *file = fopen("temp.txt", "r");

	int value;
	
	/* If there is not such a file called "temp.txt", then it is not occured before. It'll return 0 for this case. */
	if (file != NULL) {
		while(!feof(file)) {
			fscanf(file, "%d ", &value);
			
			/* If the given number is matched with the number taken from temp.txt then increment frequency */
			if (value == num) {
				frequency++;
			}
		}
		
		fclose(file);
	}
	
	return frequency;
}

/* Determine if there is a remained unsorted duplicates of a given number */
int is_number_unsorted(int num, int frequency_at_sorted_list) {
	/* Keep the number of how many times the given number occurs at "results.txt". */
	int frequency_at_all_list = 0;
	int is_unsorted;
	
	FILE *file = fopen("results.txt", "r");
	
	int value;
	/* Find how many times the given number occurs at "results.txt". */
	if (file != NULL) {
		while(!feof(file)) {
			fscanf(file, "%d ", &value);	
			
			/* If the given number is matched with the number taken from "results.txt", then increment frequency_at_all_list. */
			if (value == num) {
				frequency_at_all_list++;
			}
		}
		
		fclose(file);
	}
	
	/* Comparare frequeny_at_all_list and frequency_at_sorted_list values of a number to determine if there is a remained unsorted duplicates of that number. */
	if (frequency_at_all_list > frequency_at_sorted_list) {
		is_unsorted = 1;
	}
	
	else {
		is_unsorted = 0;
	}

	return is_unsorted;
}

void sort_file(void) {
	/* Get the length of numbers at "results.txt". */
	int unsorted_numbers_length = length_result();
	
	/* If length function returns -1 then it means there is not such a file, therefore there is no need to sort numbers. */
		
	if (unsorted_numbers_length != -1) {
	
		/* Keep sorting until there is no unsorted number. */
		while(unsorted_numbers_length != 0) {
			FILE *result_file = fopen("results.txt", "r");
			int min1, min2, min3;
			int frequency_at_sorted_list , is_unsorted;
			int input;
			
			int initialized_numbers = 0;
			int initialization_limit;
			
			/************* INITIALIZE either just min1; or min1 and min2; or min1, min2, min3 all by using initialization limit. ******************/
			
			/* If there is 1 number left, just initialize min1. If there are 2 numbers, initialize only min1 and min2. Or initialize all of them min1, min2, min3.  */
			if (unsorted_numbers_length == 1) initialization_limit = 1;
			else if (unsorted_numbers_length == 2) initialization_limit = 2;
			else initialization_limit = 3;
			
			while(!feof(result_file) && initialized_numbers != initialization_limit) {
			
				fscanf(result_file, "%d ", &input);
				/* Get how many times the number read from "results.txt" occurs at "temp.txt" from the function. */
				frequency_at_sorted_list = frequency_at_sorted_file(input);
				
				/* If there are not any initialized numbers, then initialize min1 first */
				if (initialized_numbers == 0) {
					/* Check if there is an unsorted duplicate of the number which has just been read, before initialization. */
					is_unsorted = is_number_unsorted(input, frequency_at_sorted_list);
					if (is_unsorted == 1) {
						min1 = input;
						initialized_numbers++;
					}
				}
				
				/* If only min1 has been initialized, then initialize min2. */
				else if (initialized_numbers == 1) {
					/* If min1 has just initialized with the number read now, then increment frequency_at_sorted_list. */
					if (input == min1) frequency_at_sorted_list++;
					
					is_unsorted = is_number_unsorted(input, frequency_at_sorted_list);
					if (is_unsorted == 1) {
						if (input < min1) {
							min2 = min1;
							min1 = input;
							initialized_numbers++;
						}
						
						else {
							min2 = input;
							initialized_numbers++;
						}
					}
				
				}
				
				/* If min1 and min2 initialized, then initialize min3 */
				else if (initialized_numbers == 2) {
					/* If min or min2 have just initialized with the number read now, then increment frequency_at_sorted_list. */
					if(input == min1) frequency_at_sorted_list++;
					if(input == min2) frequency_at_sorted_list++;
					
					is_unsorted = is_number_unsorted(input, frequency_at_sorted_list);
					if (is_unsorted == 1) {
						if (input < min1) {
							min3 = min2;
							min2 = min1;
							min1 = input;
							initialized_numbers++;
						}
						
						else if (input < min2) {
							min3 = min2;
							min2 = input;
							initialized_numbers++;
						}
						
						else {
							min3 = input;
							initialized_numbers++;
						}	
					}
				}
			}
						
			/****************** Required min values have been initialized. ********************************/
		
		
			/******************* Iterate toward the end of the file, and find min values. ********************/
			
			/* If there is just 1 number left, then just find min1. */
			if (unsorted_numbers_length == 1) {
				while (!feof(result_file)) {
					
					fscanf(result_file, "%d ", &input);
					
					if (input < min1) {
						frequency_at_sorted_list = frequency_at_sorted_file(input);
						
						is_unsorted = is_number_unsorted(input, frequency_at_sorted_list);
						if (is_unsorted == 1) min1 = input;
					}	
				}
				
				write_file(min1);
				unsorted_numbers_length -= 1;
			}
			
			/* If there are only 2 numbers left, then just find min1 and min2. */
			else if (unsorted_numbers_length == 2) {
				while(!feof(result_file)) {
				
					fscanf(result_file, "%d ", &input);
					
					if (input < min2) {
						
						frequency_at_sorted_list = frequency_at_sorted_file(input);
						if (input == min1) frequency_at_sorted_list++;
												
						is_unsorted = is_number_unsorted(input, frequency_at_sorted_list);
						
						if (is_unsorted == 1) {
							if (input < min1) {
								min2 = min1;
								min1 = input;
							}
							else min2 = input;
						}		
					}				
				}
				
				write_file(min1);
				write_file(min2);
				unsorted_numbers_length -= 2;
			}
			
			/* If there are more than 2 numbers, then find min1, min2 and min3 */
			else {
				while(!feof(result_file)) {
				
					fscanf(result_file, "%d ", &input);
					
					if (input < min3) {
					
						frequency_at_sorted_list = frequency_at_sorted_file(input);
						/* If the number read now is matched with the numbers with min1 or min2, then increment frequency_at_sorted_list */
						if (input == min1) frequency_at_sorted_list++;
						if (input == min2) frequency_at_sorted_list++;
					
						is_unsorted = is_number_unsorted(input, frequency_at_sorted_list);	
					
						if (is_unsorted == 1) {
							/* If number is smaller than min1, then update min1. Consequently, update min2 and min3. */
							if (input < min1) {
								min3 = min2;
								min2 = min1;
								min1 = input;
							}
							/* If number is not smaller than min1, but smaller than min2; then update min2. */
							else if (input < min2) {
								min3 = min2;
								min2 = input;
							}
							/* If number is only smaller than min3, then update min3. */
							else min3 = input;
						}
					}
				}
					
				write_file(min1);
				write_file(min2);
				write_file(min3);
				unsorted_numbers_length -= 3;
			}
			
			fclose(result_file);
		}		
		copy_temp_to_result();
	}
}

