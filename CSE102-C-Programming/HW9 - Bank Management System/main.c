#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

union Person {
	char name[50];
	char address[50];
	int phone;
};

union Loan {
	float amount;
	float interestRate;
	int period;
};

struct BankAccount {
	union Person Customer;
	union Loan Loans[3];
	int loan_number;
	int id;
};

void get_accounts_from_file(struct BankAccount Accounts[], int *account_num);

float calculateLoan(float amount, int period, float interestRate);

/* Functions for reading purposes. */
void clear_buffer();
int check_tail_input(void);
int check_string(char buff[]);

int is_id_used(struct BankAccount Accounts[], int account_num, int given_id);
void addCustomer(struct BankAccount Accounts[], int *account_num);
int get_customer_num(struct BankAccount Accounts[], int account_num, int given_id);

void newLoan(struct BankAccount Accounts[], int account_num);
void getReport();

void print_account(struct BankAccount *Account);
void listCustomers(struct BankAccount Accounts[], int account_num);

int main () {

	struct BankAccount Accounts[50];
	int account_num = 0;
	
	get_accounts_from_file(Accounts, &account_num);
	
	int choice;
	do {
		printf("=============================================\n");
		printf("Welcome to the Bank Management System\n");
		printf("=============================================\n");
		printf("	1. List All Customers\n");
		printf("	2. Add New Customer\n");
		printf("	3. New Loan Application\n");
		printf("	4. Report Menu\n");
		printf("	5. Exit System\n");
		
		int is_valid, k;	
		do {
			is_valid = 1;
			printf("Choice = ");
			k = scanf("%d", &choice);
						
			if (k != 1) {
				is_valid = 0;
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();
			
			if (! (is_valid && 1<=choice && choice<=5)) is_valid = 0; 
			
			if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
		}while(!is_valid);
		
		switch (choice) {
			case 1 :
				listCustomers(Accounts, account_num);
				break;
			
			case 2 :
				addCustomer(Accounts, &account_num);
				break;
				
			case 3 :
				newLoan(Accounts, account_num);
				break;
		
			case 4 :
				getReport();
				break;
		
			case 5 :
				printf("Program is closing...Goodbye!\n");
				break;
		}	
	
	}while(choice != 5);

	return 0;
}

/* clear_buffer to after read string/character from consol.*/
void clear_buffer() {
	char ch;
	do {
		ch = getchar();
	}while(ch != '\n' && ch != EOF);
}


/* Check if there is a non-whitespace character after the number input. */
int check_tail_input(void) {

	int is_valid = 1;
	char ch;
	
	do {
		scanf("%c", &ch);
		if (ch != ' ' && ch != '\n' && ch != '	' && ch != EOF) is_valid = 0;
		
	}while(ch != '\n' && ch != EOF);

	return is_valid;
}

/* Print a given account in struct BankAccount type. */
void print_account(struct BankAccount *Account) {
	int loan_num = (*Account).loan_number;
	int i;
	long double total_loan = 0;
	
	printf("Customer ID = %d\n", (*Account).id);
	printf("Customer Name = %s\n", (*Account).Customer.name);
	
	printf("Loans = [");
	
	for(i=0; i<loan_num-1; i++) {
		printf("%.2f + ", (*Account).Loans[i].amount);
		total_loan += (*Account).Loans[i].amount;
	}
	
	if (loan_num != 0) {
		printf("%.2f", (*Account).Loans[loan_num-1].amount);
		total_loan += (*Account).Loans[loan_num-1].amount;
	}
	
	printf("]");
	
	printf(" => %.2Lf\n", total_loan);
} 

void listCustomers(struct BankAccount Accounts[], int account_num) {
	int i;
	
	/* If there's no customers, then print message. */
	if (account_num == 0) printf("Warning : There is no customers in the system.\n\n");
	
	else {
	
		for (i=0; i<account_num; i++) {
			printf("\n");
			print_account(&Accounts[i]);
			printf("\n");
		}
	
	}
}

/* Check if the given_id is used before. */
int is_id_used(struct BankAccount Accounts[], int account_num, int given_id) {
	int i;
	int is_used = 0;
	
	for (i = 0; i<account_num && is_used == 0; i++) {
		if (Accounts[i].id == given_id) is_used = 1;
	}
	
	return is_used;
}

void addCustomer(struct BankAccount Accounts[], int *account_num) {

	if (*account_num == 50) printf("Warning : Sorry, you cannot add a customer. The system can only have 50 customers.\n\n");
	
	else {
	
		int is_valid, k;
		char buff[200];
		
		char name[50];
		char address[50];
		int phone;
		int id;
		
		/*********** Get customer ID. ************/
		do {
			is_valid = 1;
			printf("Enter customer ID : ");
			k = scanf("%d", &id);
					
			if (k != 1) {
				is_valid = 0;
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();
			
			
			if (is_valid && id<0) {
				is_valid = 0;
				printf("Warning : ID cannot be negative.\n");
			}
			
			if (is_valid && is_id_used(Accounts, *account_num, id) == 1) {
				printf("Warning : This ID is used before. Try again with another ID.\n\n");
				is_valid = 0;
			}
			
			else if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
		}while(!is_valid);
		
		
		/********** Get customer name. ************/
		do {
			is_valid = 1;	
			
			printf("Enter customer name : ");
			scanf("%[^\n]s", buff);
			
			if (strlen(buff) > 49) {
				printf("Warning : Too long name. Enter a shorter name.\n");
				is_valid = 0;
				clear_buffer();
			}
			
		}while(!is_valid);
		
		/* Get the valid name into the name variable. */
		strcpy(name, buff);
		
			
		/****************** Get customer address. *****************/
		do {
			is_valid = 1;	
			
			printf("Enter customer address : ");
			clear_buffer();
			scanf("%[^\n]s", buff);	
			
			if (strlen(buff) > 49) {
				printf("Warning : Too long address. Enter a shorter adress.\n");
				is_valid = 0;
			}
			
		}while(!is_valid);
		
		/* Get the valid address into the address variable. */
		strcpy(address, buff);
		
		
		/*************** Get customer phone. ***************/
		do {
			is_valid = 1;
			printf("Enter customer phone : ");
			k = scanf("%d", &phone);
					
			if (k != 1) {
				is_valid = 0;
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();
			
			if (is_valid && phone<=0) {
				is_valid = 0;
				printf("Warning : Phone number should be positive.\n");
			}
			
			if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
		}while(!is_valid);
			
		/************** Add new accounts informations into the text and struct array. *****************/
		
		FILE *file = fopen("customers.txt", "a");
			
		fprintf(file, "---------------\n"); 
		fprintf(file, "ID : %d\n", id);
		fprintf(file, "Name : %s\n", name);
		fprintf(file, "Address : %s\n", address);
		fprintf(file, "Phone : %d\n", phone);
		fprintf(file, "Loan number : %d\n", 0);
		
		
		(*account_num)++;
		Accounts[*account_num-1].id = id;
		strcpy(Accounts[*account_num-1].Customer.name, name);
		
		/* Set loan number to 0 as default. */	
		Accounts[*account_num-1].loan_number = 0;
		
		printf("\nSystem : New customer has been added to the system.\n\n");	
		fclose(file);
	
	}
}

/* Search for the given_id in the Accounts[] array. Return -1 if there'is not such ID, else return the customer's number. */
int get_customer_index(struct BankAccount Accounts[], int account_num, int given_id) {

	int i;
	int is_found = 0;
	int cust_index = -1;
	
	for (i = 0; i<account_num && is_found == 0; i++) {
		if (Accounts[i].id == given_id) {
			is_found = 1;
			cust_index = i;
		}	
	}

	return cust_index;
}

void newLoan(struct BankAccount Accounts[], int account_num) {

	FILE *temp_file;
	
	int is_valid;
	int k;

	int i;
	char ch;
	int is_eof;
	int is_found;
	
	int text_id;

	int loan_number;
	int new_loan_number;
	
	float amount;
	int period;
	float interest_rate;
	float total_loan_amount;
	
	int cust_id;
	int cust_index;
	
	/* Use this struct for reading purpose. */
	struct BankAccount Account;
	
	FILE *file = fopen("customers.txt", "r+");
	if (file == NULL) printf("Warning : There is no customers in the system.\n\n");
	
	else {
	
		/* Get the customer ID for loan application. */
		do {
			is_valid = 1;
			
			printf("Enter the CUSTOMER ID you want to apply for a loan : ");		
		
			k = scanf("%d", &cust_id);
					
			if (k != 1) {
				is_valid = 0;
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();
			
			if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
		}while(!is_valid);
		
		/* Get the customer number with given customer ID. */
		cust_index = get_customer_index(Accounts, account_num, cust_id);
		
		/* If there's not such ID, print warning message. */
		if (cust_index == -1) printf("\nWarning : There is no accounts with that ID.\n\n");
		
		/* If the customer has already had 3 loans, print error message.*/
		else if (Accounts[cust_index].loan_number == 3) printf("\nWarning : Each customers can only have 3 loans.\n\n");
		
		else {
		
			temp_file = fopen("temp.txt", "w");
			
			/* Look for the given cust_id in the "customers.txt", copy "customers.txt" to "temp.txt" while reading "customers.txt". */
			for(is_found = 0, is_eof = 0; !feof(file) && !is_eof && is_found == 0;) {
				ch = fgetc(file);
				if (ch == EOF) is_eof = 1;
				
				if (!is_eof) {
				
					fscanf(file, "--------------");
					fgetc(file);
					fprintf(temp_file, "---------------\n");
				
				
					fscanf(file, "ID : %d", &text_id);
					fgetc(file);
					fprintf(temp_file, "ID : %d\n", text_id);
					
					if (text_id == cust_id) is_found = 1;
					
					
					fscanf(file, "Name : %[^\n]s", Account.Customer.name);
					fgetc(file);
					fprintf(temp_file, "Name : %s\n", Account.Customer.name);
					
					fscanf(file, "Address : %[^\n]s", Account.Customer.address);
					fgetc(file);
					fprintf(temp_file, "Address : %s\n", Account.Customer.address);
					
					
					fscanf(file, "Phone : %d", &Account.Customer.phone);
					fgetc(file);
					fprintf(temp_file, "Phone : %d\n", Account.Customer.phone);
							
					fscanf(file, "Loan number : %d", &loan_number);
					fgetc(file);
					
					if (is_found) fprintf(temp_file, "Loan number : %d\n", loan_number+1);
					else fprintf(temp_file, "Loan number : %d\n", loan_number);
			
								
					for(i=0; i<loan_number; i++) {
							
						fgetc(file);
						fscanf(file, "Loan :");
						fgetc(file);
						fprintf(temp_file, "\nLoan :\n");
								
						fscanf(file, "Amount : %f", &Account.Loans[0].amount);
						fgetc(file);
						fprintf(temp_file, "Amount : %f\n", Account.Loans[0].amount);
						
						fscanf(file, "Interest Rate : %f", &Account.Loans[0].interestRate);
						fgetc(file);
						fprintf(temp_file, "Interest Rate : %f\n", Account.Loans[0].interestRate);
						
					
						fscanf(file, "Period : %d", &Account.Loans[0].period);
						fgetc(file);
						fprintf(temp_file, "Period : %d\n", Account.Loans[0].period);
						
					}
				
				}
				
			}
			
			/* Get loan amount. */					
			do {
			
				is_valid = 1;
				printf("Enter loan amount : ");
				k = scanf("%f", &amount);						
				
				if (k != 1) {
					is_valid = 0;
					scanf("%*[^\n]");
				}
				
				if (is_valid) is_valid = check_tail_input();
				
				if (is_valid && amount<=0) {
					is_valid = 0;
					printf("Warning : Amount should be positive.\n");
				}
				
				if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
			
			}while(!is_valid);
			
			/* Get interest rate. */
			do {
				is_valid = 1;
				printf("Enter interest rate : ");
				k = scanf("%f", &interest_rate);			
								
				if (k != 1) {
					is_valid = 0;
					scanf("%*[^\n]");
				}
				
				if (is_valid) is_valid = check_tail_input();
				
				if (is_valid && interest_rate<=0) {
					is_valid = 0;
					printf("Warning : Interest rate should be positive.\n");
				}
				
				if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
			
			}while(!is_valid);
						
							
			/* Get period. */
			do {
				is_valid = 1;
				printf("Enter period : ");
				k = scanf("%d", &period);			
								
				if (k != 1) {
					is_valid = 0;
					scanf("%*[^\n]");
				}
				
				if (is_valid) is_valid = check_tail_input();
				
				if (is_valid && period<=0) {
					is_valid = 0;
					printf("Warning : Period should be positive.\n");
				}
				
				if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
			
			}while(!is_valid);
			
			/* Start to add new loan information for that customer with given ID, write new loan information to "temp.txt". */
			fprintf(temp_file, "\nLoan :\n");
			fprintf(temp_file, "Amount : %f\n", amount);
			fprintf(temp_file, "Interest Rate : %f\n", interest_rate);
			fprintf(temp_file, "Period : %d\n", period);
			
			new_loan_number = loan_number + 1;
			total_loan_amount = calculateLoan(amount, period, interest_rate);
			
			/* Update the customer in the struct array Accounts[]. */
			Accounts[cust_index].loan_number = new_loan_number;
			Accounts[cust_index].Loans[new_loan_number-1].amount = total_loan_amount;
			
			/* Copy the rest of "customers.txt" into "temp.txt". */
			do {
				char ch = getc(file);
				if (ch != EOF) putc(ch, temp_file);
			}while(!feof(file) && ch != EOF);
		
			/* remove "customers.txt" and rename "temp.txt". */
			remove("customers.txt");
			rename("temp.txt", "customers.txt");
			
			printf("\nSystem : New loan application is successful!\n\n");
		
			fclose(temp_file);
			fclose(file);
		}
	}
}

/* Read customer informations from "customers.txt" and update the struct array if there is a .txt such that. */
void get_accounts_from_file(struct BankAccount Accounts[], int *account_num) {

	FILE *file = fopen("customers.txt", "r");
	float amount;
	int period;
	float interest_rate;
	
	int text_id;
	int loan_number;
	
	float total_loan_amount;
	
	int is_eof = 0;
	int counter = 0;
	int i;
	char ch;
	
	char buff[200];
	int phone;
	
	if (file != NULL) {
		while (file != NULL && !feof(file) && !is_eof) {
	
			ch = fgetc(file);
			if (ch == EOF) is_eof = 1;
			
			if (!is_eof) {
			
				counter++;
		
				fscanf(file, "--------------");
				fgetc(file);
				
				fscanf(file, "ID : %d", &text_id);
				fgetc(file);
				
					
				/* Update id and other informations in bank accounts. */
				Accounts[counter-1].id = text_id;
					
					
				fscanf(file, "Name : %[^\n]s", Accounts[counter-1].Customer.name);
				fgetc(file);
		
				
				fscanf(file, "Address : %[^\n]s", buff);
				fgetc(file);
		
		
				fscanf(file, "Phone : %d", &phone);
				fgetc(file);
		
		
				fscanf(file, "Loan number : %d", &loan_number);
				fgetc(file);
				
				for(i=0; i<loan_number; i++) {
					fgetc(file);
					fscanf(file, "Loan :");
					fgetc(file);
					
						
					fscanf(file, "Amount : %f", &amount);
					fgetc(file);
		
						
					fscanf(file, "Interest Rate : %f", &interest_rate);
					fgetc(file);
		
						
							
					fscanf(file, "Period : %d", &period);
					fgetc(file);
	
				
					total_loan_amount = calculateLoan(amount, period, interest_rate);
					Accounts[counter-1].Loans[i].amount = total_loan_amount;
				}
				
				/* Update loan numbers in bank accounts. */
				Accounts[counter-1].loan_number = loan_number;
				
			}
		
		}
		
		fclose(file);
		printf("-------------------\nFormer customer informations have been read from file.\n------------------\n");
	}
	
	*account_num = counter;
	
}

void getReport() {

	int report_type;
	int is_valid;
	int k;
	
	int is_eof = 0;
	int counter = 0;
	int i, j;
	char ch;
	
	char name[55];
	char address[55];
	int phone;
	
	int text_id;
	int loan_id;
	int given_loan_num;
	int is_loan_id_found = 0;
	
	float amount;
	int period;
	float interest_rate;
	
	int loan_number;
	float total_loan_amount;
	float monthly_payment;
		
	
	FILE *file = fopen("customers.txt", "r");
	if (file == NULL) printf("Warning : There is no customers in the system.\n\n");
	
	else {
		
		/* Get report type. */
		do {
		
			is_valid = 1;
			printf("-----------\n");
			printf("REPORT MENU\n");
			printf("1. Customer Detail\n");
			printf("2. Loan Detail\n");
			printf("Choice = ");
			k = scanf("%d", &report_type);			
							
			if (k != 1) {
				is_valid = 0;
				scanf("%*[^\n]");
			}
			
			if (is_valid) is_valid = check_tail_input();
			
			if (is_valid) {
				if (! (report_type == 1 || report_type == 2) ) {
					is_valid = 0; 
				}
			}
			
			
			if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
		}while(!is_valid);
		
		/* If report type is a loan's detail, then get customer ID and loan number. */
		if (report_type == 2) {
			
			/************ Get customer id for loan detail. ************/
			do {
			
				is_valid = 1;
				printf("Enter customer ID : ");
				k = scanf("%d", &loan_id);			
								
				if (k != 1) {
					is_valid = 0;
					scanf("%*[^\n]");
				}
					
				if (is_valid) is_valid = check_tail_input();
					
				if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
			}while(!is_valid);
		
		
			/*********** Get loan number for loan detail. *************/
			do {
			
				is_valid = 1;
				printf("Enter loan number (1-2-3): ");
				k = scanf("%d", &given_loan_num);			
								
				if (k != 1) {
					is_valid = 0;
					scanf("%*[^\n]");
				}
					
				if (is_valid) is_valid = check_tail_input();
				
				if (is_valid) {
					if (given_loan_num != 1 && given_loan_num != 2 && given_loan_num != 3) is_valid = 0;
				}
					
				if (!is_valid) printf("Warning : You entered a wrong input. Please try again.\n");
		
			}while(!is_valid);
		
		}
		
		/********** Read "customers.txt" until the ID is found or reaching the EOF. **********/
		while (!feof(file) && !is_eof && is_loan_id_found == 0) {
		
			ch = fgetc(file);
			if (ch == EOF) is_eof = 1;
			
			if (!is_eof) {
			
				counter++;
		
				fscanf(file, "--------------");
				fgetc(file);
				
				fscanf(file, "ID : %d", &text_id);
				fgetc(file);
								
				fscanf(file, "Name : %[^\n]s", name);
				fgetc(file);
			
				fscanf(file, "Address : %[^\n]s", address);
				fgetc(file);
				
				fscanf(file, "Phone : %d", &phone);
				fgetc(file);
		
		
				fscanf(file, "Loan number : %d", &loan_number);
				fgetc(file);
				
				/* If report_type is 1, then print customer details. */
				if (report_type == 1) {
					printf("\nCustomer ID = %d\n", text_id);
					printf("Customer Name = %s\n", name);
					printf("Customer Phone = %d\n", phone);
					printf("Customer Address = %s\n", address);	
				}
				
				/* If report_type is 2, then check if the given id is found in the text. */
				if (report_type == 2 && text_id == loan_id) {
					is_loan_id_found = 1;
					
					if (loan_number == 0) printf("\nWarning : There's no loans related with that account.\n\n");
					else if (given_loan_num > loan_number) printf("\nWarning : There's only %d loans related with that account.\n\n", loan_number);
					
				}
				
				for(i=0; i<loan_number; i++) {	
				
					fgetc(file);
					fscanf(file, "Loan :");
					fgetc(file);
					
						
					fscanf(file, "Amount : %f", &amount);
					fgetc(file);
		
						
					fscanf(file, "Interest Rate : %f", &interest_rate);
					fgetc(file);
		
					fscanf(file, "Period : %d", &period);
					fgetc(file);
	
					if (report_type == 2 && is_loan_id_found && i+1 == given_loan_num) {	
						
						total_loan_amount = calculateLoan(amount, period, interest_rate);
						monthly_payment = total_loan_amount / period;
					
						printf("\nTotal Credit Value = %.4lf\n", total_loan_amount);
					
						for(j=0; j<period; j++) {
							printf("%d. Month Installment = %.4lf\n", j+1, monthly_payment);		
						}
					}
				}
				
				if (report_type == 1) printf("\n");
			}
		}
		
		if (report_type == 2) {
			if (is_loan_id_found == 0) printf("Warning : There is no customer in the system with that ID.\n\n");
		}
		
		fclose(file);
	}
	
}

float calculateLoan(float amount, int period, float interestRate) {
	float new_amount;
	float result;
	
	/* If period>0, then add the interest and amount at hand; call the next function to calculate the rest of interest and total amount. */	
	if (period > 0) {
		new_amount = amount + (amount * interestRate);
	 	result =	calculateLoan(new_amount, period-1, interestRate); 
	}
	 
	/* Else return amount at hand. */
	else result = amount;

	return result;
}

