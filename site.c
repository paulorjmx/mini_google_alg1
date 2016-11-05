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
    KEYWORDS *k_root;
    unsigned int qt_keywords;
};

SITE *site_create(unsigned int code, char *nome, unsigned int relevance, char *link, KEYWORDS *k, unsigned int num_keywords)
{
    SITE *new = (SITE *) malloc(sizeof(SITE));
    if(new != NULL)
    {
        new->codigo = code;
        strcpy(new->nome, nome);
        new->relevancia = relevance;
        strcpy(new->link, link);
        new->k_root = k;
        new->qt_keywords = num_keywords;
    }
}

unsigned int site_get_code(SITE *s)
{
    return s->codigo;
}

unsigned int site_get_nkeywords(SITE *s)
{
    return s->qt_keywords;
}

void site_free(SITE **s)
{
    if((*s)->k_root != NULL)
    {
        avlkeywords_free(&(*s)->k_root);
    }
    free((*s));
    *s = NULL;
}

KEYWORDS *site_get_keywords(SITE *s)
{
    return s->k_root;
}

void site_to_string(SITE *s)
{
    printf("CODIGO %u\n", s->codigo);
    printf("NOME: %s\n", s->nome);
    printf("RELEVANCIA: %u\n", s->relevancia);
    printf("LINK: %s\n", s->link);
    printf("KEYWORDS: ");
    avlkeywords_inorder(s->k_root);
    printf("\nQUANT. KEYWORDS: %u\n", s->qt_keywords);
}
