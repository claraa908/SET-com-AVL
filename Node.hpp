#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node (int k, int h, Node* l, Node* r) {
        key = k;
        left = l;
        right = r;
        height = h;
    }
};

#endif