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

Pilha* pilha_cria(void);

void pilha_push(Pilha* p, Node* elem);

Node* pilha_pop(Pilha* p);

int pilha_vazia(Pilha* p);

void pilha_libera(Pilha* p);

int isOperator(char c);

int isNumber(char c);

int isGreater(char a, char b);

Pilha* infixtopostfix(char s[]);

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

Pilha* infixtopostfix(char s[]) {
    int i = 0, n = 1;
    Pilha* stack = pilha_cria();
    Pilha* result_stack = pilha_cria();
    
    while(s[i] != '\0') {
        Node* value = (Node*) malloc(sizeof(Node));

        char *aux = (char*) malloc(sizeof(char));

        aux[0] = s[i];

        if (isNumber(*aux)) {
            while(isNumber(s[i+1])) {
                i++;
                aux = realloc(aux, (n+1) * sizeof (char));
                aux[n] = s[i];
                n++;
            }

            int num = atoi(aux);

            value->tipo = 0;
            value->num = num;
            value->info = NULL;

            pilha_push(result_stack, value);
            
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
                    pilha_push(result_stack, previousNode);
                    previousNode = pilha_pop(stack);
                    previousOperator = previousNode->info;
                }
                break;
            }

            // printf("current: %c\n", *aux);
            // printf("%c is greater than %c: %d\n", previousOperator, *aux, isGreater(*aux, previousOperator));

            if (isGreater(previousOperator, *aux)) {
                pilha_push(result_stack, previousNode);
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
        n = 1;
        i++;
    }
    
    while (stack->topo > 0) {
        Node* cur = pilha_pop(stack);
        pilha_push(result_stack, cur);
    }

    pilha_libera(stack);

    return result_stack;
}
