/*******************************************************************************
 * DATA STRUCTURES IMPLEMENTATIONS
 *
 *   __                __
 *  |  \  _  |_  _    (_  |_  _      _ |_      _  _  _
 *  |__/ (_| |_ (_|   __) |_ |  |_| (_ |_ |_| |  (- _)
 *
 *
 * Adelson-Velskii and Landis' (AVL) tree
 *
 * Features, being N the number of elements in the tree:
 * 1. Guaranteed search time is O(log(N)).
 * 2. Dynamically updated/balanced tree structure O(N) storage.
 *
 * http://en.wikipedia.org/wiki/AVL_tree
 *
 * @author (moboustta6@gmail.com)
 * @github MoBoustta
 *
 ******************************************************************************/

#include "AVLTree.h"


template<typename T>
AVLTree<T>::AVLTree() : mSize{}, root{nullptr} {

}

template<typename T>
AVLTree<T>::~AVLTree() {
    delete root;
}


template<typename T>
void AVLTree<T>::insert_(const T &item) {
    root = insert_(root, item);
}

template<typename T>
auto AVLTree<T>::insert_(AVLTree::AVLNode *pRoot, const T &item) {

    if (pRoot == nullptr) {
        pRoot = new AVLNode{item};
        return pRoot;
    }

    if (item < pRoot->value) {
        if (pRoot->leftChild == nullptr) {
            pRoot->leftChild = new AVLNode{item};
            return pRoot;
        }
        insert(pRoot->leftChild, item);
    } else {
        if (pRoot->rightChild == nullptr) {
            pRoot->rightChild = new AVLNode{item};
            return pRoot;
        }
        insert(pRoot->rightChild, item);
    }
}


/*
 * This is another cleaner and easy to understand implementation for the insert method
 * + Rotation implemented for this version unlike the previous one.
 */


template<typename T>
void AVLTree<T>::insert(const T &item) {
    root = insert(root, item);
    mSize++;
}

template<typename T>
auto AVLTree<T>::insert(AVLNode *pRoot, const T &item) {

    if (pRoot == nullptr)
        return new AVLNode{item};

    if (item < pRoot->value)
        pRoot->leftChild = insert(pRoot->leftChild, item);
    else
        pRoot->rightChild = insert(pRoot->rightChild, item);

    /*
     * Set the height of every node
     */
    pRoot->height = std::max(getHeight(pRoot->leftChild), getHeight(pRoot->rightChild)) + 1;

    return balance(pRoot);
}

template<typename T>
auto *AVLTree<T>::balance(AVLNode *pRoot) {
    auto balanceFactor = getBalanceFactor(pRoot);

    if (isLeftHeavy(balanceFactor)) {
        if (getBalanceFactor(pRoot->leftChild) < 0)
            pRoot->leftChild = rotateLeft(pRoot->leftChild);
        return rotateRight(pRoot);
    } else if (isRightHeavy(balanceFactor)) {
        if (getBalanceFactor(pRoot->rightChild) > 0)
            pRoot->rightChild = rotateRight(pRoot->rightChild);
        return rotateLeft(pRoot);
    }

    return pRoot;
}

template<typename T>
auto *AVLTree<T>::rotateLeft(AVLNode *pRoot) const {
    auto newRoot = *pRoot->rightChild;

    pRoot->rightChild = nullptr;
    if (newRoot.leftChild != nullptr)
        pRoot->rightChild = newRoot.leftChild;
    newRoot.leftChild = pRoot;

    resetHeight(pRoot, newRoot);

    return new AVLNode { newRoot };
}


template<typename T>
auto *AVLTree<T>::rotateRight(AVLNode *pRoot) const {
    auto newRoot = *pRoot->leftChild;

    pRoot->leftChild = nullptr;
    if (newRoot.rightChild != nullptr)
        pRoot->leftChild = newRoot.rightChild;
    newRoot.rightChild = pRoot;

    resetHeight(pRoot, newRoot);

    return new AVLNode { newRoot };
}


template<typename T>
void AVLTree<T>::resetHeight(AVLNode *pRoot, AVLNode &newRoot) const {
    pRoot->height = std::max(getHeight(pRoot->leftChild), getHeight(pRoot->rightChild)) + 1;
    newRoot.height = std::max(getHeight(newRoot.leftChild), getHeight(newRoot.rightChild)) + 1;
}

template<typename T>
bool AVLTree<T>::isRightHeavy(int balanceFactor) const { return balanceFactor < -1; }

template<typename T>
bool AVLTree<T>::isLeftHeavy(int balanceFactor) const { return balanceFactor > 1; }

template<typename T>
int AVLTree<T>::getBalanceFactor(const AVLNode *pRoot) const {
    return getHeight(pRoot->leftChild) - getHeight(pRoot->rightChild);
}

template<typename T>
bool AVLTree<T>::isLeaf(const AVLNode *pRoot) const {
    return pRoot->leftChild == nullptr || pRoot->rightChild == nullptr;
}

template<typename T>
int AVLTree<T>::getHeight(const AVLNode *node) const {
    return node == nullptr ? -1 : node->height;
}

template<typename T>
bool AVLTree<T>::isBalanced() {
    return getHeight(root->leftChild) - getHeight(root->rightChild) <= 1;
}

template<typename T>
bool AVLTree<T>::isPerfect() {
    auto treeHeight = std::max(getHeight(root->leftChild), getHeight(root->rightChild)) + 1;
    return ((2 * treeHeight) + 1) - 1 == mSize;
}

template<typename T>
constexpr std::size_t AVLTree<T>::size() const {
    return mSize;
}

template<typename T>
bool AVLTree<T>::isEmpty() const {
    return mSize == 0;
}
