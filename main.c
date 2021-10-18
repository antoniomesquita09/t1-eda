#include <stdio.h>
#include <stdlib.h> 

typedef struct elemento
{
	int tipo; /* 0 para numero, 1 para simbolos */
	int num; /* numero que vai ser calculado, se nao for utilizar por ser simbolo sera NULL */
	char info; /* simbolo, se nao for o caso, sendo numero, sera NULL */
	struct elemento *prox;
} Elemento;

/* estrutura da pilha */
typedef struct pilha
{
	Elemento* topo; /* aponta para o topo da pilha */
	
} Pilha;

Pilha* pilha_cria (void)
{
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	if (p==NULL)
		exit(1);
	p->topo = NULL;
	return p;
}

int pilha_vazia (Pilha* p)
{
	if(p->topo == NULL)
		return 1;
	return 0;
}

void pilha_push (Pilha* p, char v, int tipo2, int num2)
{
	Elemento* n = (Elemento*) malloc(sizeof(Elemento));
	if (n==NULL)
	{
		printf("Sem memória para alocar elemento.\n");
		exit(1);
	}
	/* insere elemento na próxima posição livre */
	n->info = v;
	n->tipo = tipo2;
	n->	num = num2;
	n->prox = p->topo;
	p->topo = n;
}

int pilha_pop_num (Pilha* p)
{
	Elemento* t;
	int v;
	if (pilha_vazia(p))
	{
		printf("Pilha vazia.\n");
		return 'f';
	}
	t = p->topo;
	v = t->num;
	p-> topo = t->prox;
	free(t);
	return v;
}

unsigned char pilha_pop_op (Pilha* p)
{
	Elemento* t;
	unsigned char v;
	if (pilha_vazia(p))
	{
		printf("Pilha vazia.\n");
		return 'f';
	}
	t = p->topo;
	v = t->info;
	p-> topo = t->prox;
	free(t);
	return v;
}

void pilha_libera (Pilha* p)
{
	Elemento *t, *q = p->topo;
	while (q!=NULL)
	{
		t = q->prox;
		free(q);
		q = t;
	}
	free(p);
}

typedef struct avr
{
	int tipo;
	int valor;
	char oper;
	struct avr* esq;
	struct avr* dir;
	struct avr* pai;
} avrExp;



int arv_vazia (avrExp* a)
{
	return a==NULL;
}


avrExp* arv_cria (char c, avrExp* sae, avrExp* sad, int t, int v)
{
	avrExp* p=(avrExp*)malloc(sizeof(avrExp));
	if(p==NULL)
		exit(1);
	p->tipo = t;
	if(t == 0)
	{
		p->valor = t;
		p->oper = 'N';
	}
	if(t == 1)
	{
		p->valor = -1;
		p->oper = c;
	}
	p->esq = sae;
	p->dir = sad;
	return p;
}

avrExp* arv_libera (avrExp* a)
{
	if (!arv_vazia(a))
	{
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
	return NULL;
}

Pilha* infixtopostfix(char s[])
{
	Pilha *temp = pilha_cria();
	Pilha *post = pilha_cria();
	char temp2;
	// const char x[2] = " ";
	int i = 0, n = 1, temp3;
	while(s[i] != '\0')
	{
		if(s[i] == ' ')
			i++;
		else
		{
			if(s[i] >= '0' && s[i] <= '9')
			{
				char *ptr = (char*) malloc(sizeof(char));
				if (ptr==NULL)
				{
        			printf("Memoria insuficiente.\n");
        			exit(1); 
    			}
				ptr[0] = s[i];
				while(s[i+1] >= '0' && s[i+1] <= '9')
				{
					i++;
					ptr = realloc (ptr, (n+1) * sizeof (char));
					ptr[n] = s[i];
					n++;
					
				}
				temp3 = atoi(ptr);
				n = 1;
				free(ptr);
				pilha_push(post, 'N', 0, temp3);
			}
			else if(s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*')
			{
				temp2 = pilha_pop_op (temp);
				if(temp2 == '*' || temp2 == '/')
				{
					pilha_push(post, temp2, 1, -1);
					pilha_push(temp, s[i], 1, -1);
				}
				else if( temp2 != 'f')
				{
					pilha_push(temp, temp2, 1, -1);
					pilha_push(temp, s[i], 1, -1);
				}
				else
				{
					pilha_push(temp, s[i], 1, -1);
				}
			}
			else if(s[i] == '(')
			{
				pilha_push(temp, s[i], 1, -1);
			}
			else if (s[i] == ')')
			{
				temp2 = pilha_pop_op (temp);
				while(temp2 != '(')
				{
					pilha_push(post, temp2, 1, -1);
					temp2 = pilha_pop_op (temp);
				}
			}
			i++;
		}
	}
	temp2 = pilha_pop_op (temp);
	while( temp2 != 'f')
	{
		pilha_push(post, temp2, 1, -1);
		temp2 = pilha_pop_op (temp);
	}
	pilha_libera (temp);
	return post;
}


/*void arvore()
{
	s[] = '10 + 15';
	char temp;
	post = infixtopostfix(s);
	temp = pilha_pop (post);
	if (temp == '+' or temp == '-' or temp == '/' or temp == '*')
	{
		avrExp* a = arv_cria (temp, NULL, NULL, 1, NULL);
	}
	else
	{
		
	}
}*/

int main(void) {
	char s[8] = "1+2*3-4\0";

	Pilha* stack = infixtopostfix(s);

    printf("Postfix:\n");

    while (stack->topo != NULL) {
		if (stack->topo->tipo == 0) {
            printf("%d ", pilha_pop_num(stack));
			continue;
		}
		printf("%c ", pilha_pop_op(stack));
	}
    printf("\n");

	return 1;
}

// Result: + - 4 * 3 2 1
// Should be: 1 2 3 * + 4 -
