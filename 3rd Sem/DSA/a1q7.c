#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int row, col, val;
} term;

typedef struct {
    int m, n, num;
    term data[MAX];
} sparse;

void reads(sparse *s) {
    int i;
    printf("enter rows, cols, non-zero elements: ");
    scanf("%d%d%d", &s->m, &s->n, &s->num);

    printf("enter row, col, val for each non-zero element:\n");
    for (i = 0; i < s->num; i++) {
        scanf("%d%d%d", &s->data[i].row, &s->data[i].col, &s->data[i].val);
    }
}

void prints(sparse *s) {
    int i;
    printf("\nrow col val\n");
    for (i = 0; i < s->num; i++) {
        printf("%d   %d   %d\n", s->data[i].row, s->data[i].col, s->data[i].val);
    }
}

void printfull(sparse *s) {
    int k = 0;
    int i, j;
    printf("\nfull matrix form:\n");
    for (i = 0; i < s->m; i++) {
        for (j = 0; j < s->n; j++) {
            if (k < s->num && s->data[k].row == i && s->data[k].col == j) {
                printf("%d ", s->data[k].val);
                k++;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void add(sparse *a, sparse *b) {
    sparse c;
    int i = 0, j = 0;
    
    if (a->m != b->m || a->n != b->n) {
        printf("\ncannot add matrices of different dimensions\n");
        return;
    }

    c.m = a->m;
    c.n = a->n;
    c.num = 0;

    while (i < a->num && j < b->num) {
        if (a->data[i].row < b->data[j].row ||
           (a->data[i].row == b->data[j].row && a->data[i].col < b->data[j].col)) {
            c.data[c.num++] = a->data[i++];
        } else if (a->data[i].row > b->data[j].row ||
                  (a->data[i].row == b->data[j].row && a->data[i].col > b->data[j].col)) {
            c.data[c.num++] = b->data[j++];
        } else {
            c.data[c.num] = a->data[i];
            c.data[c.num++].val = a->data[i++].val + b->data[j++].val;
        }
    }
    while (i < a->num) c.data[c.num++] = a->data[i++];
    while (j < b->num) c.data[c.num++] = b->data[j++];

    printf("\nresult (sparse form):");
    prints(&c);

    printfull(&c);
}

int main() {
    sparse a, b;

    printf("enter matrix A\n");
    reads(&a);

    printf("enter matrix B\n");
    reads(&b);

    printf("\nmatrix A (sparse):");
    prints(&a);
    printfull(&a);

    printf("\nmatrix B (sparse):");
    prints(&b);
    printfull(&b);

    add(&a, &b);

    return 0;
}
