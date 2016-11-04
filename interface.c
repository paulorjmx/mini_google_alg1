#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/interface.h"

int print_question(char *question);

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls");
#endif

#ifdef __linux__
    #define CLEAR_SCREEN() system("clear");
#endif

AVL_SITE *get_from_file(char *file_name)
{
    AVL_SITE *avlsite_tmp = NULL;
    KEYWORDS *avlkeywords_tmp = NULL;
    SITE *s = NULL;
    char nome[50], link[100], keyword[50], *line = NULL;
    unsigned int code = 0, relevancia = 0;
    line = (char *) malloc(sizeof(char) * 1000);
    char *addr_line = line;
    FILE *arq = fopen(file_name, "a+");
    if(arq != NULL)
    {
        fscanf(arq, "%s", line);
        sscanf(line, "%u", &code);
        line = strchr(line, ',');
        sscanf(++line, " %[^,]s", nome);
        line = strchr(line, ',');
        sscanf(++line, "%u", &relevancia);
        line = strchr(line, ',');
        sscanf(++line, " %[^,]s", link);
        line = strchr(line, ',');
        sscanf(++line, " %[^,]s", keyword);
        avlkeywords_tmp = avlkeywords_create(keyword);
        line = strchr(line, ',');
        while(line != NULL)
        {
            sscanf(++line, " %[^,]s", keyword);
            avlkeywords_insert_node(&avlkeywords_tmp, keyword);
            line = strchr(line, ',');
        }
        s = site_create(code, nome, relevancia, link);
        avlsite_tmp = avlsite_create(s, avlkeywords_tmp);

        line = addr_line;
        while(1)
        {
            fscanf(arq, "%s", line);
            if(feof(arq))
            {
                break;
            }
            else
            {
                sscanf(line, "%u", &code);
                line = strchr(line, ',');
                sscanf(++line, " %[^,]s", nome);
                line = strchr(line, ',');
                sscanf(++line, "%u", &relevancia);
                line = strchr(line, ',');
                sscanf(++line, " %[^,]s", link);
                line = strchr(line, ',');
                sscanf(++line, " %[^,]s", keyword);
                avlkeywords_tmp = avlkeywords_create(keyword);
                s = site_create(code, nome, relevancia, link);
                avlsite_insert_node(&avlsite_tmp, s, avlkeywords_tmp);
            }
        }

        sscanf(line, "%u", &code);
        line = strchr(line, ',');
        sscanf(++line, " %[^,]s", nome);
        line = strchr(line, ',');
        sscanf(++line, "%u", &relevancia);
        line = strchr(line, ',');
        sscanf(++line, " %[^,]s", link);
        line = strchr(line, ',');
        sscanf(++line, " %[^,]s", keyword);
        avlkeywords_tmp = avlkeywords_create(keyword);
        s = site_create(code, nome, relevancia, link);
        avlsite_insert_node(&avlsite_tmp, s, avlkeywords_tmp);
    }
    else
    {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
    }
    fclose(arq);
    free(addr_line);
    return avlsite_tmp;
}

void menu()
{
    AVL_SITE *root = get_from_file("googlebot.txt");
    avlsite_inorder(root);
    // char escolha;
    // while(escolha != -1)
    // {
    //     CLEAR_SCREEN();
    //     printf("####################################################\n");
    //     printf("####################################################\n");
    //     printf("# \t\t\t\t\t\t   #");
    //     printf("\n#\t\tEscolha uma opcao \t\t   #\n# \t\t\t\t\t\t   #\n");
    //     printf("####################################################\n");
    //     printf("####################################################\n");
    //
    //     printf("\n\t\t[1] Inserir Site");
    //     printf("\n\t\t[2] Remover Site");
    //     printf("\n\t\t[3] Inserir Palavra-chave");
    //     printf("\n\t\t[4] Atualizar Relevancia");
    //     printf("\n\t\t[5] Sair");
    //     printf("\n\t\t-> ");
    //
    //     scanf(" %c", &escolha);
    //
    //     switch(escolha)
    //     {
    //         case '1':
    //             menu_inserir(l);
    //             while(print_question("Deseja inserir mais algum site?[s/N]: ") == 0)
    //             {
    //                 menu_inserir(l);
    //             }
    //             break;
    //
    //         case '2':
    //             menu_remover(l);
    //             while(print_question("Deseja remover mais algum site?[s/N]: ") == 0)
    //             {
    //                 menu_remover(l);
    //             }
    //             break;
    //
    //         case '3':
    //             menu_inserir_pchave(l);
    //             while (print_question("Deseja inserir palavras-chave em mais algum site?[s/N]: ") == 0)
    //             {
    //                 menu_inserir_pchave(l);
    //             }
    //             break;
    //
    //         case '4':
    //             menu_atualizar_relevancia(l);
    //             while (print_question("Deseja atualizar a relevancia de mais algum site?[s/N]: ") == 0)
    //             {
    //                 menu_atualizar_relevancia(l);
    //             }
    //             break;
    //
    //         case '5':
    //             escolha = -1;
    //             avlsite_free(&root);
    //             // write_on_file(l, "googlebot.txt");
    //             break;
    //
    //         default:
    //             break;
    //     }
    // }
}

