#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/keywords.h"

typedef struct nok
{
    char *word;
    struct nok *prox;
}NOK;

struct keywords
{
    NOK *inicio;
    NOK *fim;
    int tamanho;
};

KEYWORDS *create_keywords()
{
    KEYWORDS *new = (KEYWORDS *) malloc(sizeof(KEYWORDS));
    if(new != NULL)
    {
        new->inicio = NULL;
        new->fim = NULL;
        new->tamanho = 0;
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
    NOK *aux = NULL;
    if(begin != NULL && begin->tamanho < 10)
    {
        if(begin->inicio == NULL)
        {
            begin->inicio = (NOK *) malloc(sizeof(NOK));
            if(begin->inicio != NULL)
            {
                strcpy(begin->inicio->word, word);
                begin->inicio->prox = NULL;
                begin->fim = begin->inicio;
            }
            else
            {
                printf("ERRO AO TENTAR ALOCAR NOK!\n");
            }
        }
        else
        {
            aux = (NOK *) malloc(sizeof(NOK));
            if(aux != NULL)
            {
                strcpy(aux->word, word);
                aux->prox = NULL;
                begin->fim->prox = aux;
                begin->fim = aux;
            }
            else
            {
                printf("ERRO AO TENTAR ALOCAR NOK!\n");
            }
        }
        begin->tamanho++;
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

void print_keywords(KEYWORDS *k)
{
    NOK *aux = k->inicio;
    while (aux != NULL)
    {
        printf("%s, ", aux->word);
        aux = aux->prox;
    }
    printf("\n");
}

void destroy_keywords(KEYWORDS *k)
{
    NOK *aux = NULL, *aux2 = NULL;
    if(k != NULL)
    {
        for(aux = k->inicio, aux2 = aux->prox; aux2 != NULL; aux = aux2, aux2 = aux2->prox)
        {
            free(aux);
        }
        free(aux);
        free(k);
    }
    else
    {
        printf("A ESTRUTURA JA ESTA VAZIA!\n");
    }
}
