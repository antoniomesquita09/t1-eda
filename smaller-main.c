#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

int main(void) {
    char s[100] = "1+2-3*4\0";
    Fila* queue = infixtopostfix(s);

    printf("Postfix:\n");

    while (queue->n > 0) {
        Node* cur = fila_retira(queue);
        if (cur->tipo == 0) {
            printf("%d ", cur->num);
            continue;
        }
        printf("%c ", cur->info);
    }
    printf("\n");
    return 1;
}
