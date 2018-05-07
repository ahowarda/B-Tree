// Andrew Howard, Andre Lipiec
// Project 3, B-Tree
// COSC320, Dr Anderson

#include "BTree.h"

BTree::BTree(int k) {
  root = NULL;
  degree = k;
}

BTreeNode::BTreeNode(int k,bool l) {
  degree = k;
  numKeys = 0;
  leaf = l;
  //std::cout << "here\n";
  children = new BTreeNode*[2*k];
  for (int i = 0; i < 2*k; i++)
    children[i] = NULL;
  //std::cout << "here2\n";
  keys = new int[(2*k)-1];

  for (int i = 0; i < 2*k-1; i++) {
    keys[i] = 0;
  }
  //std::cout << "here3\n";
}

BTree::~BTree() {
  root->deleteTree();
}

BTreeNode::~BTreeNode() {
}

void BTreeNode::deleteTree() {
  if (this == NULL) {
    return;
  }
  if (!leaf) {
      for (int i = 0; i < numKeys+1; i++) {
        children[i]->deleteTree();
      }
  }
  delete [] keys;
  delete [] children;
  delete this;
}

void BTree::print() {
  if(root != NULL) {
    root->print();
  }
  std::cout << "\n";
}

int* BTreeNode::getKeys() {
  return keys;
}

int BTreeNode::getKey(int i) {
  if (i < numKeys) {
    return keys[i];
  } else {
    std::cout << "Key out of range. \n";
  }
}

int BTreeNode::getNumKeys() {
  return numKeys;
}

BTreeNode* BTree::search(int k) {
  if (root == NULL) {
    return NULL;
  }

  return root->search(k);
}


void BTreeNode::print() {
  int i;
  for (i = 0; i < numKeys; i++) {
    if (!leaf) {
      children[i]->print();
    }
    std::cout << " " << keys[i];
  }
  if (!leaf) {
    children[i]->print();
  }
}

BTreeNode* BTreeNode::search(int k) {
  int i = 0;
  while(i < numKeys && k > keys[i])
    i++;

  if (i < numKeys && keys[i] == k) {
    return this;
  }

  if (leaf == true) {
    return NULL;
  }

  return children[i]->search(k);
}

void BTree::insert(int k) {

  if (root == NULL) { // Tree is Empty
    // Pass in degree and Leaf is true
    root = new BTreeNode(k,true);
    root->keys[0] = k;
    root->numKeys++;
  } else { // Tree is not NULL
      if (root->numKeys == 2*degree-1) { // Root Node is full
        BTreeNode* x = new BTreeNode(degree,false);
        x->children[0] = root; // Make new node root
        //std::cout << "here\n";

        x->splitChild(0,root);
        int i = 0;
        if (x->keys[0] < k) {
          i++;
        }
        x->children[i]->insertNonFull(k);

        root = x;

      } else {
        root->insertNonFull(k);
      }
  }
}

void BTree::remove(int k)
{
    if(!root)
    {
        std::cout << "The tree is empty" << std::endl;
        return;
    }

    root->remove(k);

    //If root node has 0 keys, make first child as new root

    if(root->numKeys == 0)
    {
        BTreeNode* temp = root;
        if(root->leaf)
            root == NULL;
        else
            root = root->children[0];

        delete temp;
    }
}
void BTreeNode::insertNonFull(int k) {
  int i = numKeys - 1;
  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i+1] = keys[i];
      i--;
    }
    keys[i+1] = k;
    numKeys++;
  } else {
    while (i >= 0 && keys[i] > k) {
      i--;
    }
    if (children[i+1]->numKeys == 2*degree -1) {

      splitChild(i+1, children[i+1]);
      if(keys[i+1] < k) {
        i++;
      }
    }
    children[i+1]->insertNonFull(k);
  }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
  //std::cout << "here\n";

  BTreeNode* z = new BTreeNode(y->degree,y->leaf);
  z->numKeys = degree - 1;

  for (int j = 0; j < degree-1; j++) {
    z->keys[j] = y->keys[j+degree];
  }
  if (!y->leaf) {
    for (int j = 0; j < degree; j++) {
      z->children[j] = y->children[j+degree];
    }
  }
  y->numKeys = degree - 1;

  for (int j = numKeys; j >= i+1; j--) {
    children[j+1] = children[j];
  }
  children[i+1] = z;

  for (int j = numKeys-1; j >= i; j--) {
    keys[j+1] = keys[j];
  }
  keys[i] = y->keys[degree-1];
  numKeys++;
}

int BTreeNode::findKey(int k)
{
    int index = 0;
   // std::cout << "Inside while loop in findKey" << std::endl;
    //std::cout << "Value of index: " << index << " value of numKeys: " << numKeys << std::endl;
      //  std::cout << "Value of keys[index]: " << keys[index] << " value of k: " << k << std::endl;
    while(index < numKeys && keys[index] < k)
    {
        index++;
    }
    return index;
}

