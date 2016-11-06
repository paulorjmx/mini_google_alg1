#ifndef INTERFACE_H
    #define INTERFACE_H
        #include "avltree_site.h"
        #include "avltree_keywords.h"
        #include "site.h"

        void menu();
        void menu_inserir(AVL_SITE **root);
        void menu_remover(AVL_SITE *root);
        void menu_inserir_pchave(AVL_SITE *root);
        void menu_atualizar_relevancia(AVL_SITE *root);
        void menu_busca_palavra(AVL_SITE *root);
        AVL_SITE *get_from_file(char *file_name);
#endif
