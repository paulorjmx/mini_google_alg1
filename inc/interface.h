#ifndef INTERFACE_H
    #define INTERFACE_H
        #include "avltree_site.h"
        #include "avltree_keywords.h"
        #include "site.h"

        void menu();
        // void menu_inserir();
        // void menu_remover();
        // void menu_inserir_pchave();
        // void menu_atualizar_relevancia();
        AVL_SITE *get_from_file(char *file_name);
#endif