void BTreeNode::remove(int k)
{
    int index = findKey(k);

    //std::cout << "Index for " << k << " is " << index << std::endl;

    if(index < numKeys && keys[index] == k)
    {
        if(leaf)
            removeFromLeaf(index);
        else
            removeFromNonLeaf(index);
    }
    else
    {
        if(leaf)
        {
            std::cout << "The key " << k << " is not in the tree" << std::endl;
            return;
        }

        bool flag;
        if(index == numKeys)
            flag = true;
        else
            flag = false;

        //If the child where the key is supposed to exist has less than t keys, we fill it up
        if(children[index]->numKeys < degree)
            fill(index);
        //if last child merged, it merged with previous child so we
        //recurse on the index-1th child. If not we recurse on the indexth child
        if(flag && index > numKeys)
            children[index-1]->remove(k);
        else
            children[index]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int index)
{
    for(int i = index + 1; i < numKeys; i++)
        keys[i-1] = keys[i];

    numKeys--;
}

void BTreeNode::removeFromNonLeaf(int index)
{
    int k = keys[index];

    //if child precedes l (children[index]) has at least degree keys
    //find the predeccesor of k in the subtree of children[index]
    //replace k with predeccesor and delete predeccesor in children[index]

    //So is degree the minimum number for keys
    if(children[index]->numKeys >= degree)
    {
        int p = predeccesor(index);
        keys[index] = p;
        children[index]->remove(p);
    }

    //if children[index] has less than degree keys, check children[index+1]
    //if it has atleast degree keys, find successor of k in subtree
    // children[index+1] and then delete successor in children[index+1]
    else if(children[index+1]->numKeys >= degree)
    {
        int s = successor(index);
        keys[index] = s;
        children[index+1]->remove(s);
    }


    //if children[index] and children[index+1] have less than degree
    //keys, merge k and all of children[index+1] into children[index]
    //children[index] has 2degree-1 keys and delete k from
    //children[index]

    else
    {
        merge(index);
        children[index]->remove(k);
    }
}

int BTreeNode::predeccesor(int index)
{
    BTreeNode* x = children[index];
    while(!x->leaf)
        x = x->children[x->numKeys];

    return x->keys[x->numKeys-1];
}

int BTreeNode::successor(int index)
{
    BTreeNode* x = children[index+1];
    while(!x->leaf)
        x = x->children[0];

    return x->keys[0];
}


void BTreeNode::fill(int index)
{
    //if child of children[index-1] has more than degree-1 keys
    // use key from child

    if(index != 0 && children[index-1]->numKeys >= degree)
        borrowFromPrev(index);

    //if child of children[index+1] has more than degree-1 keys
    // use key from child
    else if(index != numKeys && children[index+1]->numKeys >= degree)
        borrowFromNext(index);

    else
    {
        if(index != numKeys)
            merge(index);
        else
            merge(index - 1);
    }
}

void BTreeNode::borrowFromPrev(int index)
{
    BTreeNode* c = children[index];
    BTreeNode* s = children[index-1];

    //last key of children[index-1] goes to parent and keys[index-1]
    //from parent is inserted as first key in children[index].

    for(int i = c->numKeys-1; i >= 0; i--)
        c->keys[i+1] = c->keys[i];

    //if children[index] not a leaf move everything one ahead
    if(!c->leaf)
    {
        for(int i = c->numKeys; i >= 0; i--)
            c->children[index+1] = c->children[i];
    }

    //setting c first key equal to keys[index-1]
    c->keys[0] = c->keys[index-1];

    if(!leaf)
        c->children[0] = s->children[s->numKeys];

    //moving key from s to parent

    keys[index-1] = s->keys[s->numKeys-1];

    c->numKeys += 1;
    s->numKeys -= 1;
}

void BTreeNode::borrowFromNext(int index)
{
    BTreeNode* c = children[index];
    BTreeNode* s = children[index + 1];

    c->keys[(c->numKeys)] = keys[index];

    if(!(c->leaf))
        c->children[(c->numKeys)+1] = s->children[0];

    keys[index] = s->keys[0];

    for(int i = 1; i < s->numKeys; i++)
        s->keys[i-1] = s->keys[i];

    if(!s->leaf)
    {
        for(int i = 1; i <= s->numKeys; i++)
            s->children[i-1] = s->children[i];
    }

    c->numKeys += 1;
    s->numKeys -= 1;
}

//merges children[index] with children[index+1] and children[index+1]

void BTreeNode::merge(int index)
{
    BTreeNode* c = children[index];
    BTreeNode* s = children[index + 1];

    c->keys[degree-1] = keys[index];

    //copying keys from children[index+1] to children[index]
    for(int i = 0; i <= s->numKeys; ++i)
        c->keys[i+degree] = s->keys[i];

    if(!c->leaf)
    {
        for(int i = 0; i <= s->numKeys; ++i)
            c->children[i+degree] = s->children[i];
    }

    //filling gap created by keys[index] to children[index]
    for(int i = index+1 ; i < numKeys; ++i)
        keys[i-1] = keys[i];

    for(int i = index+2; i <= numKeys; ++i)
        children[i-1] = children[i];

    c->numKeys += s->numKeys+1;
    numKeys--;

    delete(s);

}
