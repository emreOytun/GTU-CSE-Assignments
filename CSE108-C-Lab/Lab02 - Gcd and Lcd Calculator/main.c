#include <stdio.h>
#include <math.h>


int write_file(int num) {
	FILE *file = fopen("result.txt", "a");
	if (file != NULL) {
		fprintf(file, "%d ", num);
		printf("The result is written to the results.txt file\n");
	}
	else {
		printf("There is a problem in writing the result\n");
	}	
	
	fclose(file);
	return 0;
}

int gcd_calculator(int num1, int num2) {
	int i;
	int result;
	int smaller, bigger;
	
	/* GCD can not be calculated if one of the numbers are 0 or negative. */
	if(num1<=0 || num2<=0) {
		result -1;
		return -1;
	}
	
	else if(num1<=num2) {
		smaller = num1;
		bigger = num2;
	}
	
	else if(num2<=num1) {
		smaller = num2;
		bigger = num1;
	}
	

	int is_found = 0;
	
	for(i=smaller; is_found != 1 && smaller >= 1; i--) {
		if (bigger % i == 0 && smaller % i == 0) {
			result = i;
			is_found = 1;
		}
	}
	
	return result;
}


int lcm_calculator(int num1, int num2) {
	int gcd = gcd_calculator(num1, num2);
	int lcm;
	
	if (gcd != -1) {
		lcm = num1*num2 / gcd;
	}
	
	else {
		lcm = -1;
	}
	
	return lcm;

}

double calculate_mean(void) {
	double mean;
	double sum = 0; 
	double n = 0;
	int num;
	
	FILE *file = fopen("result.txt", "r");
	
	while(!feof(file)) {
		
		fscanf(file, "%d ", &num);
		sum += num;
		n++;
	}

	mean = sum / n;
	
	fclose(file);
	return mean;
	
}

double standart_deviation_calculator() {
	double standart_deviation;
	double mean = calculate_mean();
	
	int length = 0;
	double total = 0;
	int num;
	
	FILE *file = fopen("result.txt", "r");

	
	
	int i = 1;




	while(!feof(file)) {
		
		fscanf(file, "%d ", &num);
		printf("%d. number: %d\n",i, num);
		
		total += (double) (num - mean) * (num-mean);
		
		length++;
		i++;	
	}


	
	standart_deviation = sqrt(total / length);

	
	printf("Mean: %.2lf\nTotal Count :%d\n", mean, length);
	fclose(file);
	return standart_deviation;

}

int main () {


	int choice;
		
	printf("Enter the calculator type\n");
	printf("1. GCD Calculator\n");
	printf("2. LCM Calculator via GCD\n");
	printf("3. Standart Deviation Calculator\n");
	printf("-----------------------------------\n");
	scanf("%d", &choice);

	
	int num1,num2;
	int result;
	
	double std;
	switch(choice) {
	
		case 1 :
			printf("Please enter two different number\n");
			
			printf("Number 1: ");
			scanf("%d", &num1);
			
			printf("Number 2: ");
			scanf("%d", &num2);
			
			result = gcd_calculator(num1, num2);
			printf("GCD of these two numbers: %d\n", result);
			write_file(result);
			break;
		
		case 2 :
			printf("Please enter two different number\n");
			
			printf("Number 1: ");
			scanf("%d", &num1);
		
			printf("Number 2: ");
			scanf("%d", &num2);
			
			result = lcm_calculator(num1, num2);
			printf("LCM of these two numbers: %d\n", result);
			write_file(result);
			break;
		
		case 3 :
			std = standart_deviation_calculator();
			printf("Standart Deviation: %.2lf\n", std);;
			break;
	}







	return 0;
}
