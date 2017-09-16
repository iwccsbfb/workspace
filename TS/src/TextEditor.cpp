/*
 * TextEditor.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Zengye
 */

#include "header.h"

#include <stack>

//----------------------text editor设计题-----------------
//insert(p), delete(p1, p2), highlight(p1, p2)，redo/undo, save/load update, search
//text editor需要insert，remove，highlight，需要想办法去index每次插入的object，原po说的interval tree应该就是index的方式吧。
//关键点在于text打算怎么存
//store highlight?
//他要求三天后再load这个text,需要可以undo三天前的操作. save的时候 保存成xml类型之类的 把之前的操作也一起存下来
struct Node {
    string text;
    int size; // if Node is leaf, size = text.size(); if not leaf, size = left.size + right.size
    Node * left; // if no left child, this node is leaf
    Node * right;

    Node(string _text = "", int _size = 0)
    : text(_text), size(_size), left(NULL), right(NULL)
    {}
};

class TextEditor {
public:
    TextEditor() : root(NULL) {
    }

    void initialize(const string &str) {
        root = build(str);
    }

    char index(int i) {
        return index(root, i);
    }

private:
    Node * root;
    stack<Operation> undo; // whenever executed an operation, put the reverse operation in undo
    stack<Operation> redo; // whenever undo an operation, put the reverse operation of the undo (essentially the original operation) in redo

    Node * build(const string str) {
        int n = str.size();
        if (n <= 0)
            return NULL;

        if (n <= 2)
            return new Node(str, str.size()); // creating leaf node

        Node * node = new Node();

        node->left = build(str.substr(0, n / 2));
        node->right = build(str.substr(n/2, n - n/2));
        node->size = str.size();

        return node;
    }

    char index(Node * node, int i) {
        if (!node || i >= node->size) return 'x';

        if (!node->left) { // is leaf
            return node->text[i];
        }

        if (i < node->left->size)
            return index(node->left, i);

        return index(node->right, i - node->left->size);
    }
};




