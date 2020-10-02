//
// Created by moboustt on 10/1/20.
//

#ifndef DATA__STRUCTURES_AVLNODE_H
#define DATA__STRUCTURES_AVLNODE_H

#include <iostream>

template<typename AVLTREE>
class AVLNode {
public:
    using T = typename AVLTREE::ValueType;
public:
    AVLNode() = default;

    explicit AVLNode(T v);

    T value;
    std::size_t height;
    AVLNode *leftChild;
    AVLNode *rightChild;
};


#endif //DATA__STRUCTURES_AVLNODE_H
