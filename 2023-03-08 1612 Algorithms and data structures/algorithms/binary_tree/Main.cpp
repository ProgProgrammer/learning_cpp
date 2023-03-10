#include <iostream>
#include "class/bstree.h"

int main()
{
    struct bstree* tree = new bstree;
    const int count = 15;
    const int search_count = 3;
    int arr[count] = { 47, 40, 22, 61, 95, 9, 93, 39, 43, 38, 59, 25, 60, 71, 32 };
    int arr_search_elem[search_count] = {38, 60, 32};
    int arr_search_keys[search_count] = {9, 12, 14};
    Bstree bstree;
    bstree.startLoop(tree, arr, count);

    std::cout << "Search by value." << std::endl;

    for (int i = 0; i < search_count; ++i)
    {
        int key = bstree.bstree_lookup_key(tree, arr_search_elem[i]);
        std::cout << "Element " << arr_search_elem[i] << " has key " << key << std::endl;
    }

    int elem = bstree.bstree_max(tree);
    std::cout << std::endl << "Max element = " << elem << std::endl;

    std::cout << std::endl << "Search by key." << std::endl;;

    for (int i = 0; i < search_count; ++i)
    {
        int element = bstree.bstree_lookup_elem(tree, arr, arr_search_keys[i]);
        std::cout << "Key " << i << " has element " << element << std::endl;
    }

    tree = bstree.bstree_remove(tree, 47);
    tree = bstree.bstree_remove(tree, 22);
    tree = bstree.bstree_remove(tree, 61);

    std::cout << std::endl << "Delete applied." << std::endl;

    const int count_res = 12;
    int arr_res[count_res] = { 40, 95, 9, 93, 39, 43, 38, 59, 25, 60, 71, 32 };

    for (int i = 0; i < 12; ++i)
    {
        int key = bstree.bstree_lookup_key(tree, arr_res[i]);
        std::cout << "Element " << arr_res[i] << " has key " << key << std::endl;
    }

    delete tree;
    system("pause");
}
