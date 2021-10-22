#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
#include "arv_bin.h"
#include "Calcula_ArvExp.h"


int main(void) {
    char s[100] = "((18 + 3 *2) / 8 + 5 * 3) / 6\0";
	float t;
    Pilha* result = infixtopostfix(s);
	/* Caso queira testar os elementos da pilha
    while (!pilha_vazia(result)) {
        Node* cur = pilha_pop(result);
        if (cur->tipo == 1) {
            printf("%c ", cur->info); 
        } 
		else {
             printf("%d ", cur->num);
        }
    }
	*/
    Node* cur = pilha_pop(result);
    NoArv* arv_expressao = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv_criavazia());

    int aux = 0;
	int i = 0;
	int j = 0;
    while (!pilha_vazia(result)) {
        cur = pilha_pop(result);
        j = criar_arv_expressao(arv_expressao, cur, aux, i);
        aux = 0;
    }
    print_t(arv_expressao);
    
	printf("\n Imprimir arvore: \n");
	arv_imprime (arv_expressao);
	printf("\n\n Expressao Original: \n");
	exibir_simetrica(arv_expressao);
    printf("\n\n Expressao em pos ordem: \n");
    exibir_posordem(arv_expressao);
	printf("\n \n");
    t = arv_valorEA(arv_expressao);
    int floattoint = (int) t;
    arv_libera(arv_expressao);
	printf("\n Resultado da expressao %d \n", floattoint);
    return 1;
}
