#include "inc/site.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct site
{
    unsigned int codigo;
    char nome[50];
    unsigned int relevancia;
    char link[100];
    unsigned int qt_keywords;
};

SITE *site_create(unsigned int code, char *nome, unsigned int relevance, char *link)
{
    SITE *new = (SITE *) malloc(sizeof(SITE));
    if(new != NULL)
    {
        new->codigo = code;
        strcpy(new->nome, nome);
        new->relevancia = relevance;
        strcpy(new->link, link);
        new->qt_keywords = 0;
    }
}

unsigned int site_get_code(SITE *s)
{
    return s->codigo;
}

void site_free(SITE **s)
{
    free((*s));
    *s = NULL;
}

void site_to_string(SITE *s)
{
    printf("CODIGO: %u\n", s->codigo);
    printf("NOME: %s\n", s->nome);
    printf("RELEVANCIA: %u\n", s->relevancia);
    printf("LINK: %s\n", s->link);
    printf("QUANT. KEYWORDS: %u\n", s->qt_keywords);
}
