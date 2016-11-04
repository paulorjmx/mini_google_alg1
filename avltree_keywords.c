#include "inc/avltree_keywords.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct avl_keywords
{
    char keyword[50];
    struct avl_keywords *left, *right;
};

int avlkeywords_height(KEYWORDS *root)
{
    if(root != NULL)
    {
        int hl = 0, hr = 0;
        hl = 1 + avlkeywords_height(root->left);
        hr = 1 + avlkeywords_height(root->right);
        if(hl > hr)
            return hl;
        else
            return hr;
    }
    else
    {
        return -1;
    }
}

KEYWORDS *avlkeywords_create(char *keyword)
{
    KEYWORDS *new = (KEYWORDS *) malloc(sizeof(KEYWORDS));
    if(new != NULL)
    {
        new->left = NULL;
        new->right = NULL;
        strcpy(new->keyword, keyword);
        return new;
    }
    else
    {
        return NULL;
    }
}

void avlkeywords_insert_node(KEYWORDS **root, char *keyword)
{
    if(strcmp(keyword, (*root)->keyword) < 0)
    {
        if((*root)->left != NULL)
        {
            avlkeywords_insert_node(&(*root)->left, keyword);
        }
        else
        {
            (*root)->left = avlkeywords_create(keyword);
        }
    }
    else
    {
        if((*root)->right != NULL)
        {
            avlkeywords_insert_node(&(*root)->right, keyword);
        }
        else
        {
            (*root)->right = avlkeywords_create(keyword);
        }
    }

    int fb = (avlkeywords_height((*root)->left) - avlkeywords_height((*root)->right));
    if(fb == 2)
    {
        if(strcmp(keyword, (*root)->left->keyword) < 0)
        {
            avlkeywords_rotate_right(root);
        }
        else
        {
            avlkeywords_rotate_left(&(*root)->left);
            avlkeywords_rotate_right(root);
        }
    }
    else if(fb == -2)
    {
        if(strcmp(keyword, (*root)->right->keyword) > 0)
        {
            avlkeywords_rotate_left(root);
        }
        else
        {
            avlkeywords_rotate_right(&(*root)->right);
            avlkeywords_rotate_left(root);
        }
    }
}

int avlkeywords_remove_node(KEYWORDS **root, char *keyword)
{
    if((*root) == NULL)
    {
        return -1;
    }
    else
    {
        if(strcmp((*root)->keyword, keyword) == 0)
        {
            if((*root)->left == NULL && (*root)->right == NULL)
            {
                free((*root));
                (*root) = NULL;
                return 0;
            }
            else
            {
                if((*root)->left == NULL)
                {
                    strcpy((*root)->keyword, (*root)->right->keyword);
                    free((*root)->right);
                    (*root)->right = NULL;
                }
                else if((*root)->right == NULL)
                {
                    strcpy((*root)->keyword, (*root)->left->keyword);
                    free((*root)->left);
                    (*root)->left = NULL;
                }
                else
                {
                    strcpy((*root)->keyword, avlkeywords_search_smaller_right((*root)->right));
                    avlkeywords_remove_node(&(*root)->right, (*root)->keyword);
                }
            }
            int fb = (avlkeywords_height((*root)->left) - avlkeywords_height((*root)->right));
            if(fb == 2)
            {
                if((avlkeywords_height((*root)->left->left) - avlkeywords_height((*root)->left->right)) >= 0)
                    avlkeywords_rotate_right(root);
                else
                {
                    avlkeywords_rotate_left(&(*root)->left);
                    avlkeywords_rotate_right(root);
                }
            }
            else if(fb == -2)
            {
                if((avlkeywords_height((*root)->left->left) - avlkeywords_height((*root)->left->right)) <= 0)
                    avlkeywords_rotate_left(root);
                else
                {
                    avlkeywords_rotate_right(&(*root)->left);
                    avlkeywords_rotate_left(root);
                }
            }
        }
        else
        {
            if((*root)->keyword > keyword)
                avlkeywords_remove_node(&(*root)->left, keyword);
            else
                avlkeywords_remove_node(&(*root)->right, keyword);
        }
    }
}

char *avlkeywords_search(KEYWORDS *root, char *keyword)
{
    if(root == NULL)
    {
        return NULL;
    }
    else
    {
        if(strcmp(root->keyword, keyword) == 0)
        {
            return root->keyword;
        }
        else
        {
            if(strcmp(keyword, root->keyword) > 0)
            {
                avlkeywords_search(root->right, keyword);
            }
            else
            {
                avlkeywords_search(root->left, keyword);
            }

        }
    }
}

char *avlkeywords_search_smaller_right(KEYWORDS *root)
{
    if(root->left == NULL)
    {
        return root->keyword;
    }
    else
    {
        avlkeywords_search_smaller_right(root->left);
    }
}

void avlkeywords_rotate_right(KEYWORDS **root)
{
    KEYWORDS *b = NULL;
    b = (*root)->left;
    (*root)->left = b->right;
    b->right = (*root);
    (*root) = b;
}

void avlkeywords_rotate_left(KEYWORDS **root)
{
    KEYWORDS *b = NULL;
    b = (*root)->right;
    (*root)->right = b->left;
    b->left = (*root);
    (*root) = b;
}

void avlkeywords_free(KEYWORDS **root)
{
    if((*root) != NULL)
    {
        avlkeywords_free(&(*root)->left);
        avlkeywords_free(&(*root)->right);
        free((*root));
        (*root) = NULL;
    }
    else
    {
        return;
    }
}

void avlkeywords_inorder(KEYWORDS *root)
{
    if(root != NULL)
    {
        avlkeywords_inorder(root->left);
        printf("%s, ", root->keyword);
        avlkeywords_inorder(root->right);
    }
    else
    {
        return;
    }
}