// void menu_inserir()
// {
//     fflush(stdin);
//     size_t nbytes = 500;
//     unsigned int codigo = 0, relevancia = 0;
//     char nome[50], link[100], *palavras = NULL;
//     palavras = (char *) malloc(sizeof(char) * nbytes);
//     if(palavras == NULL)
//     {
//         printf("NAO FOI POSSIVEL ALOCAR ESPACO PARA AS PALAVRAS CHAVE\n");
//         return;
//     }
//     CLEAR_SCREEN();
//     printf("Digite o nome do site: ");
//     scanf(" %[^\n]s", nome);
//     printf("\nDigite o link para o site: ");
//     scanf("%s", link);
//     printf("\nDigite a relevancia que o site tera: ");
//     scanf("%u", &relevancia);
//     printf("\nDigite as palavras chaves separadas por virgula (max. 10): ");
//     scanf("%s", palavras);
//     codigo = (get_last_cod(l) + 1);
//     insert_site(l, codigo, nome, relevancia, link, palavras);
//     free(palavras);
// }
//
// int print_question(char *question)
// {
//     char escolha;
//     int answer;
//     printf("\n%s", question);
//     scanf(" %c", &escolha);
//     if(escolha == 's' || escolha == 'S')
//     {
//         answer = 0;
//     }
//     else
//     {
//         answer = 1;
//     }
//     return answer;
// }
//
// void menu_remover()
// {
//     unsigned int cod = 0;
//     CLEAR_SCREEN();
//     if(l != NULL)
//     {
//         print_list(l);
//         printf("\n");
//         printf("Digite o codigo do site que deseja remover: ");
//         scanf("%u", &cod);
//         remove_site(l, cod);
//     }
//     else
//     {
//         printf("Voce nao cadastrou nenhum site!\n");
//     }
// }
//
// void menu_inserir_pchave()
// {
//     char *w = NULL;
//     unsigned int cod = 0, nw = 0, nword = 0;
//     w = (char *) malloc(sizeof(char) * 300);
//     if(w != NULL)
//     {
//         CLEAR_SCREEN();
//         print_list(l);
//         printf("Digite o codigo do site que deseja adicionar mais palavras-chave: ");
//         scanf("%u", &cod);
//         nw = nwords(l, cod);
//         printf("\nDigite as palavras-chave, separadas por virgula, que deseja inserir(max. %d): ", (10 - nw));
//         scanf("%s", w);
//         nword = count_words(w);
//         if(nword > (10 - nw))
//         {
//             printf("A QUANTIDADE DE PALAVRAS-CHAVE NAO PODE ULTRAPASSAR 10!\n");
//         }
//         else
//         {
//             update_pchave(l, cod, w);
//         }
//     }
//     else
//     {
//         printf("NAO FOI POSSIVEL ALOCAR MEMORIA PARA AS PALAVRAS-CHAVE!\n");
//     }
//     free(w);
// }
//
// void menu_atualizar_relevancia()
// {
//     unsigned int cod = 0, relevancia = 0;
//     CLEAR_SCREEN();
//     print_list(l);
//     printf("Digite o codigo do site que deseja atualizar a relevancia: ");
//     scanf("%u", &cod);
//     printf("\nDigite o novo valor que a relevancia do site tera: ");
//     scanf("%u", &relevancia);
//     update_relevance(l, relevancia, cod);
// }
