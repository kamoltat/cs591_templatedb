#include "lsm.h"

using namespace std;

LSMTree::LSMTree(size_t buffer_size) {

    block_size = buffer_size;
    k = 2;
    next_empty = 0;
    block = new Node[block_size];
    disk = "storage.txt";

    cout << "completed\n";    
}