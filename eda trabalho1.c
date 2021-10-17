#include <stdio.h>


struct elemento
{
	int tipo;
	int num;
	char info;
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

void pilha_push (Pilha* p, char v)
{
	Elemento* n = (Elemento*) malloc(sizeof(Elemento));
	if (n==NULL)
	{
		printf("Sem memória para alocar elemento.\n");
		exit(1);
	}
	/* insere elemento na próxima posição livre */
	n->info = v;
	n->prox = p->topo;
	p->topo = n;
}

unsigned char pilha_pop (Pilha* p)
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

/*char convert(string s)
{
	i = 0, j = 0;
	char temp[250];
	unsigned char temp2;
	while(s[i] != '\0')
	{
		while(s[i] != '(' or s[i] != '+' or s[i] != '-' or s[i] != '/' or s[i] != '*' or s[i] != ')' or s[i] != ' ')
		{
			temp[j] = s[i];
		}
		
	}
}*/

Pilha* infixtopostfix(string s)
{
	temp = pilha_cria;
	post = pilha_cria;
	char temp2;
	const char x[2] = " ";
	i = 0;
	while(s[i] != '\0')
	{
		if(s[i] == ' ')
			pilha_push(post, s[i]);
			i++;
		else
		{
			if(s[i] >= '0' && s[i] <= '9')
			{
				pilha_push(post, s[i]);
			}
			else if(s[i] == '+' or s[i] == '-' or s[i] == '/' or s[i] == '*')
			{
				temp2 = pilha_pop (temp);
				if(temp2 == '*' or temp2 == '/')
				{
					pilha_push(post, temp2);
					pilha_push(temp, s[i]);
				}
				else
				{
					pilha_push(temp, temp2);
					pilha_push(temp, s[i]);
				}
			}
			else if(s[i] == '(')
			{
				pilha_push(temp, s[i]);
			}
			else if (s[i] == ')')
			{
				temp2 = pilha_pop (temp);
				while(temp2 != '(')
				{
					pilha_push(temp2, s[i]);
					temp2 = pilha_pop (temp);
				}
			}
			i++;
		}
	}
	temp2 = pilha_pop (temp);
	while( temp2 != 'f')
	{
		pilha_push(temp2, s[i]);
		temp2 = pilha_pop (temp);
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


