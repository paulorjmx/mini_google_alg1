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
    unsigned int code = 0, relevancia = 0, num_keywords = 0;
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
        num_keywords += 1;
        line = strchr(line, ',');
        while(line != NULL)
        {
            sscanf(++line, " %[^,]s", keyword);
            avlkeywords_insert_node(&avlkeywords_tmp, keyword);
            num_keywords += 1;
            line = strchr(line, ',');
        }
        s = site_create(code, nome, relevancia, link, avlkeywords_tmp, num_keywords);
        avlsite_tmp = avlsite_create(s);

        while(1)
        {
            line = addr_line;
            fscanf(arq, "%s", line);
            if(feof(arq))
            {
                break;
            }
            else
            {
                num_keywords = 0;
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
                num_keywords += 1;
                line = strchr(line, ',');
                while(line != NULL)
                {
                    sscanf(++line, " %[^,]s", keyword);
                    avlkeywords_insert_node(&avlkeywords_tmp, keyword);
                    num_keywords += 1;
                    line = strchr(line, ',');
                }
                s = site_create(code, nome, relevancia, link, avlkeywords_tmp, num_keywords);
                avlsite_insert_node(&avlsite_tmp, s);
            }
        }
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
        printf("\n\t\t[5] Busca por palavra-chave");
        printf("\n\t\t[6] Sair");
        printf("\n\t\t-> ");

        scanf(" %c", &escolha);

        switch(escolha)
        {
            case '1':
                menu_inserir(&root);
                while(print_question("Deseja inserir mais algum site?[s/N]: ") == 0)
                {
                    menu_inserir(&root);
                }
                break;

            case '2':
                menu_remover(root);
                while(print_question("Deseja remover mais algum site?[s/N]: ") == 0)
                {
                    menu_remover(root);
                }
                break;

            case '3':
                menu_inserir_pchave(root);
                while (print_question("Deseja inserir palavras-chave em mais algum site?[s/N]: ") == 0)
                {
                    menu_inserir_pchave(root);
                }
                break;

            case '4':
                menu_atualizar_relevancia(root);
                while (print_question("Deseja atualizar a relevancia de mais algum site?[s/N]: ") == 0)
                {
                    menu_atualizar_relevancia(root);
                }
                break;

            case '5':
                menu_busca_palavra(root);
                while (print_question("Deseja realizar mais alguma busca?[s/N]: ") == 0)
                {
                    menu_busca_palavra(root);
                }
                break;

            case '6':
                escolha = -1;
                FILE *a = fopen("googlebot.txt", "w");
                avlsite_inorder_file(root, a);
                fclose(a);
                avlsite_free(&root);
                break;

            default:
                break;
        }
    }
}

