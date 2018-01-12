/************************************************************************************
 * Transfer array to binary tree
 ***********************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct binary_tree_t {
    uint8_t val;
    struct binary_tree_t* pleft;
    struct binary_tree_t* pright;
};

typedef struct binary_tree_t binary_tree_t;
typedef enum {
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
} print_order_e;

binary_tree_t* add_node(binary_tree_t* tree, uint8_t val)
{
    binary_tree_t* cur_node;

    cur_node = (binary_tree_t*)calloc(1, sizeof(binary_tree_t));

    if (tree == NULL) { // add a new tree
        cur_node->val = val;
        cur_node->pleft = NULL;
        cur_node->pright = NULL;
        return cur_node;
    }

    if (val < tree->val) {
        if (tree->pleft == NULL) {
            tree->pleft = cur_node;
            tree->pleft->val = val;
            tree->pleft->pleft = NULL;
            tree->pleft->pright = NULL;
        } else {
            add_node(tree->pleft, val);
        }
    } else {
        if (tree->pright == NULL) {
            tree->pright = cur_node;
            tree->pright->val = val;
            tree->pright->pleft = NULL;
            tree->pright->pright = NULL;
        } else {
            add_node(tree->pright, val);
        }
    }

    return tree;
}

binary_tree_t* search_node(binary_tree_t* tree, uint8_t val)
{
    if (tree == NULL) {
        return NULL;
    }

    if (val == tree->val) {
        return tree;
    } else {
        if (val < tree->val) {
            search_node(tree->pleft, val);
        } else {
            search_node(tree->pright, val);
        }
    }
}

void delete_node(binary_tree_t* tree)
{
    if (tree != NULL) {
        delete_node(tree->pleft);
        delete_node(tree->pright);
        free(tree);
    }
}

void print_tree(binary_tree_t* tree, print_order_e order)
{
    if (tree == NULL) {
        return;
    }

    if (order == ORDER_PRE) { // travelsal binary tree using pre-order
        printf("%d ", tree->val);
        print_tree(tree->pleft, order);
        print_tree(tree->pright, order);
    } else if (order == ORDER_IN) { // travelsal binary tree using in-order
        print_tree(tree->pleft, order);
        printf("%d ", tree->val);
        print_tree(tree->pright, order);
    } else if (order == ORDER_POST) { // travelsal binary tree using post-order
        print_tree(tree->pleft, order);
        print_tree(tree->pright, order);
        printf("%d ", tree->val);
    }
}

uint8_t get_tree_level(binary_tree_t* tree)
{
    uint8_t left_level, right_level;

    if (tree == NULL) {
        return 0;
    }

    left_level = get_tree_level(tree->pleft) + 1;
    right_level = get_tree_level(tree->pright) + 1;

    if (left_level > right_level) {
        return left_level;
    } else {
        return right_level;
    }
}

int main(int argc, char* argv[])
{
    uint8_t i, len = 100, target = 18;
    binary_tree_t *root_node = NULL, *tmp_node;
    uint8_t array[] = { 10, 6, 15, 3, 7, 12, 20, 2, 1 };

    //  for (i = 0; i < len; i += 1) {
    for (i = 0; i < sizeof(array) / sizeof(array[0]); i += 1) {
        //  root_node = add_node(root_node, 2 * i + 128);
        root_node = add_node(root_node, array[i]);
    }
    print_tree(root_node, ORDER_PRE);
    printf("max level=%d\n", get_tree_level(root_node));
    tmp_node = search_node(root_node, target);
    if (tmp_node == NULL) {
        printf("Failed, %d is not in the binary tree\n", target);
    } else {
        printf("Success find %d in the binary tree\n", target);
    }
    delete_node(root_node);

    return 0;
}
