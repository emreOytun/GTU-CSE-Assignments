#include <stdio.h>
#include <math.h>


void x_star_display(int n) {

/* 

*   *
 * *
  *
 * *
*   *

*/

	int i, j;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if(i==j) printf("*");
			else if(j == n-i-1) printf("*");
			else printf(" ");				
		}
		printf("\n");
	}


}


void diamond_star_display(int n) {
	
	int i, j;
	int len = n/2 + 1;
	for(i=1; i<=len; i++) {
		for(j=len-1; j>=i; j--)
			printf(" ");
		
		printf("*");
		
		for(j=1; j<=2*(i-1)-1; j++) 
			printf(" ");
		
		if(i != 1)
			printf("*");
		
		printf("\n");	
	}
	
	for(i=len-1; i>=1; i--) {
		for(j=i; j<=len-1; j++)
			printf(" ");
			
		printf("*");
		
		for(j=2*(i-1)-1; j>=1; j--) 
			printf(" ");
		
		if(i !=	1)
			printf("*");
		
		printf("\n");
	}
	
}

/* For positive numbers get the length of the number. */
int length(int n) {
	int counter = 0;
	do {
		n = n / 10;
		counter++;
	}while(n != 0);
	return counter;
}

int is_palindrome_integer(int n) {
	int is_palindrome = 1;
	if (n<0) is_palindrome = 0;
	else {
		int first, last;
		int pow = 1;
		while(n != 0 && is_palindrome == 1) {
			last = n % 10;
			
			int i;
			for (i=0; i<length(n)-1; i++) {
				pow *= 10;
			}
			first = n / pow;
				
			if (first != last) is_palindrome = 0;
			
			n = n / pow;
			n = n / 10;		
		}
	}
	return is_palindrome;
}

void multiplication_table_display(int n) {
	int i, j;
	/* First line */
	printf(" ");
	printf(" ");
	printf(" ");
	printf(" ");
	for(i=1; i<=n; i++) printf("%3d ", i);
	printf("\n");
	printf("--------------------------------------\n");

	for(i=1; i<=n; i++) {
		
		printf("%3d*", i);
		printf(" ");
		printf(" ");
		
		for(j=1; j<=n; j++) {		
			printf("%-3d ", i*j);
		}
		
		printf("\n");
	}
}


int main () {
	int choice;
	int exit = 0;
	int n;
	do {
		printf("Enter option 1 to x_star_display\n");
		printf("Enter option 2 to diamond_star_display\n");
		printf("Enter option 3 to multiplication_table_display\n");
		printf("Enter option 4 to palindrome_check_number\n");
		printf("Enter option -1 to exit\n");
		scanf("%d", &choice);
	  
	  switch(choice) {	
	  
		case 1 :
			printf("Enter an odd integer as the heigth: ");
			scanf("%d", &n);
			x_star_display(n);
			printf("\n");
			break;
			
		case 2 :
			printf("Enter an odd integer as the heigth: ");			
			scanf("%d", &n);
			diamond_star_display(n);
			printf("\n");
			break;
			
		case 3 :
			printf("Enter an integer as the size: ");
			scanf("%d", &n);
			multiplication_table_display(n);
			printf("\n");
			break;
			
		case 4 :
			printf("Enter an integer as the palindrome: ");
			scanf("%d", &n);
			int is_palindrome = is_palindrome_integer(n);
			
			if (is_palindrome) printf("%d is a palindrome.\n", n);
			else printf("%d is not a palindrome.\n", n);
			printf("\n");
			break;
			
		case -1 :
			exit = 1;
	  }
	  
	}while(!exit);	
	
	return 0;
}
