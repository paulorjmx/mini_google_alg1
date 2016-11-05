#ifndef SITE_H
    #define SITE_H
        #include "avltree_keywords.h"

        typedef struct site SITE;

        SITE *site_create(unsigned int code, char *nome, unsigned int relevance, char *link, KEYWORDS *k, unsigned int num_keywords);
        KEYWORDS *site_get_keywords(SITE *s);
        unsigned int site_get_code(SITE *s);
        unsigned int site_get_nkeywords(SITE *s);
        void site_free(SITE **s);
        void site_to_string(SITE *s);
#endif
