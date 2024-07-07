#include <stdio.h>


typedef enum{
	sunday, monday, tuesday, wednesday, thursday, friday, saturday
}Days;

typedef enum{
	harddisk, monitor, keyboard, mouse
}Products;

typedef enum {
	buy = 1, orders, prices, exit
}Selections;

typedef enum {
	harddisk_p = 2, monitor_p = 5, keyboard_p = 3, mouse_p = 10
}Prices;

typedef enum {
	dolar = 4, euro = 5, pound = 9, peso = 10
}Currencies;

void print_days(int day) {
	if (day == sunday) printf("Sunday");
	else if (day == monday) printf("Monday");
	else if (day == tuesday) printf("Tuesday");
	else if (day == wednesday) printf("Wednesday");
	else if (day == thursday) printf("Thursday");
	else if (day == friday) printf("Friday");
	else if (day == saturday) printf("Saturday");
}	

void readOrderFile(void(*day_print)(int day)) {
	FILE *file = fopen("orders.txt", "r");
	int counter = 0;
	int product;
	int day;
	
	if (file != NULL) {
		while (!feof(file)) {
			if (counter == 0) {
				fscanf(file, "%d ", &product);
				counter++;
			}
			
			else if (counter == 1) {
				fscanf(file, "%d ", &day);
				counter = 0;
				
				printf("Product ID: %d,", product);
				printf("Day: ");
				day_print(day);
				printf("\n");
			}	
		}	
	}
}

int sum(int a, int b) {
	return a + b;
}

int product(int a, int b) {
	return a * b;
}

void all_orders(int(*add)(int a, int b), int(*multiple)(int a, int b), void(*day_print)(int day)) {
	FILE *file = fopen("orders.txt", "r");
	int counter = 0;
	int product;
	int day;
	
	int sum = 0;
	int product_price;
	int currency;
	int product_price_tl;
	
	if (file != NULL) {
		while (!feof(file)) {
			if (counter == 0) {
				fscanf(file, "%d ", &product);
				counter++;
			}
			
			else if (counter == 1) {
				fscanf(file, "%d ", &day);
				counter = 0;
				
				printf("Product : ");
				if (product == harddisk) printf("Harddisk,");
				else if (product == monitor) printf("Monitor,");
				else if (product == keyboard) printf("Keyboard,");
				else if (product == mouse) printf("Mouse,");
				
				printf("Day: ");
				day_print(day);
				printf("\n");
				
				if (product == harddisk) {
					product_price = harddisk_p;
					currency = dolar;
					
					product_price_tl = multiple(product_price, currency);
					sum = add(sum, product_price_tl);
				}
				
				else if (product == monitor) {
					product_price = monitor_p;
					currency = euro;
					
					product_price_tl = multiple(product_price, currency);
					sum = add(sum, product_price_tl);
				}
				
				else if (product == keyboard) {
					product_price = keyboard_p;
					currency = pound;
					
					product_price_tl = multiple(product_price, currency);
					sum = add(sum, product_price_tl);
				}
				
				else if (product == mouse) {
					product_price = mouse_p;
					currency = peso;
					
					product_price_tl = multiple(product_price, currency);
					sum = add(sum, product_price_tl);
				}
			}
		}
		printf("Total prices: %d\n", sum);	
	}
} 

int main () {

	int selection;
	do {
		printf("Welcome to the TechMarket.\n");
		printf("1. Buy Product\n");
		printf("2. Orders\n");
		printf("3. All Orders Prices\n");
		printf("4. Exit\n");
		printf("----------------------\n");
		scanf("%d", &selection);
		
		if (selection == buy) {
			int product;
			int day;
			
			printf("Select your product:\n");
			printf("0. Harddisk\n");
			printf("1. Monitor\n");
			printf("2. Keyboard\n");
			printf("3. Mouse\n");
			printf("4. GO TO MAIN MENU\n");
			scanf("%d", &product);
			
			if (product != 4) {
				printf("Select your arrival day[0-6]: \n");
				printf("Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday\n");
				printf("---------------------\n");
				scanf("%d", &day);
				
				FILE *file = fopen("orders.txt", "a");
				fprintf(file, "%d %d ", product, day);  
				fclose(file);
			}
		}
		
		else if (selection == orders) {
			readOrderFile(print_days);
		}
		
		else if (selection == prices) {
			all_orders(sum, product, print_days);
		}
		
	
	}while(selection != 4);




	return 0;
}
