#ifndef AVL_SITE_H
    #define AVL_SITE_H
        #include "site.h"
        // #include "avltree_keywords.h"

        typedef struct avl_site AVL_SITE;

        AVL_SITE *avlsite_create(SITE *s);
        void avlsite_insert_node(AVL_SITE **root, SITE *s);
        int avlsite_remove_node(AVL_SITE **root, unsigned int code);
        SITE *avlsite_search(AVL_SITE *root, unsigned int code);
        SITE *avlsite_search_smaller_right(AVL_SITE *root);
        void avlsite_free(AVL_SITE **root);
        void avlsite_inorder(AVL_SITE *root);
        void avlsite_inorder_file(AVL_SITE *root, FILE *arq);
        int avlsite_height(AVL_SITE *root);
        void avlsite_rotate_right(AVL_SITE **root);
        void avlsite_rotate_left(AVL_SITE **root);
#endif
