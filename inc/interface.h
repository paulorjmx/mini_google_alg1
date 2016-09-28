#ifndef INTERFACE_H
    #define INTERFACE_H
        #include "list.h"

        void menu(LIST *l);
        void menu_inserir(LIST *l);
        void menu_remover(LIST *l);
        void menu_inserir_pchave(LIST *l);
        void menu_atualizar_relevancia(LIST *l);
        LIST *get_from_file(char *file_name);
#endif
