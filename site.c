#include "inc/site.h"
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

void site_update_relevance(SITE *s, unsigned int relevance)
{
    s->relevancia = relevance;
}

unsigned int site_get_code(SITE *s)
{
    return s->codigo;
}

unsigned int site_get_relevance(SITE *s)
{
    return s->relevancia;
}

unsigned int site_get_nkeywords(SITE *s)
{
    return s->qt_keywords;
}

void site_free(SITE **s)
{
    if(s != NULL)
    {
        if((*s)->k_root != NULL)
        {
            avlkeywords_free(&(*s)->k_root);
        }
        free((*s));
        *s = NULL;
    }
}

void site_update_nkeywords(SITE *s, unsigned int num_keywords)
{
    if(s != NULL)
    {
        s->qt_keywords = num_keywords;
    }
}

KEYWORDS **site_get_keywords(SITE *s)
{
    return &(s->k_root);
}

void site_to_string(SITE *s)
{
    if(s != NULL)
    {
        printf("CODIGO %u\n", s->codigo);
        printf("NOME: %s\n", s->nome);
        printf("RELEVANCIA: %u\n", s->relevancia);
        printf("LINK: %s\n", s->link);
        printf("KEYWORDS: ");
        avlkeywords_inorder(s->k_root);
        printf("\nQUANT. KEYWORDS: %u\n", s->qt_keywords);
    }
}

void site_to_file(SITE *s, FILE *arq)
{
    if(s != NULL)
    {
        fprintf(arq, "%u,%s,%u,%s,", s->codigo, s->nome, s->relevancia, s->link);
        avlkeywords_inorder_file(s->k_root, arq);
    }
}

int site_search_keyword(SITE *s, char *keyword)
{
    if(s != NULL)
    {
        if(avlkeywords_search(s->k_root, keyword) != NULL)
        {
            return 0;
        }
    }

    return 1;
}

void site_print_namelink(SITE *s)
{
    printf("%s\t\t%s\n", s->nome, s->link);
}
