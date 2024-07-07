#include <stdio.h>


void reverse(char str[], char reversed[], int n) {
	if (n == 0) return;
	reverse(str+1, reversed, n-1);
	reversed[n-1] = str[0];
	reversed[n] = '\0';
}

/* Function = merge 
   Algorithm = Sort and merge two subarrays.	

*/

void merge(int arr[], int p, int q, int r) {
	
	int n1 = q - p + 1;
	int n2 = r - q;
	
	int L[n1], M[n2];
	
	for(int i = 0; i<n1; i++) {
		L[i]  = arr[p+i];
	}
	for(int j = 0; j<n2; j++) {
		M[j] = arr[q+1+j];
	}
	
	int i=0, j=0, k=p;
	
	while(i<n1 && j<n2) {
		if (L[i] <= M[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = M[j];
			j++;
		}
		k++;
	}

	while(i<n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	
	while(j<n2) {
		arr[k] = M[j];
		j++;
		k++;
	}

}

/* Function : mergeSort
   Algorithm : Divide and Conquer
   -> Divide the arr into subsets then merge subsets.

*/
void mergeSort(int arr[], int l, int r) {
	int mid = l + (r-l) / 2;
	if (l >= r) return; 
		
	mergeSort(arr, l, mid);
	mergeSort(arr, mid+1, r);
	merge(arr, l, mid, r);	
}

int main () {

	char str[]  = "abcd";
	char reversed[10];
	reverse(str, reversed, 4);	
	printf("%s\n", reversed);
	
	int arr[6] = {6, 5, 12, 10, 9, 1};
	mergeSort(arr, 0, 5);
	for(int i=0; i<6; i++) {
		printf("%d ", arr[i]);
	}



	return 0;
}
