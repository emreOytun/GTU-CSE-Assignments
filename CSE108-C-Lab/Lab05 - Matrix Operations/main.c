#include <stdio.h>


void create_matrix(int matrix[][3]) {
	int i, j;
	int num;
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			printf("Please enter %d.row %d.column : ", i+1, j+1);
			scanf("%d", &num);
			matrix[i][j] = num;
		}
	}
}

void print_matrix(int matrix[][3]) {
	int i, j;
	int num;
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			printf("%-3d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* Sum diagonal numbers of matrix. */
int trace(int matrix[][3]) {
	int trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
	return trace;
}

/* In every iteration, keep column stable and change the row. Put numbers to the transpoze arr. */
void transpose(int matrix[][3], int transpoze[3][3]) {
	int i, j;
	
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			transpoze[i][j] = matrix[j][i];
		}
	}	
}

/* For every row in matrix1, iterate as much as matrix2's column num. 
   In every iteration, get one value. 	
*/
void multiplication(int matrix1[][3], int matrix2[][3]) {
	int i, j, k;
	int sum;
	int multip[3][3];
	
	for (i=0; i<3; i++) {
		for (k=0; k<3; k++) {
			sum = 0;
			for (j=0; j<3; j++) {
				sum += matrix1[i][j] * matrix2[j][k];
			}
			multip[i][k] = sum;
		}	
	}

	printf("Multiplication of matrix:\n");
	print_matrix(multip);
}

void create_1d_arr(int arr[]) {
	int i;
	int num;
	for(i=0; i<10; i++) {
		printf("Enter a num : ");
		scanf("%d", &num);
		arr[i] = num;
	}
}

void print_1d_arr(int arr[]) {
	int i;
	int num;
	for(i=0; i<10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/* Iterate till the end of the arr, in each iteration slide the window of 3 numbers. */
void filter(int arr[]) {
	int kernel[3] = {-1, 1, -1};
	int i, j;
	int r[8];
	
	for(i=0; i<8; i++) {
		int sum = 0;
		
		for(j=0; j<3; j++) {
			sum += arr[i+j] * kernel[j];
		}
		r[i] = sum;
	}
	
	printf("Convolutional Filter Result:\n");
	for(i=0; i<8; i++) {
		printf("%d ", r[i]);
	}
	printf("\n");

}

int main () {

	int matrix1[3][3];
	int matrix2[3][3];
	
	int arr[10];	
	int choice;
	
	int t;
	int transpose_arr[3][3];
	
	/* Before menu, first get the matrix values. */
	printf("Enter 1.st matrix values:\n");
	create_matrix(matrix1);
	printf("Enter 2.nd matrix values:\n");
	create_matrix(matrix2);
	
	printf("1.st Matrix:\n");
	print_matrix(matrix1);
	printf("2.nd Matrix\n");
	print_matrix(matrix2);	
	
	
	do {	
		printf("-------------------------\n");
		printf("1. Convolutional Filter for 1D array\n");
		printf("2. Multiplication\n");
		printf("3. Trace\n");
		printf("4. Transpose\n");
		printf("5. Exit\n");
		printf("-------------------------\n");
		printf("Enter your choice:");
		scanf("%d", &choice);
				
		switch(choice) {
			
			case 1 :
				create_1d_arr(arr);
				filter(arr);
				break;
			
			case 2 :			
				multiplication(matrix1, matrix2);
				break;
				
			case 3 :
				t = trace(matrix1);
				printf("Trace of matrix1 is : %d\n", t);
				
				t = trace(matrix2);
				printf("Trace of matrix2 is : %d\n", t);
				break;
				
			case 4 :
				
				transpose(matrix1, transpose_arr);
				printf("Transpose of the first matrix:\n");
				print_matrix(transpose_arr);
				
				transpose(matrix2, transpose_arr);
				printf("Transpose of the first matrix:\n");
				print_matrix(transpose_arr);
				break;
				
			case 5 :
				printf("Goodbye!...\n");
		}
		
	}while(choice != 5);
	

	return 0;
}
