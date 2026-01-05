#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c, v;
} term;

typedef struct {
    int rows, cols, n;
    term *data;
} sparse;

void reads(sparse *s) {
    printf("enter rows cols non-zeros: ");
    scanf("%d%d%d", &s->rows, &s->cols, &s->n);
    s->data = malloc(s->n * sizeof(term));
    if (!s->data) { printf("memory error\n"); exit(1); }

    printf("enter row col val (1-based):\n");
    for (int i = 0; i < s->n; i++) {
        int r, c, v;
        scanf("%d%d%d", &r, &c, &v);
        if (r > 0 && r <= s->rows && c > 0 && c <= s->cols) {
            s->data[i].r = r - 1;
            s->data[i].c = c - 1;
            s->data[i].v = v;
        } else {
            printf("invalid row/col, re-enter:\n");
            i--;
        }
    }
}

void count(sparse s) {
    int *cnt = calloc(s.rows, sizeof(int));
    if (!cnt) { printf("memory error\n"); return; }

    for (int i = 0; i < s.n; i++)
        cnt[s.data[i].r]++;

    printf("\nnon-zeros per row:\n");
    for (int i = 0; i < s.rows; i++)
        printf("row %d: %d\n", i + 1, cnt[i]);

    free(cnt);
}

int main() {
    sparse s;
    reads(&s);
    count(s);
    free(s.data);
    return 0;
}
