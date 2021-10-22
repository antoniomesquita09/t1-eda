#include <stdio.h>
#include <stdlib.h>

float arv_valorEA(NoArv* arv);

float arv_valorEA(NoArv* arv) {
	if (arv == NULL || ((arv->info->tipo != 0) && (arv->info->tipo != 1)))
		return 0;
		
	else if (arv->info->tipo == 0)
	{
		return arv->info->num;
	}
	else {
		switch ( arv->info->info )
		{
		
			case('+'):
				return arv_valorEA(arv->esq) + arv_valorEA(arv->dir);
				break;
				
			case('-'):
				return arv_valorEA(arv->esq) - arv_valorEA(arv->dir);
				break;
			
			case('*'):
				return arv_valorEA(arv->esq) * arv_valorEA(arv->dir);
				break;
				
			case('/'):
				return arv_valorEA(arv->esq) / arv_valorEA(arv->dir);
				break;
				
			default :
    			printf ("Valor invalido!\n");
		}
	}	
}
