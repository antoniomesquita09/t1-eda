#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#include "arv_bin.h"
#include "Calcula_ArvExp.h"


int main(void) {
    char s[100];
    printf("Digite a expressao que quer calcular\n");
    scanf("%[^\n]", s);
	float t;
    Pilha* result = infixtopostfix(s);

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

	printf("\n\n Expressao Original: \n");
	exibir_simetrica(arv_expressao);
    printf("\n\n Expressao em pos ordem: \n");
    exibir_posordem(arv_expressao);
	printf("\n \n");
	
	printf("\n Arvore com representacao aninhada \n");
	print_simetrica(arv_expressao);
	printf("\n \n");
    t = arv_valorEA(arv_expressao);
    int floattoint = (int) t;
    arv_libera(arv_expressao);
	printf("\n Resultado da expressao %d \n", floattoint);
    return 1;
}
