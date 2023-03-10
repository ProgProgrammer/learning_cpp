#include <iostream>
#include "bstree.h"

void Bstree::bstree_create(struct bstree* node, const int key, const int value)
{
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
}

void Bstree::bstree_add(struct bstree* tree, const int key, const int value)
{
    bstree* parent, * node;

    if (tree == NULL)
        return;

    for (parent = tree; tree != NULL; ) {
        parent = tree;
        if (value < tree->value)
            tree = tree->left;
        else if (value > tree->value)
            tree = tree->right;
        else
        {
            node = tree;
            return;
        }
    }

    node = new bstree;
    bstree_create(node, key, value);

    if (value < parent->value)
        parent->left = node;
    else
        parent->right = node;
}

void Bstree::startLoop(struct bstree* tree, const int arr[], const int count)
{
    bstree_create(tree, 0, arr[0]);

    for (int i = 0; i < count; ++i)
    {
        bstree_add(tree, i, arr[i]);
    }
}

int Bstree::bstree_lookup_key(struct bstree* tree, const int value)
{
    while (tree != NULL) {
        if (value == tree->value) 
        {
            return tree->key;
        }
        else if (value < tree->value) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
}

int Bstree::bstree_lookup_elem(struct bstree* tree, const int arr[], const int key)
{
    int value = arr[key];

    while (tree != NULL) {
        if (value == tree->value)
        {
            return tree->value;
        }
        else if (value < tree->value) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
}

int Bstree::bstree_max(struct bstree* tree)
{
    while (tree->right != NULL)
        tree = tree->right;

    return tree->value;
}

struct bstree* Bstree::bstree_remove(struct bstree* tree, const int value)
{
    if (tree == NULL)
        return tree;

    if (value == tree->value) {

        bstree* tmp;
        if (tree->right == NULL)
            tmp = tree->left;
        else {

            bstree* ptr = tree->right;
            if (ptr->left == NULL) {
                ptr->left = tree->left;
                tmp = ptr;
            }
            else {

                bstree* pmin = ptr->left;
                while (pmin->left != NULL) {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = tree->left;
                pmin->right = tree->right;
                tmp = pmin;
            }
        }

        delete tree;
        return tmp;
    }
    else if (value < tree->value)
        tree->left = bstree_remove(tree->left, value);
    else
        tree->right = bstree_remove(tree->right, value);

    return tree;
}