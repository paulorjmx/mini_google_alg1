#include <stdio.h>
#include <stdlib.h>
#include "inc/list.h"
#include "inc/keywords.h"

typedef struct no
{
    unsigned char cod[4];
    char nome[50];
    unsigned int relevancia;
    char link[100];
    KEYWORDS *keyword;
    struct no *prox;
}NO;

struct list
{
    NO *inicio, *fim;
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
        new->inicio = NULL;
        new->fim = NULL;
        new->tamanho = 0;
    }

    return new;
}


void erase_list(LIST *begin)
{
    NO* pt_aux = NULL, pt_aux2 = NULL;
    for(pt_aux = begin->inicio; pt_aux != NULL; pt_aux2 = pt_aux; pt_aux = pt_aux->prox)
    {
        free(pt_aux2);
    }
}
