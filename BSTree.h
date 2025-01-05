#ifndef BSTREE_H
#define BSTREE_H

#include "BSNode.h"
#include <vector>

template <typename T>
class BSTree {
private:
    BSNode<T>* root;

    int size(BSNode<T>* node) const {
        return node ? 1 + size(node->left) + size(node->right) : 0;
    }

    bool exists(BSNode<T>* node, const T& elem) const {
        if (!node) return false;
        if (elem == node->elem) return true;
        return exists(elem < node->elem ? node->left : node->right, elem);
    }

    BSNode<T>* insert(BSNode<T>* node, const T& elem) {
        if (!node) return new BSNode<T>(elem);
        if (elem < node->elem) node->left = insert(node->left, elem);
        else node->right = insert(node->right, elem);
        return node;
    }

    BSNode<T>* search(BSNode<T>* node, const T& elem) const {
        if (!node || node->elem == elem) return node;
        return search(elem < node->elem ? node->left : node->right, elem);
    }

    void toVector(BSNode<T>* node, std::vector<T>& vec) const {
        if (node) {
            toVector(node->left, vec);
            vec.push_back(node->elem);
            toVector(node->right, vec);
        }
    }

    void destroy(BSNode<T>* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    BSTree() : root(nullptr) {}
    ~BSTree() { destroy(root); }

    int size() const { return size(root); }
    bool exists(const T& elem) const { return exists(root, elem); }

    void insert(const T& elem) { root = insert(root, elem); }

    T search(const T& elem) const {
        BSNode<T>* node = search(root, elem);
        if (!node) throw std::runtime_error("Element not found");
        return node->elem;
    }
    std::vector<T> toVector() const {
        std::vector<T> result;
        toVector(root, result);
        return result;
    }

    BSNode<T>* remove(BSNode<T>* node, const T& elem, T& removedElem) {
        if (!node) return nullptr;

        if (elem < node->elem) {
            node->left = remove(node->left, elem, removedElem);
        } else if (elem > node->elem) {
            node->right = remove(node->right, elem, removedElem);
        } else {
            removedElem = node->elem;

            if (!node->left) {
                BSNode<T>* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (!node->right) {
                BSNode<T>* leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                BSNode<T>* minNode = findMin(node->right);
                node->elem = minNode->elem;
                node->right = remove(node->right, minNode->elem, removedElem);
            }
        }
        return node;
    }

    BSNode<T>* findMin(BSNode<T>* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    T remove(const T& elem) {
        T removedElem;
        root = remove(root, elem, removedElem);
        return removedElem;
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& tree) {
        std::vector<T> vec = tree.toVector();
        for (const T& elem : vec) {
            out << elem << " ";
        }
        return out;
    }
};

#endif // BSTREE_H
