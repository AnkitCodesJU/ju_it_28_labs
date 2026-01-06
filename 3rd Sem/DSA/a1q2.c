#include <stdio.h>

int main() {
    int n;
    int i;
    int temp;
    int arr[100]; /* Using fixed size instead of VLA for better C89 compliance, though some GCCs allow VLA. But strict ISO C90 does not support VLAs. User's Guide says 'Ancient GCC' */
    
    printf("Enter number of elements: ");
    scanf("%d", &n);

    /* Check bounds if strictly necessary, but for now assuming user behaves. */
    
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

   
    for (i = 0; i < n/2; i++) {
        temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }

    printf("Reversed list:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

