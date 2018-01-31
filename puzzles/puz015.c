/********************************************************************************************
 * This is an implementation of AVL binary tree
 *******************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AVL_tree_t {
    uint16_t val;              // key value
    uint16_t height;           // max levl
    struct AVL_tree_t* pleft;  // pointer to left leaf
    struct AVL_tree_t* pright; // pointer to right leaf
};

typedef struct AVL_tree_t AVL_tree_t;

static uint16_t get_height(AVL_tree_t *tree)
{
    uint16_t left_height, right_height;

    if (tree == NULL) {
        return 0;
    } else {
        left_height = get_height(tree->pleft) + 1;
        right_height = get_height(tree->pright) + 1;
    }

    if (left_height > right_height) {
        return left_height;
    } else {
        return right_height;
    }
}

/* left rotation tree, A-B-C to B-A-C in pre-order */
static AVL_tree_t* left_rot_tree(AVL_tree_t* tree)
{
    AVL_tree_t *tmp_tree;

    tmp_tree = tree->pright;
    tree->pright = tmp_tree->pleft;
    tmp_tree->pleft = tree;

    tmp_tree->height = get_height(tmp_tree);
    tmp_tree->pleft->height = get_height(tmp_tree->pleft);

    return tmp_tree;
}

/* right rotation tree, A-B-C to C-B-A in pre-order */
static AVL_tree_t* right_rot_tree(AVL_tree_t* tree)
{
}

/* first left rotation tree, A-B-C to A-C-B in pre-order
 * then right rotation tree, A-C-B to B-C-A in pre-order */
static AVL_tree_t* left_right_rot_tree(AVL_tree_t* tree)
{
    tree = left_rot_tree(tree);
    tree = right_rot_tree(tree);
    return tree;
}

/* first right rotation tree, A-B-C to A-C-B
 * then left rotation tree, A-C-B to A-C-B */
static AVL_tree_t* right_left_rot_tree(AVL_tree_t* tree)
{
    tree = right_rot_tree(tree);
    tree = left_rot_tree(tree);
    return tree;
}

/* when add/delete a node, need reblance tree */
static AVL_tree_t* reblance_tree(AVL_tree_t* tree)
{
}

/* add a node to the tree based on its value
 * if given a NULL tree, create a new tree */
AVL_tree_t* add_node(AVL_tree_t* tree, uint16_t val)
{
    if (tree == NULL) {
        tree = (AVL_tree_t*)calloc(1, sizeof(AVL_tree_t));
        if (tree == NULL) {
            printf("fail to allocate memory to add a new node");
            return NULL;
        }
        tree->pleft = NULL;
        tree->pright = NULL;
    } else if (val < tree->val) { // add at left
        tree->pleft = add_node(tree->pleft, val);
    } else { // add at right
        tree->pright = add_node(tree->pright, val);
    }

    return tree;
}

/* search node based on its value */
AVL_tree_t* search_node(AVL_tree_t* tree, uint16_t val)
{
    if (tree == NULL) {
        return NULL;
    } else if (val == tree->val) {
        return tree;
    } else if (val < tree->val) {
        search_node(tree->pleft, val);
    } else {
        search_node(tree->pright, val);
    }
}

/* delete given node */
AVL_tree_t* del_node(AVL_tree_t* tree)
{
    if (tree != NULL) {
        del_node(tree->pleft);
        del_node(tree->pright);
        free(tree);
    }
}
