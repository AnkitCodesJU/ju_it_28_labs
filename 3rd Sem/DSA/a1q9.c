#include <stdio.h>

int main() {
    int r, c;
    printf("Enter rows and cols: ");
    scanf("%d %d", &r, &c);

    int a[r][c], one[r * c];

    printf("Enter elements of %d x %d matrix:\n", r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
            // Row-major mapping
            one[i * c + j] = a[i][j];
        }
    }

    printf("\nOne dimensional array (row-major mapping):\n");
    for (int i = 0; i < r * c; i++) {
        printf("%d ", one[i]);
    }
    printf("\n");

    // Demonstrate accessing using 2D indices
    printf("\nAccess using 2D indices (formula: i * c + j):\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int idx = i * c + j; // Formula
            printf("2d[%d][%d] = %d at 1d[%d]\n", i, j, one[idx], idx);
        }
    }

    return 0;
}

