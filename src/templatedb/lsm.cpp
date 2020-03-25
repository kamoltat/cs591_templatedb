#include "lsm.h"

#include <iostream>
#include <fstream>

using namespace std;

LSMTree::LSMTree(size_t buffer_size) {
    block_size = buffer_size;
    k = 2;
    next_empty = 0;
    block = new Node[block_size];
    disk = "storage.txt";

    cout << "completed\n";    
}

void LSMTree::write_to_disk(Node newData){
    
    
    //flush all data in memory to disk and also newData
    //store it as storage.txt
    // ofstream file (disk);
    // for (int i = 0; i < block_size; i++) {
    //     file << block[i].key << ',' << block[i].val << '\n';
    // }
    // file << newData.key << ',' << newData.val << '\n';
    // file.close();

    ofstream file_obj;
    file_obj.open(disk, ios::app);
    for (int i = 0; i < block_size; i++) {
        file_obj.write((char*)&block[i], sizeof(block[i])); 
    }
    file_obj.write((char*)&newData, sizeof(newData)); 
    file_obj.close();

    // Object to read from file 
    ifstream ifile_obj; 
  
    // Opening file in input mode 
    ifile_obj.open(disk, ios::in); 
  
    // Object of class Node to input data in file 
    Node obj; 
  
    // Reading from file into object "ifile_obj" 
    cout << "read from disk "<< endl;
    ifile_obj.read((char*)&obj, sizeof(obj));
    while (!ifile_obj.eof()) { 
        // print to see results
        cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
        // Checking further 
        ifile_obj.read((char*)&obj, sizeof(obj)); 
    }
    ifile_obj.close();
    next_empty = 0; 
}

void LSMTree::put(int *key, int *value) {
    Node newData;
    newData.key = *key;
    newData.val = *value;
    if(next_empty == block_size){
        // write to disk since buffer is full
        write_to_disk(newData);
    }


    block[next_empty] = newData;
    next_empty += 1;

}

void LSMTree::printBuffer() {
    cout << "printBuffer"  << endl;
    for (int i = 0; i < next_empty; i++) {
        cout << "Key: " << block[i].key << ", Value: " << block[i].val << endl;
    }
}