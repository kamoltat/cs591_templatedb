#ifndef LSM_H
#define LSM_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

typedef struct Node{
  int key;
  int val;
} Node;

typedef struct nodeFinder{
  Node* node;
  int index;
} nodeFinder;

class Run {
    public:
      Run(size_t dataSize, string newFileName);
      void insert(Node* data, int numElements);
      void update(int key, int value);
      void remove(int key);
      string fileName;
      int maxSize;
      int currSize = 0;
      bool isEmpty = true;
    private:
     
};

class Level {
    public:
      Level(size_t runSize);
      vector<Run> runs;
      int currNumRuns = 0;
      //fence pointer
      //bloom filter
      int maxNumRuns;
      //search
      //put
      //remove
      //update
    private:

};

class LSMTree {
    public:
        LSMTree(size_t bufferSize, size_t levelCapacity);
        void put(int key, int value);
        void printBuffer();
        void readFromDisk();
        void merge();
        void update(int key, int value);
        void remove(int key);
        Node* get(const int key);
    private:
        int fileNameCounter = 0;
        vector<Level> levels;
        size_t levelRunCapacity;
        void mergeDown(int nextEmptyLevel);
        void deleteRunsPreviousLevel(int currLevel);
        void mergeFiles(int nextEmptyLevel, Node* fullData);
        void write_to_disk();
        int findNextEmptyLevel(int currLevel);
        int binarySearch(int lower, int upper, const int* key, Node* inputArray);
        nodeFinder* searchBuffer(const int* key);
        nodeFinder* searchDisk(const int* key);
        int findFileSize();
        void populateFileData(Node* fileData, string fileName);
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