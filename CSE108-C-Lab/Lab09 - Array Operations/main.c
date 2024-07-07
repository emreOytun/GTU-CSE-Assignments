#include <stdio.h>
#include <string.h>

int findMax(int n1, int n2, int n3, int n4) {
	if (n1>n2 && n1>n3 && n1>n4) return n1;
	if (n2>n1 && n2>n3 && n2>n4) return n2;
	if (n3>n1 && n3>n2 && n3>n4) return n3;
	if (n4>n1 && n4>n2 && n4>n3) return n4;
}

int findMin(int n1, int n2, int n3, int n4) {
	if (n1<n2 && n1<n3 && n1<n4) return n1;
	if (n2<n1 && n2<n3 && n2<n4) return n2;
	if (n3<n1 && n3<n2 && n3<n4) return n3;
	if (n4<n1 && n4<n2 && n4<n3) return n4;
}

int findMinOf3(int n1, int n2, int n3) {
	if (n1<n2 && n1<n3) return n1;
	if (n2<n1 && n2<n3) return n2;
	if (n3<n1 && n3<n2) return n3;
}


/*
	-> Find min and max of an integer arr.
	
	TO-DO-LIST : 
		1)If there's 1 or 2 elements in the arr return them.
		2)Divide the array in two parts(left-right), and get 4 values from these calls.
		3)Order this 4 values and return min-max.

*/
int* findMaximumDistance(int distanceOfCities[], int start, int end, int arr[]) {
	if (start == end) {
		arr[0] = distanceOfCities[start];
		arr[1] = distanceOfCities[end];
		return arr;
	}
	
	if (start+1 == end) {
		arr[0] = distanceOfCities[start];
		arr[1] = distanceOfCities[end];
		return arr;
	}
	
	int mid = start+(end-start)/2;
	int r1[2];
	findMaximumDistance(distanceOfCities, start, mid, r1);
	int r2[2];
	findMaximumDistance(distanceOfCities, mid+1, end, r2);
	
	int n1 = r1[0];
	int n2 = r1[1];
	int n3 = r2[0];
	int n4 = r2[1];
	
	int min = findMin(n1, n2, n3, n4);
	int max = findMax(n1, n2, n3, n4);
	
	arr[0] = min;
	arr[1] = max;
	
	return arr;
}

/* -> Find minimum changes to make two strings same. 

	TO-DO-LIST : 
		1) Check if str1 or str2 is empty. 
		2) Check the last character of the strings.
		3) Call the other recursive function.
*/
int recursiveMinStrDiff(char str1[], char str2[], int m, int n) {
	if (m == 0) return n;
	if (n == 0) return m;
	
	int total = 0;
	if (str1[m-1] == str2[n-1]) return recursiveMinStrDiff(str1, str2, m-1, n-1);
	
	else {
		int r1 = recursiveMinStrDiff(str1, str2, m, n-1);
		int r2 = recursiveMinStrDiff(str1, str2, m-1, n);
		int r3 = recursiveMinStrDiff(str1, str2, m-1, n-1);
		int min = findMinOf3(r1, r2, r3);
		return 1+min;
	}
}

void clear_buffer(void) {
	char ch;
	do {
		ch = getchar();
	}while(ch != '\n');
}

int main () {

	int r[2];
	int distanceOfCities[5];
	
	int i;
	
	for(i=0; i<5; i++) {
		printf("%d.distance : ", i+1);
		scanf("%d", &distanceOfCities[i]);
	}
	
	
	findMaximumDistance(distanceOfCities, 0, 4, r);
	printf("%d %d\n", r[0], r[1]);
	
	char str1[20];
	char str2[20];
	
	printf("Enter str1 : ");
	clear_buffer();	
	scanf("%s", str1);
	
	printf("Enter str2 : ");
	clear_buffer();
	scanf("%s", str2);
	
	printf("%d\n", recursiveMinStrDiff(str1, str2, strlen(str1), strlen(str2)));
	





	return 0;
}
