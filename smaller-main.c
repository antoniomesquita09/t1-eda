#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
#include "arv_bin.h"

int main(void) {
    char s[100] = "1+2-3*4\0";

    Pilha* result = infixtopostfix(s);

    NoArv* arv_expressao = arv_criavazia();

    while (!pilha_vazia(result)) {
        Node* cur = pilha_pop(result);
        criar_arv_expressao(arv_expressao, cur);
    }

    printf("print tree: \n");

    exibir_posordem(arv_expressao);

    arv_libera(arv_expressao);

    return 1;
}
