#include "inc/site.h"
#include <stdio.h>
#include <stdlib.h>

struct site
{
    unsigned int cod;
    char nome[50];
    unsigned int relevancia;
    char link[100];
    unsigned int size_keywords;
};

SITE *site_create()
{

}

unsigned int site_get_code(SITE *s)
{
    return s->cod;
}
