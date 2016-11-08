#include "inc/avltree_site.h"
#include <stdio.h>
#include <stdlib.h>

struct avl_site
{
    SITE *s;
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

AVL_SITE *avlsite_create(SITE *s)
{
    AVL_SITE *new = (AVL_SITE *) malloc(sizeof(AVL_SITE));
    if(new != NULL)
    {
        new->left = NULL;
        new->right = NULL;
        new->s = s;
        return new;
    }
    else
    {
        return NULL;
    }
}

void avlsite_inorder_file(AVL_SITE *root, FILE *arq)
{
    if(root != NULL)
    {
        avlsite_inorder_file(root->left, arq);
        site_to_file(root->s, arq);
        fseek(arq, -1, SEEK_CUR);
        fprintf(arq, "\n");
        avlsite_inorder_file(root->right, arq);
    }
    else
    {
        return;
    }
}

void avlsite_insert_node(AVL_SITE **root, SITE *s)
{
    if(site_get_code(s) < site_get_code((*root)->s))
    {
        if((*root)->left != NULL)
        {
            avlsite_insert_node(&(*root)->left, s);
        }
        else
        {
            (*root)->left = avlsite_create(s);
        }
    }
    else
    {
        if((*root)->right != NULL)
        {
            avlsite_insert_node(&(*root)->right, s);
        }
        else
        {
            (*root)->right = avlsite_create(s);
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
        if(site_get_code(s) > site_get_code((*root)->right->s))
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

void avlsite_insert_node_relevance(AVL_SITE **root, SITE *s)
{
    if(site_get_relevance(s) < site_get_relevance((*root)->s))
    {
        if((*root)->left != NULL)
        {
            avlsite_insert_node_relevance(&(*root)->left, s);
        }
        else
        {
            (*root)->left = avlsite_create(s);
        }
    }
    else
    {
        if((*root)->right != NULL)
        {
            avlsite_insert_node_relevance(&(*root)->right, s);
        }
        else
        {
            (*root)->right = avlsite_create(s);
        }
    }

    int fb = (avlsite_height((*root)->left) - avlsite_height((*root)->right));
    if(fb == 2)
    {
        if(site_get_relevance(s) < site_get_relevance((*root)->left->s))
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
        if(site_get_relevance(s) > site_get_relevance((*root)->right->s))
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
                site_free(&(*root)->s);
                free((*root));
                *root = NULL;
                return 0;
            }
            else
            {
                if((*root)->left == NULL)
                {
                    (*root)->s = (*root)->right->s;
                    site_free(&(*root)->right->s);
                    free((*root)->right);
                    (*root)->right = NULL;
                }
                else if((*root)->right == NULL)
                {
                    (*root)->s = (*root)->left->s;
                    site_free(&(*root)->left->s);
                    free((*root)->left);
                    (*root)->left = NULL;
                }
                else
                {
                    (*root)->s = avlsite_search_smaller_right((*root)->right);
                    avlsite_remove_node(&(*root)->right, site_get_code((*root)->s));
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
            return 0;
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
        return NULL;
    }
    else
    {
        if(site_get_code(root->s) == code)
        {
            return root->s;
        }
        else
        {
            if(code < site_get_code(root->s))
            {
                avlsite_search(root->left, code);
            }
            else
            {
                avlsite_search(root->right, code);
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

unsigned int avlsite_num_keywords(AVL_SITE *root)
{
    return site_get_nkeywords(root->s);
}

void avlsite_free(AVL_SITE **root)
{
    if((*root) != NULL)
    {
        avlsite_free(&(*root)->left);
        avlsite_free(&(*root)->right);
        site_free(&(*root)->s);
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
        site_to_string(root->s);
        printf("\n\n");
        avlsite_inorder(root->right);
    }
    else
    {
        return;
    }
}

void avlsite_search_keyword(AVL_SITE *root, AVL_SITE **result_tree, char *keyword)
{
    if(root != NULL)
    {
        avlsite_search_keyword(root->right, result_tree, keyword);
        if(site_search_keyword(root->s, keyword) == 0)
        {
            avlsite_insert_node_relevance(result_tree, root->s);
        }
        avlsite_search_keyword(root->left, result_tree, keyword);
    }
    else
    {
        return;
    }
}

void avlsite_postorder(AVL_SITE *root)
{
    if(root != NULL)
    {
        avlsite_postorder(root->right);
        site_to_string(root->s);
        printf("\n\n");
        avlsite_postorder(root->left);
    }
    else
    {
        return;
    }
}

void avlsite_free_onlynode(AVL_SITE **root)
{
    if((*root) != NULL)
    {
        avlsite_free_onlynode(&(*root)->right);
        avlsite_free_onlynode(&(*root)->left);
        free((*root));
        (*root) = NULL;
    }
    else
    {
        return;
    }
}
