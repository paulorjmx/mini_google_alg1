#ifndef LIST_H
    #define LIST_H

        typedef struct list LIST;

        LIST *create_list();
        void add_node(LIST *begin, char *cod, char *nome, unsigned int relevancia, char *link, KEYWORDS *keywords);
        void erase_list(LIST *begin);
#endif
