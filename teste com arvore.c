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

int elem_ou_op (Pilha *p)
{
	Elemento* t;
	int v;
	if (pilha_vazia(p))
	{
		printf("Pilha vazia 2.\n");
		return 'f';
	}
	t = p->topo;
	v = t->tipo;
	return v;
}

char pilha_pop_op (Pilha* p)
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

avrExp* arv_cria (char c, avrExp* sae, avrExp* sad, avrExp* dad, int t, int v)
{
	avrExp* p=(avrExp*)malloc(sizeof(avrExp));
	if(p==NULL)
		exit(1);
	p->tipo = t;
	if(t == 0)
	{
		p->valor = v;
		p->oper = 'N';
	}
	if(t == 1)
	{
		p->valor = -1;
		p->oper = c;
	}
	p->pai = dad;
	p->esq = sae;
	p->dir = sad;
	return p;
}


int arv_vazia (avrExp* a)
{
	return a==NULL;
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
			else if(s[i] == '/' || s[i] == '*')
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
			else if(s[i] == '+' || s[i] == '-')
			{
				temp2 = pilha_pop_op (temp);
				if(temp2 != 'f')
				{
					while(temp2 != 'f' && temp2 != '(')
					{
						pilha_push(post, temp2, 1, -1);
						temp2 = pilha_pop_op (temp);
					}
					if(temp2 == '(')
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
			else if(s[i] == ')')
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

void arv_imprime (avrExp* a)
{
	if (!arv_vazia(a))
	{
		if(a->tipo == 0)
			printf("%c ",a->valor); /* mostra raiz */
		if(a->tipo == 1)
			printf("%c ",a->oper); /* mostra raiz */
		arv_imprime(a->dir); /* mostra sad */
		arv_imprime(a->esq); /* mostra sae */
	}

	return;
}

avrExp* arv_criavazia ()
{	
	return NULL;
}


void preenche_arvore(Pilha* post)
{
	char temp;
	int tipo;
	tipo = elem_ou_op (post);
	printf("%d qyak tipo \n", tipo);
	avrExp* avr;
	if(tipo == 1)
	{
		temp = pilha_pop_op (post);
		avr = arv_cria (temp, arv_criavazia(), arv_criavazia(), avr, 1, -1);
	}
	else
	{
		printf("Problema ao criar raiz, não é um operador \n");
		exit(1);
	}
	tipo = elem_ou_op (post);
	avrExp* filho = avr->dir;
	avrExp* dad = avr;
	int lado = -1;
	while(tipo != 'f')
	{
		printf("to trabalhando com tipo %d \n", tipo);
		while(filho != NULL)
		{
			if(filho->tipo == 1 || filho->tipo == -1)
			{
				dad = filho;
				filho = filho->dir;
				lado = 1;
			}
			else if(filho->tipo == 0)
			{
				if (filho != filho->pai->esq)
				{
					dad = filho->pai;
					filho = filho->pai->esq;
					printf("Teste \n");
				}
				else
				{
					dad = filho->pai->pai;
					filho = filho->pai->pai->esq;
				}
			}
		}
		
		if(tipo == 0)
		{
			filho = arv_cria ('N', arv_criavazia(), arv_criavazia(), dad, 0, pilha_pop_num (post));
		}
		else if(tipo == 1)
		{
			filho = arv_cria (pilha_pop_op (post), arv_criavazia(), arv_criavazia(), dad, 1, -1);
		}
		tipo = elem_ou_op (post);
	}
	filho = avr->dir;
	if(avr->dir != NULL)
		printf(" FADFDA%d ", avr->tipo);
	arv_imprime (avr);
	
}


int main(void) {
	char s[20] = "1+(2-3)/4-5*6+7\0";

	Pilha* stack = infixtopostfix(s);

    preenche_arvore(stack);
	
	return 1;
}

// Result: - 5 / 4 * 3 + 2 1 => 1 2 + 3 * 4 / 5 -
// Should be: 1 2 3 * 4 / + 5 -


/*int main(void)
{
	preenche_arvore;
	return 0;
}*/
