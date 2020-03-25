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

void LSMTree::readFromDisk() {
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
}

int LSMTree::findFileSize() {
    ifstream ifile_obj; 
    ifile_obj.open(disk, ios::in); 
    Node obj; 
    int numElements = 0;

    ifile_obj.read((char*)&obj, sizeof(obj));
    while (!ifile_obj.eof()) { 
        numElements += 1;
        ifile_obj.read((char*)&obj, sizeof(obj)); 
    }
    
    ifile_obj.close();

    return numElements;
}

void LSMTree::populateFileData(Node* fileData) {
    ifstream ifile_obj; 
    ifile_obj.open(disk, ios::in); 
    Node obj; 
    int index = 0;
  
    ifile_obj.read((char*)&obj, sizeof(obj));
    while (!ifile_obj.eof()) { 
        fileData[index] = (Node){obj.key, obj.val};
        index += 1;
        ifile_obj.read((char*)&obj, sizeof(obj)); 
    }

    ifile_obj.close();
}

void LSMTree::write_to_disk(){
    //flush all data in memory to disk and also newData
    //store it as storage.txt
    // ofstream file (disk);
    // for (int i = 0; i < block_size; i++) {
    //     file << block[i].key << ',' << block[i].val << '\n';
    // }
    // file << newData.key << ',' << newData.val << '\n';
    // file.close();

    // sort buffer
    mergeSort(block, next_empty);

    Node* fullData = NULL;
    Node* fileData = NULL;

    int numElements = 0;
    int r;

    struct stat s;
    char* diskName = strcpy(new char[disk.length() + 1], disk.c_str());

    int file_exists = stat(diskName, &s);

    if (file_exists == 0) {
        numElements = findFileSize();
        fileData = new Node[numElements];
        populateFileData(fileData);
        fullData = new Node[numElements + next_empty];
        mergeStep(fullData, fileData, numElements, block, next_empty);
        delete(fileData);
    }

    if (fullData == NULL) {
        fullData = block;
    }

    ofstream file_obj;
    file_obj.open(disk, ios::trunc);
    for (int i = 0; i < numElements + next_empty; i++) {
        file_obj.write((char*)&fullData[i], sizeof(fullData[i])); 
    }
    // file_obj.write((char*)&newData, sizeof(newData)); 
    file_obj.close();
    next_empty = 0; 
    // readFromDisk();
}

void LSMTree::put(int *key, int *value) {
    Node newData;
    newData.key = *key;
    newData.val = *value;
    if (next_empty == block_size) {
        // write to disk since buffer is full
        write_to_disk();
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

void LSMTree::mergeStep(Node *originalArray, Node *leftArray, int leftSize, Node *rightArray, int rightSize){
    int r, l, i;
    r = 0; 
    l = 0;
    i = 0;

    while (l < leftSize && r < rightSize) {
        if(leftArray[l].key  < rightArray[r].key){
            originalArray[i++] = leftArray[l++];
        } 
        else{
            originalArray[i++] = rightArray[r++];
        }
    }

    while (l < leftSize) {
        originalArray[i++] = leftArray[l++];
    }

    while (r < rightSize) {
        originalArray[i++] = rightArray[r++];
    }
}

void LSMTree::mergeSort(Node* inputBlock, int n) {
    if (n < 2) {
        return;
    }

    int mid;
    int i;

    mid = n * 0.5;
    Node *leftArray = new Node[mid];
    Node *rightArray = new Node[n - mid];

    copy(inputBlock, &inputBlock[mid], leftArray);
    copy(&inputBlock[mid], &inputBlock[n], rightArray);

    mergeSort(leftArray, mid);
    mergeSort(rightArray, n - mid);
    mergeStep(inputBlock, leftArray, mid, rightArray, n - mid);

    delete(leftArray);
    delete(rightArray);
}

void LSMTree::merge() {
    cout << "here" << endl;
    mergeSort(block, next_empty);
}