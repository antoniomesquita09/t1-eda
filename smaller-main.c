#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
#include "arv_bin.h"

int main(void) {
    char s[100] = "1+2*3\0";

    Pilha* result = infixtopostfix(s);

    NoArv* arv_expressao = arv_criavazia();

    // while (!pilha_vazia(result)) {
    //     Node* cur = pilha_pop(result);
    //     if (cur->tipo == 1) {
    //         printf("%c ", cur->info); 
    //     } else {
    //         printf("%d ", cur->num);
    //     }
    // }

    Node* cur = pilha_pop(result);
    arv_expressao = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv_criavazia());

    while (!pilha_vazia(result)) {
        cur = pilha_pop(result);
        criar_arv_expressao(arv_expressao, cur);
    }

    printf("print tree: \n");

    exibir_posordem(arv_expressao);

    arv_libera(arv_expressao);

    return 1;
}