void menu_inserir(AVL_SITE **root)
{
    SITE *new_s = NULL;
    KEYWORDS *new_k = NULL;
    unsigned int codigo = 0, relevancia = 0, num_keywords = 0;
    char nome[50], link[100], *tmp_palavras = NULL, *palavras = NULL, *addr_palavras = NULL;
    palavras = (char *) malloc(sizeof(char) * 500);
    tmp_palavras = (char *) malloc(sizeof(char) * 50);
    addr_palavras = palavras;
    if(palavras == NULL)
    {
        printf("NAO FOI POSSIVEL ALOCAR ESPACO PARA AS PALAVRAS CHAVE\n");
        return;
    }
    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tInserir novo site \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");
    printf("\nDigite o codigo do site: ");
    scanf("%u", &codigo);
    new_s = avlsite_search((*root), codigo);
    if(new_s == NULL)
    {
        printf("\nDigite o nome do site: ");
        scanf(" %[^\n]s", nome);
        printf("\nDigite o link para o site: ");
        scanf("%s", link);
        printf("\nDigite a relevancia que o site tera: ");
        scanf("%u", &relevancia);
        printf("\nDigite as palavras chaves separadas por virgula (max. 10): ");
        scanf("%s", palavras);
        sscanf(palavras, " %[^,]s", tmp_palavras);
        new_k = avlkeywords_create(tmp_palavras);
        num_keywords += 1;
        palavras = strchr(palavras, ',');
        while(palavras != NULL && num_keywords <= 10)
        {
            sscanf(++palavras, " %[^,]s", tmp_palavras);
            avlkeywords_insert_node(&new_k, tmp_palavras);
            num_keywords += 1;
            palavras = strchr(palavras, ',');
        }
        new_s = site_create(codigo, nome, relevancia, link, new_k, num_keywords);
        avlsite_insert_node(root, new_s);
    }
    else
    {
        printf("\nEsse codigo ja existe!\n");
    }
    free(addr_palavras);
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

void menu_remover(AVL_SITE *root)
{
    unsigned int cod = 0;
    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tSites cadastrados \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");
    if(root != NULL)
    {
        avlsite_inorder(root);
        printf("\n\nDigite o codigo do site que deseja remover: ");
        scanf("%u", &cod);
        if(avlsite_search(root, cod) != NULL)
        {
            avlsite_remove_node(&root, cod);
        }
        else
        {
            printf("\nO site nao esta cadastrado!\n");
        }
    }
    else
    {
        printf("Voce nao cadastrou nenhum site!\n");
    }
}

void menu_inserir_pchave(AVL_SITE *root)
{
    KEYWORDS **k_tmp = NULL;
    SITE *tmp = NULL;
    char *w = NULL, *addr_w = NULL, *keyword;
    unsigned int cod = 0, nword = 1;
    w = (char *) malloc(sizeof(char) * 300);
    keyword = (char *) malloc(sizeof(char) * 50);
    addr_w = w;
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tSites cadastrados \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");
    if(root != NULL)
    {
        avlsite_inorder(root);
        printf("\n\nDigite o codigo do site que deseja inserir a(s) palavra(s)-chave: ");
        scanf("%u", &cod);
        tmp = avlsite_search(root, cod);
        if(tmp != NULL)
        {
            printf("\nDigite as palavra(s)-chave separadas por virgula (max. %u): ", abs(site_get_nkeywords(tmp) - 10));
            scanf("%s", w);
            while((w = strchr(w, ',')) != NULL)
            {
                nword += 1;
                ++w;
            }
            if(abs((site_get_nkeywords(tmp) - nword)) <= 10)
            {
                w = addr_w;
                k_tmp = site_get_keywords(tmp);
                sscanf(w, " %[^,]s", keyword);
                avlkeywords_insert_node(k_tmp, keyword);
                w = strchr(w, ',');
                while(w != NULL)
                {
                    sscanf(++w, " %[^,]s", keyword);
                    avlkeywords_insert_node(k_tmp, keyword);
                    w = strchr(w, ',');
                }
                nword += site_get_nkeywords(tmp);
                site_update_nkeywords(tmp, nword);
            }
            else
            {
                printf("O site so pode ter no max. 10 palavras-chave!\n");

            }
        }
        else
        {
            printf("\n\nNenhum site corresponde ao codigo digitado!");
        }
    }
    else
    {
        printf("\n\nNenhum site esta cadastrado!");
    }
    free(addr_w);
}

void menu_atualizar_relevancia(AVL_SITE *root)
{
    SITE *tmp = NULL;
    unsigned int cod = 0, relevancia = 0;
    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tSites cadastrados \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");
    if(root != NULL)
    {
        avlsite_inorder(root);
        printf("\n\nDigite o codigo do site que deseja atualizar a relevancia: ");
        scanf("%u", &cod);
        tmp = avlsite_search(root, cod);
        if(tmp != NULL)
        {
            printf("\nDigite o novo valor que a relevancia do site tera: ");
            scanf("%u", &relevancia);
            site_update_relevance(tmp, relevancia);
        }
        else
        {
            printf("\n\nNenhum site corresponde ao codigo digitado!");
        }
    }
    else
    {
        printf("\n\nNenhum site esta cadastrado!");
    }
}

void menu_busca_palavra(AVL_SITE *root)
{
    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\tBusca por palavra-chave \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");
    avlsite_postorder(root);
}
