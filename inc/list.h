#ifndef LIST_H
    #define LIST_H

        typedef struct list LIST;

        LIST *create_list();
        void insert_node(LIST *l, unsigned int code, char nome[], unsigned int relevancia, char link[]);
        void update_relevance(LIST *begin, unsigned int relevancia, unsigned int cod);
        void remove_site(LIST *begin, unsigned cod);
        void erase_list(LIST *begin);
#endif
