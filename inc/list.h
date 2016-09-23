#ifndef LIST_H
    #define LIST_H
        #include "keywords.h"
        typedef struct list LIST;

        LIST *create_list();
        void insert_site(LIST *l, unsigned int codigo, char nome[], unsigned int relevancia, char link[], KEYWORDS *palavrachave);
        void update_relevance(LIST *l, unsigned int relevancia, unsigned int cod);
        void remove_site(LIST *l, unsigned cod);
        void erase_list(LIST *l);
        unsigned int get_last_cod(LIST *l);
        void print_list(LIST *l);
#endif
