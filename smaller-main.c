#include <stdio.h>
#include <stdlib.h>
#include "tad.h"



int main(void) {
    char s[100] = "1+2-3*4\0";
    Pilha* result = infixtopostfix(s);

    printf("Postfix:\n");

    while (!pilha_vazia(result)) {
        Node* cur = pilha_pop(result);
        if (cur->tipo == 0) {
            printf("%d ", cur->num);
            continue;
        }
        printf("%c ", cur->info);
    }

    printf("\n");
    return 1;
}
