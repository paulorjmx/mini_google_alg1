#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/interface.h"

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls");
#endif

#ifdef __linux__
    #define CLEAR_SCREEN() system("clear");
#endif

LIST *get_from_file(const char *file_name)
{
    char nome[50], link[100], *pchave = NULL;
    unsigned int code = 0, relevancia = 0;
    LIST *l = create_list();
    KEYWORDS *k = create_keywords();
    pchave = (char *) malloc(sizeof(char) * 500);
    FILE *arq = fopen(file_name, "a+");
    if(arq != NULL)
    {
        while(1)
        {
            if(feof(arq) == 0)
            {
                fscanf(arq, "%u %s %u %s %s", code, nome, relevancia, link, pchave);
                printf("COD: %u\n", code);
                printf("NOME: %s\n", code);
                printf("RELEVANCIA: %u\n", relevancia);
                printf("LINK: %s\n", link);
                printf("PALAVRAS-CHAVE: %s\n", pchave);
            }
            printf("\n");
        }
    }
    else
    {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
    }
}

void menu(LIST *l)
{
    char escolha;
    while(escolha != -1)
    {
        CLEAR_SCREEN();
        printf("####################################################\n");
        printf("####################################################\n");
        printf("# \t\t\t\t\t\t   #");
        printf("\n#\t\tEscolha uma opcao \t\t   #\n# \t\t\t\t\t\t   #\n");
        printf("####################################################\n");
        printf("####################################################\n");

        printf("\n\t\t[1] Inserir Site");
        printf("\n\t\t[2] Remover Site");
        printf("\n\t\t[3] Inserir Palavra-chave");
        printf("\n\t\t[4] Atualizar Relevancia");
        printf("\n\t\t[5] Sair");
        printf("\n\t\t-> ");

        scanf(" %c", &escolha);

        switch(escolha)
        {
            case '1':
                menu_inserir(l);
                while(print_question("Deseja inserir mais algum site? ") == 0)
                {
                    menu_inserir(l);
                }
                break;

            case '2':
                menu_remover(l);
                break;

            case '3':
                menu_inserir_pchave(l);
                break;

            case '4':
                menu_atualizar_relevancia(l);
                break;

            case '5':
                escolha = -1;
                break;

            default:
                break;
        }
    }
}

void menu_inserir(LIST *l)
{
    fflush(stdin);
    size_t nbytes = 500;
    int i = 0, j = 0;
    unsigned int codigo = 0, relevancia = 0;
    char nome[50], link[100], *w = NULL, *palavras = NULL;
    KEYWORDS *pchave = NULL;
    w = (char *) malloc(sizeof(char) * 50);
    if(w == NULL)
    {
        printf("NAO FOI POSSIVEL ALOCAR ESPACO PARA A VARIAVEL AUXILIAR W\n");
        return;
    }
    palavras = (char *) malloc(sizeof(char) * nbytes);
    if(palavras == NULL)
    {
        printf("NAO FOI POSSIVEL ALOCAR ESPACO PARA AS PALAVRAS CHAVE\n");
        return;
    }
    CLEAR_SCREEN();
    printf("Digite o nome do site: ");
    scanf(" %[^\n]s", nome);
    printf("\nDigite o link para o site: ");
    scanf("%s", link);
    printf("\nDigite a relevancia que o site tera: ");
    scanf("%u", &relevancia);
    printf("\nDigite as palavras chaves separadas por virgula (max. 10): ");
    scanf("%s", palavras);
    codigo = (get_last_cod(l) + 1);
    pchave = create_keywords();
    while(palavras[i] != '\0')
    {
        if(palavras[i] == ',')
        {
            j = 0;
            printf("WORD: %s\n", w);
            insert_keyword(pchave, w);
        }
        else
        {

            w[j++] = palavras[i];
        }
        i++;
    }
    insert_keyword(pchave, w);
    insert_site(l, codigo, nome, relevancia, link, pchave);
    free(palavras);
    free(w);
}

int print_question(char *question)
{
    char escolha;
    int answer;
    printf("\n%s", question);
    scanf(" %c", &escolha);
    if(escolha == 's' || escolha == 'S')
    {
        answer = 0;
    }
    else
    {
        answer = 1;
    }
    return answer;
}

void menu_remover(LIST *l)
{

}

void menu_inserir_pchave(LIST *l)
{

}

void menu_atualizar_relevancia(LIST *l)
{

}
