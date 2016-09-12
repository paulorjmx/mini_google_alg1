#ifndef KEYWORDS_H
    #define KEYWORDS_H

    typedef struct keywords KEYWORDS;

    KEYWORDS *create_keywords();
    void insert_keyword(KEYWORDS *begin, char *word);
    void destroy_keywords(KEYWORDS *begin);
#endif
