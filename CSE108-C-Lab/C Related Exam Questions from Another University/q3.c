#include <stdio.h>
#include <stdlib.h>

int countNumWords(char* arr) {
    if (arr == NULL || arr[0] == '\0') return 0;
    int inWord = 0;
    
    int count = 0;
    int i = 0;
    while (arr[i] != '\0') {
        if (arr[i] == ' ') {
            inWord = 0;
        }
        else {
            if (inWord == 0) {
                ++count;
            }
            inWord = 1;
        }
        ++i;
    }
    return count;
}

int main() {

    printf("%d \n", countNumWords("hello world"));
    printf("%d \n", countNumWords(" hello world"));
    printf("%d \n", countNumWords("  "));
    printf("%d \n", countNumWords("  system programming "));
    printf("%d \n", countNumWords("old school is so cool "));
    printf("%d \n", countNumWords("Java the coffee!"));
    printf("%d \n", countNumWords("     H   a y ı           r     "));

    return 0;
}