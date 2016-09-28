#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/list.h"

typedef struct no
{
    unsigned int cod;
    char nome[50];
    unsigned int relevancia;
    char link[100];
    char *keyword;
    struct no *prox;
}NO;

struct list
{
    NO *inicio, *fim;
    int tamanho;
};

void write_on_file(LIST *l, const char *file_name)
{
    NO *ptr = NULL;
    FILE *arq = fopen(file_name, "w");
    if(arq != NULL)
    {
        for(ptr = l->inicio; ptr != NULL; ptr = ptr->prox)
        {
            fprintf(arq, "%u,%s,%u,%s,%s\n", ptr->cod, ptr->nome, ptr->relevancia, ptr->link, ptr->keyword);
        }
    }
    else
    {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO: %s\n", file_name);
    }
    fclose(arq);
}

void print_list(LIST *l)
{
    NO *aux = l->inicio;
    while(aux != NULL)
    {
        printf("CODIGO: %u\n", aux->cod);
        printf("NOME: %s\n", aux->nome);
        printf("RELEVANCIA: %u\n", aux->relevancia);
        printf("LINK: %s\n", aux->link);
        printf("KEYWORDS: %s\n", aux->keyword);
        aux = aux->prox;
        printf("\n");
    }
}

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


void insert_site(LIST *l, unsigned int codigo, char nome[], unsigned int relevancia, char link[], char *palavras_chave)
{
    NO *new = (NO *) malloc(sizeof(NO));
    if(new != NULL)
    {
        new->cod = codigo;
        strcpy(new->nome, nome);
        new->relevancia = relevancia;
        strcpy(new->link, link);
        new->keyword = (char *) malloc(sizeof(char) * strlen(palavras_chave));
        new->keyword = strcpy(new->keyword, palavras_chave);
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

void update_relevance(LIST *l, unsigned int relevancia, unsigned int cod)
{
    NO *ptr = NULL;
    if(l != NULL && l->tamanho > 0)
    {
        for(ptr =  l->inicio; ptr->cod != cod && ptr != NULL; ptr = ptr->prox) { }
        if(ptr != NULL)
        {
            ptr->relevancia = relevancia;
        }
        else
        {
            printf("O ELEMENTO NAO ESTA CADASTRADO\n");
        }
    }
}

void remove_site(LIST *l, unsigned int cod)
{
    NO *ptr = NULL, *ptr2 = NULL;
    if(l != NULL && l->tamanho > 0)
    {
        for(ptr2 = NULL, ptr =  l->inicio; ptr->cod != cod && ptr != NULL; ptr2 = ptr, ptr = ptr->prox) { }
        if(ptr != NULL)
        {
            if(ptr == l->inicio)
            {
                ptr2 = ptr->prox;
                l->inicio = ptr2;
                ptr->prox = NULL;
            }
            else
            {
                ptr2->prox = ptr->prox;
                ptr->prox = NULL;
            }
            l->tamanho--;
            free(ptr);
        }
        else
        {
            printf("O ELEMENTO NAO ESTA CADASTRADO\n");
        }
    }
}


unsigned int get_last_cod(LIST *l)
{
    if(l != NULL && l->tamanho > 0)
    {
        return l->fim->cod;
    }
    else
    {
        return 0;
    }
}

void erase_list(LIST *l)
{
    NO* pt_aux = NULL, *pt_aux2 = NULL;
    if(l != NULL)
    {
        if(l->tamanho > 0)
        {
            for(pt_aux = l->inicio->prox, pt_aux2 = l->inicio; pt_aux != NULL; pt_aux2 = pt_aux, pt_aux = pt_aux->prox)
            {
                free(pt_aux2->keyword);
                free(pt_aux2);
            }
            free(pt_aux2->keyword);
            free(pt_aux2);
        }
        free(l);
    }
}
