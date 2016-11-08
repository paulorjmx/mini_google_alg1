#ifndef SITE_H
    #define SITE_H
        #include "avltree_keywords.h"
        #include <stdio.h>

        typedef struct site SITE;

        SITE *site_create(unsigned int code, char *nome, unsigned int relevance, char *link, KEYWORDS *k, unsigned int num_keywords);
        KEYWORDS **site_get_keywords(SITE *s);
        unsigned int site_get_code(SITE *s);
        unsigned int site_get_nkeywords(SITE *s);
        unsigned int site_get_relevance(SITE *s);
        int site_search_keyword(SITE *s, char *keyword);
        void site_update_nkeywords(SITE *s, unsigned int num_keywords);
        void site_update_relevance(SITE *s, unsigned int relevance);
        void site_free(SITE **s);
        void site_to_string(SITE *s);
        void site_to_file(SITE *s, FILE *arq);
#endif
