#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
#include "arv_bin.h"

int main(void) {
    char s[100] = "1*2-3/(4-5)\0";

    Pilha* result = infixtopostfix(s);

    // while (!pilha_vazia(result)) {
    //     Node* cur = pilha_pop(result);
    //     if (cur->tipo == 1) {
    //         printf("%c ", cur->info); 
    //     } else {
    //         printf("%d ", cur->num);
    //     }
    // }

    Node* cur = pilha_pop(result);
    NoArv* arv_expressao = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv_criavazia());

    int aux = 0;

    while (!pilha_vazia(result)) {
        cur = pilha_pop(result);
        criar_arv_expressao(arv_expressao, cur, aux);
        aux = 0;
    }

    printf("print tree pos ordem: \n");
    exibir_posordem(arv_expressao);

    printf("\n");

    arv_libera(arv_expressao);

    return 1;
}

// + * 3 2 1
// arv_expressao: + * 3 2 1

/*
       +
     /   \
    /     \
   1       *
          / \
         2   3
*/
