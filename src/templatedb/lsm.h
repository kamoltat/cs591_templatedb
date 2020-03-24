#ifndef LSM_H
#define LSM_H

#include <iostream>
#include <string>

using namespace std;

typedef struct Node{
  int key;
  int val;
} Node;

class LSMTree {
    public:
        LSMTree(size_t bufferSize);
        void put(int *key, int *value);
        void printBuffer();
    private:
        size_t block_size;
        int k;
        size_t next_empty;
        Node* block;
        string disk;
};

// typedef struct nodei{
//   node *node;
//   int index;
// } nodei;

#endif