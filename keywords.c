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
        aux = (NOK *) malloc(sizeof(NOK));
        if(aux != NULL)
        {
            aux->prox = NULL;
            aux->word = (char *) malloc(sizeof(char) * strlen(word));
            if(aux->word != NULL)
            {
                strcpy(aux->word, word);
                if(begin->inicio == NULL)
                {
                    begin->inicio = aux;
                    begin->fim = begin->inicio;
                }
                else
                {
                    begin->fim->prox = aux;
                    begin->fim = aux;
                }
            }
            else
            {
                free(aux);
                printf("NAO FOI POSSIVEL ALOCAR ESPACO PARA WORD\n");
            }
        }
        else
        {
            printf("ERRO AO TENTAR ALOCAR NOK\n");
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
        if(k->tamanho > 0)
        {
            for(aux = k->inicio, aux2 = k->inicio->prox; aux2 != NULL; aux = aux2, aux2 = aux2->prox)
            {
                free(aux->word);
                free(aux);
            }
            free(aux->word);
            free(aux);
        }
        free(k);
    }
    else
    {
        printf("A ESTRUTURA JA ESTA VAZIA!\n");
    }
}
