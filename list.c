#include <stdio.h>
#include <stdlib.h>
#include "inc/list.h"
#include "inc/keywords.h"

struct list
{
    unsigned char cod[4];
    char nome[50];
    unsigned int relevancia;
    char link[100];
    KEYWORDS *keyword;
    struct list *prox;
    int tamanho;
};

LIST *create_list()
{
    LIST *new = (LIST *) malloc(sizeof(LIST));
    if(new == NULL)
    {
        printf("ERRO AO CRIAR A LISTA\n");
        new = NULL;
    }
    else
    {
        new->cod = NULL;
        new->nome = NULL;
        new->relevancia = 0;
        new->link = NULL;
        new->keywords = NULL;
        tamanho = -1;
    }

    return new;
}


void erase_list(LIST *begin)
{
    LIST* pt_aux = NULL;
    for(pt_aux = begin->prox; pt_aux != NULL; begin = pt_aux; pt_aux = pt_aux->prox)
    {
        free(begin);
    }
}
