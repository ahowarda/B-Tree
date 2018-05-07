// Andrew Howard, Andre Lipiec
// Project 3, B-Tree
// COSC320, Dr Anderson

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <chrono>
#include <cstdlib>

// Defines the BTree Node Class
class BTreeNode {
  private:
    int* keys; // Array of keys in the node
    int degree; // Range for number of keys
    BTreeNode** children; // Array of pointers to children nodes
    int numKeys; // Number of keys currently in the node
    bool leaf; // Self Explanitory
  public:
    BTreeNode(int,bool);
    ~BTreeNode();
    void insertNonFull(int);
    void splitChild(int,BTreeNode*);
    void deleteTree();
    void print();
    BTreeNode* search(int);
    void initKeys();
    int* getKeys();
    int getKey(int);
    int getNumKeys();
    void traverse();
    int findKey(int);
    void remove(int);
    void removeFromLeaf(int);
    void removeFromNonLeaf(int);
    int predeccesor(int);
    int successor(int);
    void fill(int);
    void borrowFromPrev(int);
    void borrowFromNext(int);
    void merge(int);
  friend class BTree;
};

class BTree {
  private:
    BTreeNode* root;
    int degree;
  public:
    BTree(int);
    ~BTree();
    void print();
    BTreeNode* search(int);
    void insert(int);

    void remove(int);

};


#endif
