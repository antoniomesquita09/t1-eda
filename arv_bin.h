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

NoArv* arv_cria(Node* cur, NoArv* sae, NoArv* sad, NoArv* sap);

NoArv* arv_libera(NoArv* a);

void exibir_simetrica(NoArv* a);

void exibir_posordem(NoArv* a);

void exibir_preordem(NoArv* a);

void criar_arv_expressao(NoArv* arv, Node* cur);

int isOperatorNode(Node* cur);

NoArv* arv_criavazia(void) {
    return NULL;
}

int arv_vazia(NoArv* a) {
    return a == NULL;
}

NoArv* arv_cria(Node* cur, NoArv* sae, NoArv* sad, NoArv* sap) {
    NoArv* p = (NoArv*) malloc(sizeof(NoArv));
    if(p == NULL) exit(1);
    p->info = cur;
    p->esq = sae;
    p->dir = sad;
    p->pai = sap;
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

int isOperatorNode(Node* cur) {
    return cur->tipo == 1;
}

void criar_arv_expressao(NoArv* arv, Node* cur) {
    if (arv == NULL) return;

    if (!arv->dir) {
        NoArv* arv_dir = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv);
        arv->dir = arv_dir;
        return;
    }

    if (isOperatorNode(arv->dir->info)) {
        return criar_arv_expressao(arv->dir, cur);
    }

    if (!arv->esq) {
        NoArv* arv_esq = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv);
        arv->esq = arv_esq;
        return;
    }

    if (isOperatorNode(arv->esq->info)) {
        return criar_arv_expressao(arv->esq, cur);
    }

    return criar_arv_expressao(arv->pai->esq, cur);
}
