#include <stdio.h>
#include <stdlib.h> 

struct elemento
{
	int tipo; /* 0 para numero, 1 para simbolos */
	int num; /* numero que vai ser calculado, se nao for utilizar por ser simbolo sera NULL */
	char info; /* simbolo, se nao for o caso, sendo numero, sera NULL */
	struct elemento *prox
};
typedef struct elemento Elemento;

/* estrutura da pilha */
struct pilha
{
	Elemento* topo; /* aponta para o topo da pilha */
	
};
typedef struct pilha Pilha;

Pilha* pilha_cria (void)
{
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	if (p==NULL)
		exit(1);
	p->topo = NULL;
	return p;
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

unsigned char pilha_pop_num (Pilha* p)
{
	Elemento* t;
	int v;
	if (pilha_vazia(p))
	{
		printf("Pilha vazia.\n");
		return f;
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
		return f;
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

int pilha_vazia (Pilha* p)
{
	if(p->topo == NULL)
		return 1;
	return 0;
}

typedef struct avr
{
	int tipo
	int valor;
	char oper;
	struct avrExp* esq;
	struct avrExp* dir;
	struct avrExp* pai;
} avrExp;

avrExp* arv_cria (char c, avrExp* sae, avrExp* sad, int t, int v)
{
	avrExp* p=(avrExp*)malloc(sizeof(avrExp));
	if(p==NULL)
		exit(1);
	p->tipo = t;
	if(t == 0)
	{
		p->valor = t;
		p->oper = NULL;
	}
	if(t == 1)
	{
		p->valor = NULL;
		p->oper = c;
	}
	p->esq = sae;
	p->dir = sad;
	return p;
}

NoArv* arv_libera (avrExp* a)
{
	if (!arv_vazia(a))
	{
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
	return NULL;
}



int arv_vazia (avrExp* a)
{
	return a==NULL;
}


Pilha* infixtopostfix(string s)
{
	temp = pilha_cria;
	post = pilha_cria;
	char temp2;
	const char x[2] = " ";
	int i = 0, j, n = 1, temp3;
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
				ptr[0] = s[i]
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
				pilha_push(post, NULL, 0, temp3);
			}
			else if(s[i] == '+' or s[i] == '-' or s[i] == '/' or s[i] == '*')
			{
				temp2 = pilha_pop_op (temp);
				if(temp2 == '*' or temp2 == '/')
				{
					pilha_push(post, temp2, 1, NULL);
					pilha_push(temp, s[i], 1, NULL);
				}
				else if( temp2 != 'f')
				{
					pilha_push(temp, temp2, 1, NULL);
					pilha_push(temp, s[i], 1, NULL);
				}
				else
				{
					pilha_push(temp, s[i], 1, NULL);
				}
			}
			else if(s[i] == '(')
			{
				pilha_push(temp, s[i], 1, NULL);
			}
			else if (s[i] == ')')
			{
				temp2 = pilha_pop_op (temp);
				while(temp2 != '(')
				{
					pilha_push(temp2, s[i], 1, NULL);
					temp2 = pilha_pop_op (temp);
				}
			}
			i++;
		}
	}
	temp2 = pilha_pop_op (temp);
	while( temp2 != 'f')
	{
		pilha_push(post, temp2, 1, NULL);
		temp2 = pilha_pop_op (temp);
	}
	pilha_libera (temp);
	return post;
}


void arvore()
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
}




