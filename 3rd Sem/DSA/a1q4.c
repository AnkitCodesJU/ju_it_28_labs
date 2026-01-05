
#include <stdio.h>
#include <math.h>

// Define a term of polynomial: coeff * x^exp
typedef struct {
    int coeff;
    int exp;
} Term;

// Define a sparse polynomial (collection of terms)
typedef struct {
    Term terms[50];   // assuming max 50 terms
    int n;           
} Poly;

// Function to evaluate polynomial at x
int evaluate(Poly p, int x) {
    int result = 0;
    for (int i = 0; i < p.n; i++) {
        result += p.terms[i].coeff * (int)pow(x, p.terms[i].exp);
    }
    return result;
}

int main() {
    Poly p;
    int x;

    printf("Enter number of terms in polynomial: ");
    scanf("%d", &p.n);

    printf("Enter terms as: coefficient exponent\n");
    for (int i = 0; i < p.n; i++) {
        scanf("%d %d", &p.terms[i].coeff, &p.terms[i].exp);
    }

    printf("Enter value of x: ");
    scanf("%d", &x);

    int result = evaluate(p, x);
    printf("Value of polynomial at x = %d is: %d\n", x, result);

    return 0;
}


