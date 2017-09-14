/*
 * ArrayTree.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Zengye
 */
# include "header.h"



// - remove subtree from index array tree
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int parentIdx;
    bool valid;
    bool visited;

    Node(int pi) : parentIdx(pi), valid(true), visited(false) {}
};

class ArrayTree {
public:
    ArrayTree(vector<int> nums) {
        for (int i : nums) {
            nodes.push_back(new Node(i));
            size ++;
        }
    }

    void deleteSubtree(int idx) {
        if (!nodes[idx]->valid) // if already deleted
            return;

        reset(); // reset valid nodes back to unvisited

        nodes[idx]->valid = false;
        nodes[idx]->visited = true;
        size --;

        for (int i = 0; i < nodes.size(); ++ i) {
            if (nodes[i]->visited)
                continue;
            explore(i);
        }
    }

    void print() {
        cout << "tree size: " << size << endl;
        for (int i = 0; i < nodes.size(); ++ i) {
            cout << "\tnode idx: " << i << ", parent idx: " << nodes[i]->parentIdx
            << ", visited: " << nodes[i]->visited << ", valid: " << nodes[i]->valid << endl;
        }
    }

private:
    vector<Node *> nodes;
    int size;

    bool explore(int idx) {
        // if current is root or is already visited
        if (nodes[idx]->parentIdx == -1 || nodes[idx]->visited) {
            nodes[idx]->visited = true;
            return nodes[idx]->valid;
        }

        nodes[idx]->visited = true;
        // current validness depends on parent validness
        bool isParentValid = explore(nodes[idx]->parentIdx);
        if (nodes[idx]->valid != isParentValid) {
            nodes[idx]->valid = isParentValid;
            size --; // only decrement size when change from valid to invalid
        }

        return isParentValid;
    }

    void reset() {
        for (Node * n : nodes) {
            if (n->valid)
                n->visited = false;
        }
    }
};
int run_ArrayTree() {

    vector<int> nums = {1, 5, 5, 2, 2, -1, 3};
    ArrayTree at(nums);
    at.print();

    at.deleteSubtree(3);
    at.print();

    at.deleteSubtree(6);
    at.print();

    at.deleteSubtree(2);
    at.print();

    return 0;
}







