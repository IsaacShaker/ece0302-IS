
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include <cassert>
#include <cstdlib>
#include <stack>

template <typename KeyType, typename ItemType>
class BinarySearchTree {
   public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& rhs);
    BinarySearchTree& operator=(BinarySearchTree rhs);
    ~BinarySearchTree();

    void swap(BinarySearchTree& rhs);
    bool insert(const KeyType& key, const ItemType& item);
    bool isEmpty();
    bool retrieve(const KeyType& key, ItemType& item);
    bool remove(KeyType key);
    void destroy();
    void treeSort(KeyType arr[], int size);

   private:
    template <typename K, typename I>
    struct Node {
        I data;
        K key;
        Node<K, I>* left = 0;
        Node<K, I>* right = 0;
    };

    template <typename K, typename I>
    struct stackvar {
        Node<K, I>* rhs;
        Node<K, I>** lhs;
    };

    Node<KeyType, ItemType>* root;

    void inorder(Node<KeyType, ItemType>* curr, Node<KeyType, ItemType>*& in,
                 Node<KeyType, ItemType>*& parent);

    void search(KeyType key, Node<KeyType, ItemType>*& curr,
                Node<KeyType, ItemType>*& parent);
};

#include "binary_search_tree.tpp"

#endif  // _BINARY_SEARCH_TREE_H_
