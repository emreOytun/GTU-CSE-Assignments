#include <stdio.h>
#include <string.h>
#define WORD_SIZE 100

/*
Function : swap
-------------------
It does : It swaps the given two strings.

Return : It modifies two strings. 

*/


void swap(char *str1, char *str2) {
	char temp[WORD_SIZE];
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

/*
Function : concatAlphabeticReverseSort
-------------------
It does : 1) It sorts the given string array in reverse order.
		2) Then, it turns the string array into 1D array.
		
Return :	It returns the concat string in catStr.

*/

void concatAlphabeticReverseSort(char str[][WORD_SIZE], int n, char catStr[]) {
	int i, j;
	int min_i;
	
	for(i=0; i<n-1; i++) {
		for(j=i+1, min_i=i; j<n; j++) {
			if( strcmp(str[min_i], str[j])<0 ) min_i = j;
		}
		swap(str[i], str[min_i]);
	}
	
	printf("Sorted Array : \n");
	for(i=0; i<n; i++) {
		printf("%d: %s\n", i, str[i]);
	}
	
	for(i=0; i<n; i++) {
		strcat(catStr, str[i]);
	}
}

/*
Function : generateTagParser
-------------------
It does : -> It modifies the given array 
		1) If array is less than 5 char, then it adds <<>> at the head and tail of the arr.
		2) If array is bigger than 5 char and less than 5 char, then it adds <<>> at the head and tail of the arr.
		3) If array is bigger than 10 char, then it adds * *.
		
Return :	It returns the modified string in temp arr.

*/

void generateTagParser(char temp[], char arr[]) {
	int len = strlen(arr);
	
	int i, j;
	if (len < 5) {
		temp[0] = '<';
		temp[1] = '<';
		j = 2;
		
		for(i=1; i<len-1; i++) {
			temp[j] = arr[i];
			j++;
		}
		
		temp[j] = '>';
		temp[j+1] = '>';
		temp[j+2] = '\0';
		
	}
	
	else if (5<=len && len<=10) {
		temp[0] = '*';
		j = 1;
		
		for(i=1; i<len-1; i++) {
			temp[j] = arr[i];
			j++;
		}
		
		temp[j] = '*';
		temp[j+1] = '\0';
		
	}
	
	else {
		temp[0] = '/';
		temp[1] = '+';
		j = 2;
		
		for(i=1; i<len-1; i++) {
			temp[j] = arr[i];
			j++;
		}
		
		temp[j] = '+';
		temp[j+1] = '/';	
	}
}


int main () {

	char catStr[WORD_SIZE] = {};
	char str[20][WORD_SIZE];
	int n = 0;
	
	char temp[WORD_SIZE];
	char arr[WORD_SIZE];
	
	
	
	int choice;
	do {
		printf("\n");
		printf("1 -> Part 1\n");
		printf("2 -> Part 2\n");
		printf("0 -> Exit\n");
		printf("Choice = ");
		scanf("%d", &choice);
		
		switch(choice) {
			
			case 1 :
				printf("enter the count of how many strings you will enter...\n");
				scanf("%d", &n);
	
				int i;
				printf("Enter the strings : \n");
				
				for(i=0; i<n; i++) {
					scanf("%s", str[i]);
				}
				
				printf("Given array is : \n");
				for(i=0; i<n; i++) {
					printf("%d: %s\n", i, str[i]);
				}
				printf("\n");
						
				concatAlphabeticReverseSort(str, n, catStr); 	
			
				printf("\nResult is : \n");
				printf("%s\n", catStr);
			
				break;	
		
			case 2:
				
				printf("\nEnter a string:\n");
				scanf("%s", arr);
	
				generateTagParser(temp, arr);
				printf("%s\n",temp);
			
				break;	
	
		}
	
	}while(choice != 0);
	
	
	return 0;	
}

