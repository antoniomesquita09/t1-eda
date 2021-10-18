#include <stdio.h>
#include <stdlib.h>
/* TAD: pilha de nodes */

#define N 50 /* número máximo de elementos */

struct node {
	int tipo; /* 0 para numero, 1 para simbolos */
	int num; /* numero que vai ser calculado, se nao for utilizar por ser simbolo sera NULL */
	char info; /* simbolo, se nao for o caso, sendo numero, sera NULL */
};

typedef struct node Node;

struct pilha {
    int topo; /* vet[topo]: primeira posição livre do vetor */
    Node* vet[N];
};

typedef struct pilha Pilha;

struct fila {
    int n; /* número de elementos na fila */
    int ini; /* posição do próximo elemento a ser retirado da lista */
    Node* vet[N]; /* vet[0] a vet[N-1]: posições ocupáveis */
};

typedef struct fila Fila;

Pilha* pilha_cria(void);

void pilha_push(Pilha* p, Node* elem);

Node* pilha_pop(Pilha* p);

int pilha_vazia(Pilha* p);

void pilha_libera(Pilha* p);

Fila* fila_cria(void);

void fila_insere(Fila* f, Node* v);

Node* fila_retira(Fila* f);

int fila_vazia(Fila* f);

int isOperator(char c);

int isNumber(char c);

int isGreater(char a, char b);

Fila* infixtopostfix(char s[]);

int main(void) {
    char s[100] = "1+2*3/4-5*(6+7)\0";
    Fila* queue = infixtopostfix(s);

    printf("Postfix:\n");

    while (queue->n > 0) {
        Node* cur = fila_retira(queue);
        if (cur->tipo == 0) {
            printf("%d", cur->num);
            continue;
        }
        printf("%c", cur->info);
    }
    printf("\n");
    return 1;
}

Pilha* pilha_cria() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) exit(1);
    p->topo = 0; /* inicializa com zero elementos */
    return p;
}

void pilha_push(Pilha* p, Node* elem) {
    if (p->topo == N) { /* capacidade esgotada */
        printf("Stackoverflow.\n");
        exit(1); /* aborta programa */
    }
    /* insere elemento na próxima posição livre */
    p->vet[p->topo] = elem;
    p->topo++;
}

int pilha_vazia(Pilha* p) {
    if(p->topo == 0)
        return 1;
    return 0;
}

Node* pilha_pop(Pilha* p) {
    Node* elem;
    if(pilha_vazia(p)) {
        printf("Pilha vazia.\n");
        exit(1); /* aborta programa */
    }
    /* retira elemento do topo */
    elem = p->vet[p->topo-1];
    p->topo--;
    return elem;
}

void pilha_libera(Pilha* p) {
    int i;
    for(i=0; i < p->topo; i++)
        free(p->vet[i]);
    free(p);
}

int fila_vazia(Fila* f) {
    return f->n == 0;
}

Fila* fila_cria(void) {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->n = 0; /* inicializa fila como vazia */
    f->ini = 0; /* escolhe uma posição inicial */
    return f;
}

void fila_insere(Fila* f, Node* v) {
    int fim;
    if (f->n == N) { /* fila cheia: capacidade esgotada */
        printf("Capacidade da fila estourou.\n");
        exit(1); /* aborta programa */
    }
    /* insere elemento na próxima posição livre */
    fim = (f->ini + f->n) % N;
    f->vet[fim] = v;
    f->n++;
}

Node* fila_retira(Fila* f) {
    Node* v;
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        exit(1); /* aborta programa */
    }
    /* retira elemento do início */
    v = f->vet[f->ini];
    f->ini = (f->ini + 1) % N;
    f->n--;
    return v;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*';
}

int isNumber(char c) {
    return c >= '0' && c <= '9';
}

int isGreater(char previous, char current) {
    if (current == '(')
        return 0;
    if (previous == '*' || previous == '/')
        return 1;
    if (previous == '+' && current == '+')
        return 1;
    if (previous == '+' && current == '-')
        return 1;
    if (previous == '-' && current == '+')
        return 1;
    if (previous == '-' && current == '-')
        return 1;
    return 0;
}

Fila* infixtopostfix(char s[]) {
    int i = 0;
    Pilha* stack = pilha_cria();
    Fila* queue = fila_cria();
    
    while(s[i] != '\0') {
        Node* value = (Node*) malloc(sizeof(Node));

        char *aux = (char*) malloc(sizeof(char));

        aux[0] = s[i];

        if (isNumber(*aux)) {
            int num = atoi(aux);

            value->tipo = 0;
            value->num = num;
            value->info = NULL;

            fila_insere(queue, value);
            
            i++;
            continue;
        }

        value->tipo = 1;
        value->num = NULL;
        value->info = *aux;

        while(!pilha_vazia(stack)) {
            Node* previousNode = pilha_pop(stack);

            char previousOperator = previousNode->info;

            if (*aux == ')') {
                while(previousOperator != '(') {
                    fila_insere(queue, previousNode);
                    previousNode = pilha_pop(stack);
                    previousOperator = previousNode->info;
                }
                break;
            }

            // printf("current: %c\n", *aux);
            // printf("%c is greater than %c: %d\n", previousOperator, *aux, isGreater(*aux, previousOperator));

            if (isGreater(previousOperator, *aux)) {
                fila_insere(queue, previousNode);
            } else {
                pilha_push(stack, previousNode);
                break;
            }
        }

        if (*aux == ')') {
            i++;
            continue;
        }

        pilha_push(stack, value);
        i++;
    }
    
    while (stack->topo > 0) {
        Node* cur = pilha_pop(stack);
        fila_insere(queue, cur);
    }

    pilha_libera(stack);

    return queue;
}
