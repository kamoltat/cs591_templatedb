#ifndef LSM_H
#define LSM_H

#include <iostream>
#include <string>
#include <cstring>

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
        void merge();
    private:
        void write_to_disk();
        void mergeSort(Node* block, int n);
        void mergeStep(Node* whole, Node* leftArray, int leftSize, Node* rightArray, int rightSize);
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