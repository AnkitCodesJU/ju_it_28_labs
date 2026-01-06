#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, c;
    int *a, *one;
    int i, j, idx;

    printf("Enter rows and cols: ");
    scanf("%d %d", &r, &c);

    /* Use malloc to simulate 2D array in 1D memory for C89 compliance */
    a = (int *)malloc(r * c * sizeof(int));
    one = (int *)malloc(r * c * sizeof(int));
    
    if (a == NULL || one == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter elements of %d x %d matrix:\n", r, c);
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            /* Manual 2D indexing: a[i*c + j] */
            scanf("%d", &a[i * c + j]);
            /* Row-major mapping */
            one[i * c + j] = a[i * c + j];
        }
    }

    printf("\nOne dimensional array (row-major mapping):\n");
    for (i = 0; i < r * c; i++) {
        printf("%d ", one[i]);
    }
    printf("\n");

    /* Demonstrate accessing using 2D indices */
    printf("\nAccess using 2D indices (formula: i * c + j):\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            idx = i * c + j; /* Formula */
            printf("2d[%d][%d] = %d at 1d[%d]\n", i, j, one[idx], idx);
        }
    }
    
    free(a);
    free(one);

    return 0;
}

