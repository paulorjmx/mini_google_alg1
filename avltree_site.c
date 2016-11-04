#include "inc/avltree_site.h"
#include "inc/avltree_keywords.h"
#include <stdio.h>
#include <stdlib.h>

struct avl_site
{
    SITE *s;
    KEYWORDS *k_root;
    struct avl_site *left, *right;
};

int avlsite_height(AVL_SITE *root)
{
    if(root != NULL)
    {
        int hl = 0, hr = 0;
        hl = 1 + avlsite_height(root->left);
        hr = 1 + avlsite_height(root->right);
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

AVL_SITE *avlsite_create(SITE *s, KEYWORDS *k)
{
    AVL_SITE *new = (AVL_SITE *) malloc(sizeof(AVL_SITE));
    if(new != NULL)
    {
        new->left = NULL;
        new->right = NULL;
        new->s = s;
        new->k_root = k;
        return new;
    }
    else
    {
        return NULL;
    }
}

void avlsite_insert_node(AVL_SITE **root, SITE *s, KEYWORDS *k)
{
    if(site_get_code(s) < site_get_code((*root)->s))
    {
        if((*root)->left != NULL)
        {
            avlsite_insert_node(&(*root)->left, val);
        }
        else
        {
            (*root)->left = avlsite_create(val);
        }
    }
    else
    {
        if((*root)->right != NULL)
        {
            avlsite_insert_node(&(*root)->right, val);
        }
        else
        {
            (*root)->right = avlsite_create(val);
        }
    }

    int fb = (avlsite_height((*root)->left) - avlsite_height((*root)->right));
    if(fb == 2)
    {
        if(site_get_code(s) < site_get_code((*root)->left->s))
        {
            avlsite_rotate_right(root);
        }
        else
        {
            avlsite_rotate_left(&(*root)->left);
            avlsite_rotate_right(root);
        }
    }
    else if(fb == -2)
    {
        if(site_get_code(s) < site_get_code((*root)->right->s))
        {
            avlsite_rotate_left(root);
        }
        else
        {
            avlsite_rotate_right(&(*root)->right);
            avlsite_rotate_left(root);
        }
    }
}

int avlsite_remove_node(AVL_SITE **root, unsigned int code)
{
    if((*root) == NULL)
    {
        return -1;
    }
    else
    {
        if(site_get_code((*root)->s) == code)
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
                    (*root)->s = (*root)->right->s;
                    free((*root)->right);
                    (*root)->right = NULL;
                }
                else if((*root)->right == NULL)
                {
                    (*root)->s = (*root)->left->s;
                    free((*root)->left);
                    (*root)->left = NULL;
                }
                else
                {
                    (*root)->s = avlsite_search_smaller_right((*root)->right);
                    avlsite_remove_node(&(*root)->right, (*root)->s);
                }
            }
            int fb = (avlsite_height((*root)->left) - avlsite_height((*root)->right));
            if(fb == 2)
            {
                if((avlsite_height((*root)->left->left) - avlsite_height((*root)->left->right)) >= 0)
                    avlsite_rotate_right(root);
                else
                {
                    avlsite_rotate_left(&(*root)->left);
                    avlsite_rotate_right(root);
                }
            }
            else if(fb == -2)
            {
                if((avlsite_height((*root)->left->left) - avlsite_height((*root)->left->right)) <= 0)
                    avlsite_rotate_left(root);
                else
                {
                    avlsite_rotate_right(&(*root)->left);
                    avlsite_rotate_left(root);
                }
            }
        }
        else
        {
            if(site_get_code((*root)->s) > code)
                avlsite_remove_node(&(*root)->left, code);
            else
                avlsite_remove_node(&(*root)->right, code);
        }
    }
}

SITE *avlsite_search(AVL_SITE *root, unsigned int code)
{
    if(root == NULL)
    {
        return -1;
    }
    else
    {
        if(site_get_code(root->s) == code)
        {
            return root->s;
        }
        else
        {
            if(site_get_code(s) > code)
            {
                avlsite_search(root->right, code);
            }
            else
            {
                avlsite_search(root->left, code);
            }

        }
    }
}

SITE *avlsite_search_smaller_right(AVL_SITE *root)
{
    if(root->left == NULL)
    {
        return root->s;
    }
    else
    {
        avlsite_search_smaller_right(root->left);
    }
}

void avlsite_rotate_right(AVL_SITE **root)
{
    AVL_SITE *b = NULL;
    b = (*root)->left;
    (*root)->left = b->right;
    b->right = (*root);
    (*root) = b;
}

void avlsite_rotate_left(AVL_SITE **root)
{
    AVL_SITE *b = NULL;
    b = (*root)->right;
    (*root)->right = b->left;
    b->left = (*root);
    (*root) = b;
}

void avlsite_free(AVL_SITE **root)
{
    if(root != NULL)
    {
        avlsite_free(root->left);
        avlsite_free(root->right);
        free((*root));
        (*root) = NULL;
    }
    else
    {
        return;
    }
}

void avlsite_inorder(AVL_SITE *root)
{
    if(root != NULL)
    {
        avlsite_inorder(root->left);
        printf("%d\n", root->n);
        avlsite_inorder(root->right);
    }
    else
    {
        return;
    }
}
