#pragma once

struct bstree {
    int key;
    int value;
    struct bstree* left, * right;
};

class Bstree
{
private:
    bstree * bst = new bstree;
    void bstree_create(struct bstree* node, const int key, const int value);
    void bstree_add(struct bstree* tree, const int key, const int value);

public:
    void startLoop(struct bstree* tree, const int arr[], const int count);
    int bstree_lookup_key(struct bstree* tree, const int value);
    int bstree_lookup_elem(struct bstree* tree, const int arr[], const int value);
    int bstree_max(struct bstree* tree);
    struct bstree* bstree_remove(struct bstree* tree, const int value);
};