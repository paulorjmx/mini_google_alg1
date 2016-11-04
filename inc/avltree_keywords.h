#ifndef KEYWORDS_H
    #define KEYWORDS_H

        typedef struct avl_keywords KEYWORDS;

        KEYWORDS *KEYWORDS_create(char *keyword);
        void avlkeywords_insert_node(KEYWORDS **root, char *keyword);
        int avlkeywords_remove_node(KEYWORDS **root, char *keyword);
        char *avlkeywords_search(KEYWORDS *root, char *keyword);
        char *avlkeywords_search_smaller_right(KEYWORDS *root);
        void avlkeywords_free(KEYWORDS **root);
        void avlkeywords_inorder(KEYWORDS *root);
        int avlkeywords_height(KEYWORDS *root);
        void avlkeywords_rotate_right(KEYWORDS **root);
        void avlkeywords_rotate_left(KEYWORDS **root);
#endif
