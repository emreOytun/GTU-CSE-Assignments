#include <stdio.h>

typedef struct {
	char str_num[50];
	int num; 
}number_t;


typedef struct {
	number_t n;
	number_t r;
	
	double com;
	
}combination_t;

void clear_buffer(void) {
	char ch;
	do {
		ch = getchar();
	}while(ch != '\n');
}

/* Go till the end of string if not add 1. */
int str_len(char *str) {
	if (str[0] == '\0') return 0;
	else {
		return 1 + str_len(str+1);
	}
}

/* Go till the end of the string if a character is not a digit return 0. */
int is_number(char *str, int len) {
	if (str[0] == '\0' || len == 0) return 1;
	else {
		if ('0'<=str[0] && str[0]<='9') return is_number(str+1, len-1);
		else return 0;
	}
}

/* Take the power of num. */
int my_pow(int num, int e) {
	int i;
	
	int r = 1;
	for(i=0; i<e; i++) {
		r *= num;
	}
	
	return r;
}

/* Convert str to int by multipliying the current digit by the pow of 10 in len-1. */
int parse_to_int(char *str, int len) {
	if (str[0] == '\0' || len == 0) return 0;
	else return (str[0]-'0')*my_pow(10, len-1) + parse_to_int(str+1, len-1);
}

int factorial(int n) {
	if (n==1 || n==0) return 1;
	else return n * factorial(n-1);
}

/* Get the combination of n in k. */
double comb (int n, int k) {
	int n_fac = factorial(n);
	int k_fac = factorial(k);

	int dif_fac = factorial(n-k);
	
	double com = n_fac / (k_fac * dif_fac);
	
	return com;
}

/* Convert a given decimal_num to the given base. */
int base_converter(int decimal_num, int base) {
	if (decimal_num == 0) return 0;
	else return decimal_num % base + 10 * base_converter(decimal_num / base,  base);
}


int main () {

	combination_t result;

	/* Get inputs till the inputs are true. */
	int is_done = 0;
	do {
		printf("n : ");
		scanf("%s", result.n.str_num);
		
		
		printf("r : ");
		scanf("%s", result.r.str_num);
		
		
		if (is_number(result.n.str_num, str_len(result.n.str_num)) && is_number(result.r.str_num, str_len(result.r.str_num)) ) {
			result.n.num = parse_to_int(result.n.str_num, str_len(result.n.str_num));
			result.r.num = parse_to_int(result.r.str_num, str_len(result.r.str_num));
			
			result.com = comb(result.n.num , result.r.num);
			printf("Comb = %lf\n", result.com);
		
			is_done = 1;
		}
		
		else printf("You entered a wrong input !\n"); 
	
		clear_buffer();
	}while(!is_done);
	
	
	int num, base;
	printf("Decimal number: ");
	scanf("%d", &num);
	
	printf("Base: ");
	scanf("%d", &base);
	
	printf("%d in base %d is : %d\n", num, base, base_converter(num, base));
	


	return 0;
}
