#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/keywords.h"

struct keywords
{
    char *word;
    int tamanho;
    struct keywords *prox;
};

KEYWORDS *create_keywords()
{
    KEYWORDS *new = (KEYWORDS *) malloc(sizeof(KEYWORDS));
    if(new != NULL)
    {
        new->word = NULL;
        new->tamanho = -1;
    }
    else
    {
        new = NULL;
        printf("ERRO AO ALOCAR A ESTRUTURA KEYWORDS\n");
    }

    return new;
}

void insert_keyword(KEYWORDS *begin, char *word)
{
    KEYWORDS *aux = NULL;
    if(begin != NULL && begin->tamanho < 10)
    {
        for(aux = begin; aux->prox != NULL; aux = aux->prox)
        {
        }
        aux->word = (char *) malloc(sizeof(char) * strlen(word));
        if(aux->word != NULL)
        {
            aux->word = strcpy(aux->word, word);
        }
        else
        {
            printf("NAO FOI POSSIVEL ALOCAR ESPACO PARA A PALAVRA\n");
        }
    }
    else
    {
        if(begin == NULL)
        {
            printf("A ESTRUTURA NAO EXISTE!\n");
        }
        else
        {
            printf("NAO E POSSIVEL INSERIR MAIS PALAVRAS\n");
        }
    }
}

void destroy_keywords(KEYWORDS *k)
{
    KEYWORDS *aux = NULL;
    if(k != NULL)
    {
        for(aux = k->prox; aux != NULL; k = aux, aux = aux->prox)
        {
            free(k->word);
            free(k);
        }
    }
    else
    {
        printf("A ESTRUTURA JA ESTA VAZIA!\n");
    }
}
