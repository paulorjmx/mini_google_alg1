#ifndef LIST_H
    #define LIST_H
        typedef struct list LIST;

        LIST *create_list();
        void insert_site(LIST *l, unsigned int codigo, char nome[], unsigned int relevancia, char link[], char *palavras_chave);
        void update_relevance(LIST *l, unsigned int relevancia, unsigned int cod);
        void remove_site(LIST *l, unsigned cod);
        void erase_list(LIST *l);
        unsigned int get_last_cod(LIST *l);
        void print_list(LIST *l);
        unsigned int nwords(LIST *l, unsigned int code);
        unsigned int count_words(const char *words);
        void update_pchave(LIST *l, unsigned int code, char *palavras_chave);
        void write_on_file(LIST *l, const char *file_name);
#endif
