#include <stdio.h>

typedef struct {
    int coeff;
    int exp;
} Term;

typedef struct {
    Term terms[50];  
    int n;          
} Poly;


void readPoly(Poly *p) {
    int i;
    printf("Enter number of terms: ");
    scanf("%d", &p->n);
    printf("Enter terms (coeff exponent) in descending order of exponents:\n");
    for (i = 0; i < p->n; i++) {
        scanf("%d %d", &p->terms[i].coeff, &p->terms[i].exp);
    }
}


void printPoly(const Poly *p) {
    int i;
    for (i = 0; i < p->n; i++) {
        printf("%dx^%d", p->terms[i].coeff, p->terms[i].exp);
        if (i != p->n - 1) printf(" + ");
    }
    printf("\n");
}


Poly addPoly(const Poly *p1, const Poly *p2) {
    Poly result;
    int i = 0, j = 0;
    int sumCoeff;
    result.n = 0;

    while (i < p1->n && j < p2->n) {
        if (p1->terms[i].exp == p2->terms[j].exp) {
            sumCoeff = p1->terms[i].coeff + p2->terms[j].coeff;
            if (sumCoeff != 0) {
                result.terms[result.n].coeff = sumCoeff;
                result.terms[result.n].exp = p1->terms[i].exp;
                result.n++;
            }
            i++; j++;
        } else if (p1->terms[i].exp > p2->terms[j].exp) {
            result.terms[result.n++] = p1->terms[i++];
        } else {
            result.terms[result.n++] = p2->terms[j++];
        }
    }

    while (i < p1->n) result.terms[result.n++] = p1->terms[i++];
    while (j < p2->n) result.terms[result.n++] = p2->terms[j++];

    return result;
}

int main() {
    Poly p1, p2, sum;

    printf("Enter first polynomial:\n");
    readPoly(&p1);

    printf("Enter second polynomial:\n");
    readPoly(&p2);

    sum = addPoly(&p1, &p2);

    printf("\nPolynomial 1: ");
    printPoly(&p1);
    printf("Polynomial 2: ");
    printPoly(&p2);
    printf("Sum: ");
    printPoly(&sum);

    return 0;
}
