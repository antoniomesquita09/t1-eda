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

int criar_arv_expressao(NoArv* arv, Node* cur, int height, int i);

int isOperatorNode(Node* cur);

int _print_t(NoArv* tree, int is_esq, int offset, int depth, char s[20][255]);

void print_t(NoArv* tree);

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

void arv_imprime (NoArv* a)
{
	if (!arv_vazia(a))
	{
		if(a->info->tipo == 0)
			printf("%d ",a->info->num); /* mostra raiz */
		if(a->info->tipo == 1)
			printf("%c ",a->info->info); /* mostra raiz */
		arv_imprime(a->dir); /* mostra sad */
		arv_imprime(a->esq); /* mostra sae */
		
	}

	return;
}

int criar_arv_expressao(NoArv* arv, Node* cur, int height, int i) {
	int t=0;
    if (arv == NULL)
		return i;

    if (!arv->dir) { // right is an free
        NoArv* arv_dir = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv);
        arv->dir = arv_dir;
        i = 1;
    }

    else if (isOperatorNode(arv->dir->info)) { // right is an operator
        i = criar_arv_expressao(arv->dir, cur, height + 1, i);
    }

    else if (!arv->esq) { // left is an free
        NoArv* arv_esq = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv);
        arv->esq = arv_esq;
        i = 1;
    }

    else if (isOperatorNode(arv->esq->info)) { // left is an operator
        i = criar_arv_expressao(arv->esq, cur, height + 1, i);
    }
	

	if(i==1)
		return 1;
	
	while (height >= 0) {
        if(arv == arv->pai->esq)
        {
        	arv = arv->pai->pai;
        	height--;
    	}
		if(arv != arv->pai->esq)
			arv = arv->pai;
        height--;
        if(!arv->esq)
        {
        	NoArv* arv_esq = arv_cria(cur, arv_criavazia(), arv_criavazia(), arv);
        	arv->esq = arv_esq;
        	i = 1;
		}
		else if(isOperatorNode(arv->esq->info))
		{
			i = criar_arv_expressao(arv->esq, cur, height + 1, i);
		}
        if(i==1)
        	return i;
    }
}



int _print_t(NoArv* tree, int is_esq, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5, i;
    if (!tree) return 0;
    if(tree->info->tipo == 0){
		sprintf(b, "(%03d)", tree->info->num);
    }
    if(tree->info->tipo == 1){
		sprintf(b, "(%c)", tree->info->info);
    }

    int esq  = _print_t(tree->esq,  1, offset,                depth + 1, s);
    int dir = _print_t(tree->dir, 0, offset + esq + width, depth + 1, s);

#ifdef COMPACT
    for (i = 0; i < width; i++)
        s[depth][offset + esq + i] = b[i];

    if (depth && is_esq) {

        for (int i = 0; i < width + dir; i++)
            s[depth - 1][offset + esq + width/2 + i] = '-';

        s[depth - 1][offset + esq + width/2] = '.';

    } else if (depth && !is_esq) {

        for (int i = 0; i < esq + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + esq + width/2] = '.';
    }
#else
    for (i = 0; i < width; i++)
        s[2 * depth][offset + esq + i] = b[i];

    if (depth && is_esq) {

        for (i = 0; i < width + dir; i++)
            s[2 * depth - 1][offset + esq + width/2 + i] = '-';

        s[2 * depth - 1][offset + esq + width/2] = '+';
        s[2 * depth - 1][offset + esq + width + dir + width/2] = '+';

    } else if (depth && !is_esq) {

        for (i = 0; i < esq + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + esq + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return esq + width + dir;
}

void print_t(NoArv* tree)
{
    char s[20][255];
    int i;
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
