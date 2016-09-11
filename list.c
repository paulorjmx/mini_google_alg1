#include <stdio.h>
#include <stdlib.h>
#include "inc/list.h"

struct list
{
    unsigned char cod[4];
    char nome[50];
    unsigned int relevancia;
    char link[100];
    char keywords[10][50];
};

LIST *create()
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
        new->keywords[0][0] = NULL;
    }

    return new;
}
