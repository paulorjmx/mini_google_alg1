#include <stdio.h>
#include <stdlib.h>
#include "inc/list.h"
#include "inc/keywords.h"

typedef struct no
{
    unsigned int cod;
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


void insert_node(LIST *l, unsigned int code, char nome[], unsigned int relevancia, char link[])
{
    NO *new = (NO *) malloc(sizeof(NO));
    if(new != NULL)
    {
        new->cod = code;
        strcpy(new->nome, nome);
        new->relevancia = relevancia;
        strcpy(new->link, link);
        new->prox = NULL;
        if(l->tamanho == 0)
        {
            l->inicio = new;
            l->fim = l->inicio;
        }
        else
        {
            l->fim->prox = new;
            l->fim = new;
        }
        l->tamanho++;
    }
    else
    {
        printf("NAO FOI POSSIVEL ALOCAR O NO\n");
        new = NULL;
    }
}

void erase_list(LIST *begin)
{
    NO* pt_aux = NULL, pt_aux2 = NULL;
    for(pt_aux = begin->inicio; pt_aux != NULL; pt_aux2 = pt_aux; pt_aux = pt_aux->prox)
    {
        free(pt_aux2);
    }
}
