#include <stdio.h>

typedef struct {
    int coeff;
    int exp;
} term;

typedef struct {
    term terms[100];
    int n;
} poly;

poly multiply(poly p1, poly p2) {
    poly result;
    int i, j, k;
    int coeff, exp, found;
    result.n = 0;

    for (i = 0; i < p1.n; i++) {
        for (j = 0; j < p2.n; j++) {
            coeff = p1.terms[i].coeff * p2.terms[j].coeff;
            exp   = p1.terms[i].exp   + p2.terms[j].exp;

            found = 0;
            for (k = 0; k < result.n; k++) {
                if (result.terms[k].exp == exp) {
                    result.terms[k].coeff += coeff;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                result.terms[result.n].coeff = coeff;
                result.terms[result.n].exp   = exp;
                result.n++;
            }
        }
    }

    return result;
}

void display(poly p) {
    int i;
    for (i = 0; i < p.n; i++) {
        printf("%dx^%d", p.terms[i].coeff, p.terms[i].exp);
        if (i != p.n - 1)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    poly p1, p2, prod;
    int i;

    printf("enter number of terms in first polynomial: ");
    scanf("%d", &p1.n);
    printf("enter terms as: coeff exp\n");
    for (i = 0; i < p1.n; i++)
        scanf("%d %d", &p1.terms[i].coeff, &p1.terms[i].exp);

    printf("enter number of terms in second polynomial: ");
    scanf("%d", &p2.n);
    printf("enter terms as: coeff exp\n");
    for (i = 0; i < p2.n; i++)
        scanf("%d %d", &p2.terms[i].coeff, &p2.terms[i].exp);

    prod = multiply(p1, p2);

    printf("\nfirst polynomial: ");
    display(p1);
    printf("second polynomial: ");
    display(p2);
    printf("product polynomial: ");
    display(prod);

    return 0;
}
