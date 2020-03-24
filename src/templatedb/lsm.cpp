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

void LSMTree::put(int key, int value) {
    Node newData;
    newData.key = key;
    newData.val = value;

    block[next_empty] = newData;
    next_empty += 1;

}

void LSMTree::printBuffer() {
    for (int i = 0; i < next_empty; i++) {
        cout << "Key: " << block[i].key << ", Value: " << block[i].val << endl;
    }
}