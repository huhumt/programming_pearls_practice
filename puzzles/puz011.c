/****************************************************************************************************
 * Linked List Reverse Printing Challenge
 *
 * write the cleanest possible function you can think of to print a singly linked list in reverse.
 * The format for the node should be a struct containing an integer value, val,
 * and a next pointer to the following node.
 ******************************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct single_list_t {
    uint8_t val;
    uint8_t node_num;
    struct single_list_t* pnext;
};

void swap(uint8_t* x, uint8_t* y)
{
    uint8_t tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

struct single_list_t* creat_list(uint8_t len)
{
    uint8_t i;
    struct single_list_t *root_node, *pre_node, *cur_node;

    root_node = (struct single_list_t*)calloc(1, sizeof(struct single_list_t));
    pre_node = root_node;
    for (i = 1; i < len; i += 1) {
        cur_node = (struct single_list_t*)calloc(1, sizeof(struct single_list_t));
        pre_node->node_num = i - 1;
        pre_node->pnext = cur_node;
        pre_node = cur_node;
    }
    cur_node->node_num = i - 1;
    cur_node->pnext = NULL;

    return root_node;
}

void delete_list(struct single_list_t* root_node, uint8_t len)
{
    uint8_t i;
    struct single_list_t *cur_node, *next_node;

    cur_node = root_node;
    for (i = 0; i < len; i += 1) {
        next_node = cur_node->pnext;
        cur_node->pnext = NULL;
        free(cur_node);
        cur_node = next_node;
    }
}

/* sort list by element in ascending/descending order */
void sort_list(struct single_list_t* root_node, uint8_t len, uint8_t order)
{
    uint8_t flag;
    struct single_list_t *cur_node, *next_node;

    if (root_node == NULL) {
        return;
    }

    while (1) {
        flag = 1;
        cur_node = root_node;
        next_node = cur_node->pnext;

        while (cur_node->pnext != NULL) {
            if (order) { // ascending order
                if (cur_node->val > next_node->val) {
                    flag = 0;
                    swap(&(cur_node->val), &(next_node->val));
                }
            } else { // descending order
                if (cur_node->val < next_node->val) {
                    flag = 0;
                    swap(&(cur_node->val), &(next_node->val));
                }
            }
            cur_node = next_node;
            next_node = next_node->pnext;
        }

        if (flag) {
            return;
        }
    }
}

void reverse_list(struct single_list_t* root_node, uint8_t len)
{
    uint8_t i, j, tmp;
    struct single_list_t *cur_node, *next_node;

    for (i = 0; i < len - 1; i += 1) {
        cur_node = root_node;
        next_node = cur_node->pnext;
        for (j = 0; j < len - 1 - i; j += 1) {
            swap(&(cur_node->val), &(next_node->val));
            cur_node = next_node;
            next_node = next_node->pnext;
        }
    }
}

void print_list(struct single_list_t* root_node)
{
    struct single_list_t* tmp_node = root_node;

    if (root_node == NULL) {
        return;
    }

    while (1) {
        printf("node info (%d %d)\n", tmp_node->node_num, tmp_node->val);
        if (tmp_node->pnext == NULL) {
            return;
        } else {
            tmp_node = tmp_node->pnext;
        }
    }
}

void insert_node(struct single_list_t** root_node, uint8_t* len, uint8_t index)
{
    struct single_list_t *new_node, *tmp_node;

    if (*root_node == NULL) {
        return;
    }

    new_node = (struct single_list_t*)calloc(1, sizeof(struct single_list_t));
    if (new_node == NULL) {
        printf("Fail to allocate memory when insert a node.\n");
        return;
    }

    if (index == 0) { // insert a root node
        new_node->pnext = *root_node;
        new_node->node_num = 0;
        *root_node = new_node;

        tmp_node = new_node->pnext;
        while (tmp_node->pnext != NULL) {
            tmp_node->node_num += 1;
            tmp_node = tmp_node->pnext;
        }
        tmp_node->node_num += 1;
    } else if (index >= *len) { // insert at tail
        tmp_node = *root_node;
        while (tmp_node->pnext != NULL) {
            tmp_node = tmp_node->pnext;
        }
        tmp_node->pnext = new_node;
        new_node->pnext = NULL;
        new_node->node_num = tmp_node->node_num + 1;
    } else { // insert at middle
        tmp_node = *root_node;
        while (tmp_node->node_num != index - 1) {
            tmp_node = tmp_node->pnext;
        }
        new_node->pnext = tmp_node->pnext;
        new_node->node_num = tmp_node->node_num + 1;
        tmp_node->pnext = new_node;

        tmp_node = new_node->pnext;
        while (tmp_node->pnext != NULL) {
            tmp_node->node_num += 1;
            tmp_node = tmp_node->pnext;
        }
        tmp_node->node_num += 1;
    }
    *len += 1;
}

void delete_node(struct single_list_t** root_node, uint8_t* len, uint8_t index)
{
    uint8_t i;
    struct single_list_t *del_node, *tmp_node;

    if (*root_node == NULL) {
        return;
    }

    if (index >= *len) {
        return;
    }

    if (index == 0) { // delete root node
        del_node = *root_node;
        *root_node = (*root_node)->pnext;

        tmp_node = *root_node;
        while (tmp_node->pnext != NULL) {
            tmp_node->node_num -= 1;
            tmp_node = tmp_node->pnext;
        }
        tmp_node->node_num -= 1;
    } else if (index == *len - 1) { // delete tail node
        tmp_node = *root_node;
        while (tmp_node->node_num != *len - 2) {
            tmp_node = tmp_node->pnext;
        }
        del_node = tmp_node->pnext;
        tmp_node->pnext = NULL;
    } else { // delete middle node
        tmp_node = *root_node;
        while (tmp_node->node_num != index - 1) {
            tmp_node = tmp_node->pnext;
        }
        del_node = tmp_node->pnext;
        tmp_node->pnext = del_node->pnext;

        tmp_node = tmp_node->pnext;
        while (tmp_node->pnext != NULL) {
            tmp_node->node_num -= 1;
            tmp_node = tmp_node->pnext;
        }
        tmp_node->node_num -= 1;
    }

    *len -= 1;
    del_node->pnext = NULL;
    free(del_node);
}

void set_node_val(struct single_list_t* root_node, uint8_t index, uint8_t val)
{
    struct single_list_t* tmp_node = root_node;

    if (root_node == NULL) {
        return;
    }

    while (tmp_node->node_num != index) {
        if (tmp_node->pnext == NULL) {
            printf("index is out of range\n");
            return;
        } else {
            tmp_node = tmp_node->pnext;
        }
    }
    tmp_node->val = val;
}

int main(int argc, char* argv[])
{
    uint8_t i, len = 100;
    struct single_list_t* root_node;

    root_node = creat_list(len);
    for (i = 0; i < len; i += 1) {
        set_node_val(root_node, i, 2 * i + 128);
    }

    /* add node at head */
    insert_node(&root_node, &len, 0);
    set_node_val(root_node, 0, 99);
    /* add node at middle */
    insert_node(&root_node, &len, 23);
    set_node_val(root_node, 23, 77);
    /* add node at tail */
    insert_node(&root_node, &len, len - 1);
    set_node_val(root_node, len - 1, 55);

    delete_node(&root_node, &len, 0);
    delete_node(&root_node, &len, 24);
    delete_node(&root_node, &len, len - 1);

    sort_list(root_node, len, 1);
    reverse_list(root_node, len);

    print_list(root_node);

    delete_list(root_node, len);
    root_node = NULL;

    return 0;
}
