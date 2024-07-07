#include <stdio.h>
#include <stdlib.h>

int** getDissimlarityMatrix(int* arr, int size) {
    if (size <= 0) return NULL;
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        matrix[i] = (int*)malloc(i+1);
        for (int j = i; j >= 0; --j) {
            matrix[i][j] = (arr[i] - arr[j]) * (arr[i] - arr[j]);
        }
    }
    return matrix;
}

int main() {

    int arr[] = {10,3,7,8};
    int** matrix = getDissimlarityMatrix(arr, 4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    
    int arr2[] = {2,7};
    int** matrix2 = getDissimlarityMatrix(arr2, 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    return 0;
}