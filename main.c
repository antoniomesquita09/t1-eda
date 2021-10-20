#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
#include "arv_bin.h"

int main(void) {
    char s[100] = "1+2*3\0";

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

    while (!pilha_vazia(result)) {
        cur = pilha_pop(result);
        criar_arv_expressao(arv_expressao, cur);
    }

    printf("print tree simetrica: \n");

    exibir_simetrica(arv_expressao);

    printf("\n");
    printf("raiz: %c \n", arv_expressao->info->info);
    printf("raiz > dir: %c \n", arv_expressao->dir->info->info);
    printf("raiz > esq: %d \n", arv_expressao->esq->info->num);
    printf("raiz > dir > esq: %d \n", arv_expressao->dir->esq->info->num);
    printf("raiz > dir > dir: %d \n", arv_expressao->dir->dir->info->num);

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
