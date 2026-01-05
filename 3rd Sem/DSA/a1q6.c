#include <stdio.h>

#define max 1000

typedef struct {
    int digits[max];  // store digits
    int n;            // number of digits
} bignum;

// function to read a big number
void read_bignum(bignum *num) {
    printf("enter number of digits: ");
    scanf("%d", &num->n);
    printf("enter the digits one by one (most significant first):\n");
    for (int i = 0; i < num->n; i++) {
        scanf("%d", &num->digits[i]);
    }
}

// function to add two big numbers
void add_bignum(bignum *a, bignum *b, bignum *res) {
    int i = a->n - 1;
    int j = b->n - 1;
    int carry = 0;
    int temp[max];
    int k = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int d1 = (i >= 0) ? a->digits[i] : 0;
        int d2 = (j >= 0) ? b->digits[j] : 0;
        int sum = d1 + d2 + carry;

        temp[k++] = sum % 10;
        carry = sum / 10;

        i--;
        j--;
    }

    res->n = k;
    for (int m = 0; m < k; m++) {
        res->digits[m] = temp[k - m - 1];
    }
}


void display_bignum(bignum *num) {
    for (int i = 0; i < num->n; i++) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

int main() {
    bignum num1, num2, sum;

    printf("enter first number:\n");
    read_bignum(&num1);

    printf("enter second number:\n");
    read_bignum(&num2);

    add_bignum(&num1, &num2, &sum);

    printf("sum = ");
    display_bignum(&sum);

    return 0;
}

