#include "lsm.h"

using namespace std;

lsm* init_new_lsm(size_t buffer_size) {

    lsm* newTree;
    if (!newTree) {
        cout << "Init Err";  
        return NULL;
    }

    newTree->block_size = buffer_size;
    newTree->k = 2;
    newTree->next_empty = 0;
    newTree->block = new node[newTree->block_size];

    if (!newTree->block) {
        cout << "Init Block Err";
        return NULL;
    }

    newTree->disk1 = "storage.txt";
    cout << "completed";

    return newTree;
    
}