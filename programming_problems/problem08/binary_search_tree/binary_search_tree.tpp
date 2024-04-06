#include "binary_search_tree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree() {
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs) {
    root = 0;
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs.root;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> rhs) {
    swap(rhs);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType>& rhs) {
    std::swap(root, rhs.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree() {
    destroy();
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy() {
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item) {
    Node<KeyType, ItemType>* newNode = new Node<KeyType, ItemType>;
    newNode->key = key;
    newNode->data = item;

    if (isEmpty()) {
        root = newNode;
        return true;
    }

    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    // 2 possibilities
    // 1.) already exists (don't add because duplicate)
    if (key == curr->key) {
        delete newNode;
        return false;
    }
    // 2.) one of curr's leaves is null ptr and that is where it will be inserted
    if (key < curr->key) {
        curr->left = newNode;
    } else {
        curr->right = newNode;
    }

    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty() {
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item) {
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    // if curr is nullptr // empty tree
    if (curr == 0)
        return false;

    // if search was successful
    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key) {
    if (isEmpty())
        return false;  // empty tree

    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    // key not found
    if (curr->key != key) {
        return false;
    }

    // case, found deleted item at leaf
    if (curr->left == 0 && curr->right == 0) {
        if (curr == root) {
            root = 0;
        } else if (curr_parent->left == curr) {
            curr_parent->left = 0;
        } else {
            curr_parent->right = 0;
        }
    }
    // case, item to delete has only a left child
    else if (curr->right == 0) {
        if (curr == root) {
            root = curr->left;
        } else if (curr_parent->left == curr) {
            curr_parent->left = curr->left;
        } else {
            curr_parent->right = curr->left;
        }
    }
    // case, item to delete has only a right child
    else if (curr->left == 0) {
        if (curr == root) {
            root = curr->right;
        } else if (curr_parent->left == curr) {
            curr_parent->left = curr->right;
        } else {
            curr_parent->right = curr->right;
        }
    }
    // case, item to delete has two children
    else {
        Node<KeyType, ItemType>* in;
        Node<KeyType, ItemType>* in_parent = curr;
        inorder(curr->right, in, in_parent);
        if (curr == in_parent) {
            in->left = curr->left;
        } else {
            in_parent->left = in->right;
            in->left = curr->left;
            in->right = curr->right;
        }

        if (curr == root) {
            root = in;
        } else if (curr_parent->left == curr) {
            curr_parent->left = in;
        } else {
            curr_parent->right = in;
        }
    }

    delete curr;

    return true;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
                                                  Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent) {
    // find inorder successor of "curr" and assign to "in"
    while (true) {
        if (curr->left != 0) {
            parent = curr;
            curr = curr->left;
        } else
            break;
    }

    in = curr;
}

// will give the pointer of where key node is or will give the leaves where it should be (curr left or right)
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
                                                 Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent) {
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int size) {
    // TODO: check for duplicate items in the input array

    // TODO: use the tree to sort the array items

    // TODO: overwrite input array values with sorted values
}
