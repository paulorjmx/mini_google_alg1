#ifndef SITE_H
    #define SITE_H

        typedef struct site SITE;

        SITE *site_create(unsigned int code, char *nome, unsigned int relevance, char *link);
        unsigned int site_get_code(SITE *s);
        void site_free(SITE **s);
        void site_to_string(SITE *s);
#endif
