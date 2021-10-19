#include <stdio.h>
#include <stdlib.h>

/* TAD: arv bin */

typedef struct noArv NoArv;

struct noArv {
    Node* info;
    struct noArv* pai;
    struct noArv* esq;
    struct noArv* dir;
};

NoArv* arv_criavazia(void);

int arv_vazia(NoArv* a);

NoArv* arv_cria(Node* cur, NoArv* sae, NoArv* sad);

NoArv* arv_libera(NoArv* a);

void exibir_simetrica(NoArv* a);

void exibir_posordem(NoArv* a);

void exibir_preordem(NoArv* a);

NoArv* criar_arv_expressao(NoArv* arv, Node* cur);

NoArv* arv_criavazia(void) {
    return NULL;
}

int arv_vazia(NoArv* a) {
    return a == NULL;
}

NoArv* arv_cria(Node* cur, NoArv* sae, NoArv* sad) {
    NoArv* p = (NoArv*) malloc(sizeof(NoArv));
    if(p == NULL) exit(1);
    p->info = cur;
    p->esq = sae;
    p->dir = sad;
    return p;
}

NoArv* arv_libera(NoArv* a) {
    if (!arv_vazia(a)) {
        arv_libera(a->esq); /* libera sae */
        arv_libera(a->dir); /* libera sad */
        free(a); /* libera raiz */
    }
    return NULL;
}

void exibir_simetrica(NoArv* a) {
	if (a == NULL) return;
    exibir_simetrica(a->esq); /* mostra sae */
    if (a->info->tipo == 1) { /* mostra raiz */
        printf("%c ", a->info->info); 
    } else {
        printf("%d ", a->info->num);
    }
    exibir_simetrica(a->dir); /* mostra sad */
}

void exibir_posordem(NoArv* a) {
	if (a == NULL) return;
	exibir_posordem(a->esq); /* mostra sae */
	exibir_posordem(a->dir); /* mostra sad */
    if (a->info->tipo == 1) { /* mostra raiz */
        printf("%c ", a->info->info); 
    } else {
        printf("%d ", a->info->num);
    }
}

void exibir_preordem(NoArv* a) {
	if (a == NULL) return;
	if (a->info->tipo == 1) { /* mostra raiz */
        printf("%c ", a->info->info); 
    } else {
        printf("%d ", a->info->num);
    }
	exibir_preordem(a->esq); /* mostra sae */
	exibir_preordem(a->dir); /* mostra sad */
}

NoArv* criar_arv_expressao(NoArv* arv, Node* cur) {
    if (cur->tipo == 1) { // isOperator
        printf("%c ", cur->num);

        if (arv->dir == NULL) {
            return arv_cria(&arv, arv->esq, cur);
        }

        if (arv->esq == NULL) {
            return arv_cria(&arv, cur, arv->dir);
        }

        return criar_arv_expressao(arv->pai, cur);
    }
    // isNumber
    printf("%d ", cur->info);
    return criar_arv_expressao(arv->pai, cur);
}