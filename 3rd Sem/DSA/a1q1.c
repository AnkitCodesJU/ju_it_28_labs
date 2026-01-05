#include <stdio.h>

int main() {
    int arr[10];
    printf("Enter 10 elements:\n");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }
    int n = 10;   
    for (int i = 2; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--; 
 
    printf("The 5th element of the new array is: %d\n", arr[4]);

    return 0;
}

