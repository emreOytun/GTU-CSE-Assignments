#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *array;
	int cur_size;
}dynamic_array;

/* 1) Incerement the number of given arr, and copy the elements into new array.
   2) free arr and return new_arr.
*/
int* resize_array(int *arr, int cur_size) {
	int new_size = cur_size + 1;
	int *new_arr = (int*) calloc(new_size, sizeof(int));
	
	int i;
	for (i=0; i<cur_size; i++) {
		new_arr[i] = arr[i];
	}
	
	if (arr != NULL) free(arr);
	return new_arr;
}

void read_from_file(char *filename, dynamic_array *arr) {
	FILE *file = fopen(filename, "r");
	
	int input;
	int *new_arr;
	
	/* Read till EOF and get inputs. */
	while (!feof(file)) {
		fscanf(file, "%d ", &input);
		
		new_arr = resize_array(arr->array, arr->cur_size); // resize the array and get new_arr.
		arr->array = new_arr;
		
		arr->array[arr->cur_size] = input; // put the new input.
		arr->cur_size += 1; // increment the cur_size.
	}
	
	fclose(file);
	printf("Numbers has been read from file.\n");
}


void print_array(dynamic_array arr) {
	int i;

	
	for (i=0; i<arr.cur_size; i++) {
		printf("%d\n", arr.array[i]);
	}
}

/* Find the index of the given number in the arr. */
int find_index(dynamic_array *arr, int number) {
	int i;
	int index = -1;
	int is_found;
	
	for (i=0, is_found=0; i<arr->cur_size && is_found == 0; i++) {
		if (arr->array[i] == number) {
			index = i;
			is_found = 1;
		}
	}
	
	return index;
}

/* Shrink the given arr by using the index. */
int* shrink_array(int *arr, int currentsize, int index) {
	
	if (arr != NULL) {
		int new_size = currentsize - 1;
		int *new_arr = calloc(new_size, sizeof(int));
		
		int i;
		
		for(i=0; i<index; i++) {
			new_arr[i] = arr[i];	
		}
		
		for(i=index+1; i<currentsize; i++) {
			new_arr[i-1] = arr[i];
		}		
	
	
		free(arr);
		return new_arr;
	}
	
	else return NULL;
}

void removeData(dynamic_array *arr, int number) {
	int index = find_index(arr, number);
	int i;
	
	if (index == -1) printf("There's not such number in the list\n");
	
	else {
	
		int *new_arr = shrink_array(arr->array, arr->cur_size, index);
		arr->array = new_arr;
		arr->cur_size -= 1;
		
		printf("Deletion is successful.\n");
	}
}



int main () {

	dynamic_array arr;
	arr.array = NULL;
	arr.cur_size = 0;
	
	read_from_file("data.txt", &arr);
	
	printf("\nData in source file : \n");
	print_array(arr);
	
	int number;
	printf("Enter the number you want to be deleted : ");
	scanf("%d", &number);
	
	removeData(&arr, number);
	printf("\nArray after deletion : \n***********************\n");
	print_array(arr);
	

	return 0;
}
