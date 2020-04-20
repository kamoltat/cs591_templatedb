#include "lsm.h"

using namespace std;

Run::Run(size_t dataSize, string NewFileName) {
    maxSize = dataSize;
    fileName = NewFileName;
}

void Run::insert(Node* data, int numElements) {
    ofstream file_obj;
    file_obj.open(fileName, ios::trunc);
    for (int i = 0; i < numElements; i++) {
        file_obj.write((char*)&data[i], sizeof(data[i])); 
    }
    // file_obj.write((char*)&newData, sizeof(newData)); 
    file_obj.close();
    isEmpty = false;
}

Level::Level(size_t runSize) {
    maxNumRuns = runSize;
}

LSMTree::LSMTree(size_t buffer_size, size_t levelCapacity) {
    block_size = buffer_size;
    levelRunCapacity = levelCapacity;
    k = 2;
    next_empty = 0;
    block = new Node[block_size];
    disk = "storage.txt";

    cout << "completed\n";    
}

int LSMTree::findNextEmptyLevel(int currLevel) {
    if (currLevel == levels.size()) {
        return currLevel;
    }

    if (levels[currLevel].currNumRuns != levels[currLevel].maxNumRuns) {
        return currLevel;
    }

    return findNextEmptyLevel(currLevel + 1);
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

void LSMTree::populateFileData(Node* fileData, string fileName) {
    ifstream ifile_obj; 
    ifile_obj.open(fileName, ios::in); 
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

void LSMTree::mergeFiles(int nextEmptyLevel, Node* fullData){

    Node* fileData = NULL;
    Node* inputBlock = NULL;

    int currNumElements = 0;
    vector<Run> runs_vector = levels[nextEmptyLevel-1].runs;

    for(int i = 0; i < runs_vector.size(); i++){
        Run cur_run = runs_vector[i];
        fileData = new Node[cur_run.maxSize];
        inputBlock = new Node[currNumElements];
        copy(fullData, &fullData[currNumElements], inputBlock);

        populateFileData(fileData, cur_run.fileName);
        mergeStep(fullData, inputBlock, currNumElements, fileData, cur_run.maxSize);
        currNumElements += cur_run.maxSize;

        delete[] fileData;
        delete[] inputBlock;

        fileData = NULL;
        inputBlock = NULL;
    }
}

void LSMTree::deleteRunsPreviousLevel(int currLevel) {
    for(int i = 0; i < levels[currLevel].maxNumRuns; i++) {
        levels[currLevel].runs[i].isEmpty = true;
    }

    levels[currLevel].currNumRuns = 0;
}

void LSMTree::mergeDown(int nextEmptyLevel) {

    Node* fullData = NULL;
    int runIndex;
    for (int i = nextEmptyLevel; i > 0; i--) {
        //merge all runs on previous level
        //insert into new run on lower 
        fullData = new Node[levelRunCapacity*levels[i - 1].runs[0].maxSize];
        mergeFiles(i, fullData);
    
        runIndex = levels[i].currNumRuns;
        // for (int j = 0; j < levels[i].maxNumRuns; j++) {
        //     if (levels[i].runs[j].isEmpty) {
        //         runIndex = j;
        //         break;
        //     }
        // }

        levels[i].runs[runIndex].insert(fullData, levelRunCapacity*levels[i - 1].runs[0].maxSize);
        levels[i].currNumRuns += 1;
        deleteRunsPreviousLevel(i - 1);
    }
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

    //find next empty level
    int nextEmptyLevel = findNextEmptyLevel(0);
    if (nextEmptyLevel == levels.size()) {
        Level newLevel = Level(levelRunCapacity);
        levels.push_back(newLevel);
    }

    size_t newSize;

    if (nextEmptyLevel == 0) {
        newSize = block_size;
    }
    else {
        newSize = (levels[nextEmptyLevel - 1].runs[0].maxSize) * levelRunCapacity;
    }

    if (levels[nextEmptyLevel].runs.size() != levels[nextEmptyLevel].maxNumRuns) {
        string fileName = "disk" + to_string(fileNameCounter);
        fileNameCounter += 1;

        Run newRun = Run(newSize, fileName);

        levels[nextEmptyLevel].runs.push_back(newRun); 
    }

    int nexEmptyRun;

    if (nextEmptyLevel == 0) {
        nexEmptyRun = levels[nextEmptyLevel].currNumRuns;
        levels[nextEmptyLevel].runs[nexEmptyRun].insert(block, next_empty);
        levels[nextEmptyLevel].currNumRuns += 1;
    }

    else {
        mergeDown(nextEmptyLevel);
        nexEmptyRun = levels[0].currNumRuns;
        levels[0].runs[nexEmptyRun].insert(block, next_empty);
        levels[0].currNumRuns += 1;
    }
   //insert into empty run

    // Node* fullData = NULL;
    // Node* fileData = NULL;

    // int numElements = 0;
    // int r;

    // struct stat s;
    // char* diskName = strcpy(new char[disk.length() + 1], disk.c_str());

    // int file_exists = stat(diskName, &s);

    // if (file_exists == 0) {
    //     numElements = findFileSize();
    //     fileData = new Node[numElements];
    //     populateFileData(fileData);
    //     fullData = new Node[numElements + next_empty];
    //     mergeStep(fullData, fileData, numElements, block, next_empty);
    //     delete(fileData);
    // }

    // if (fullData == NULL) {
    //     fullData = block;
    // }

    // ofstream file_obj;
    // file_obj.open(disk, ios::trunc);
    // for (int i = 0; i < numElements + next_empty; i++) {
    //     file_obj.write((char*)&fullData[i], sizeof(fullData[i])); 
    // }
    // // file_obj.write((char*)&newData, sizeof(newData)); 
    // file_obj.close();
    // delete(diskName);
    next_empty = 0; 
    // readFromDisk();
}

void LSMTree::put(int key, int value) {
    Node newData;
    newData.key = key;
    newData.val = value;
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

    delete[] leftArray;
    delete[] rightArray;
}

void LSMTree::merge() {
    cout << "here" << endl;
    mergeSort(block, next_empty);
}

int LSMTree::binarySearch(int lower, int upper, const int* key, Node* inputArray) {
    int mid = ceil((lower + upper) * 0.5);
    nodeFinder* found;
    while (lower <= upper) {
        mid = ceil((lower + upper) * 0.5);
        if (inputArray[mid].key == *key) {
            return mid;
        }
        else if (inputArray[mid].key > *key) {
            upper = mid - 1;
        }
        else {
            lower = mid + 1;
        }
    }  

    return -1;  
}

// iterative binary search
nodeFinder* LSMTree::searchBuffer(const int* key) {
    cout << "searching through buffer..." << endl;
    int index = binarySearch(0, next_empty, key, block);
    
    if (index == -1) {
        cout << "not found in buffer" << endl;
        return NULL;
    }

    cout << "found in buffer" << endl;
    Node found = {block[index].key, block[index].val};
    nodeFinder *ret = new (nodeFinder){&found, index};

    return ret;
}
// iterative binary search
nodeFinder* LSMTree::searchDisk(const int* key) {
    cout << "searching through disk..." << endl;
    int size = findFileSize();
    Node* fileData = new Node[size];
    string temp = "disk0";
    populateFileData(fileData, temp);
    int index = binarySearch(0, size, key, fileData);

    if (index == -1) {
        cout << "not found in disk" << endl;
        return NULL;
    }

    cout << "found in disk" << endl;
    Node found = {fileData[index].key, fileData[index].val};
    nodeFinder* ret = new (nodeFinder){&found, index};

    delete[] fileData;

    return ret;
}

Node* LSMTree::get(const int key) {
    mergeSort(block, next_empty);
    nodeFinder* finder = searchBuffer(&key);
    if (finder != NULL) {
        return finder->node;    
    }
    else {
        finder = searchDisk(&key);
        if (finder != NULL) {
            return finder->node;
        }
    }

    return NULL;
}

void LSMTree::update(int key, int value) {
    mergeSort(block, next_empty);
    int index = -1;

    index = binarySearch(0, next_empty, &key, block);
    if (index != -1) {
        block[index].val = value;
        return;
    }

    int size = findFileSize();
    Node* fileData = new Node[size];
    string temp = "temp";
    populateFileData(fileData, temp);
    index = binarySearch(0, size, &key, fileData);

    if (index != -1) {
        fileData[index].val = value;
        ofstream file_obj;
        file_obj.open(disk, ios::trunc);
        for (int i = 0; i < size; i++) {
            file_obj.write((char*)&fileData[i], sizeof(fileData[i])); 
        }
        // file_obj.write((char*)&newData, sizeof(newData)); 
        file_obj.close();
        delete[] fileData;
        return;
    }

    delete[] fileData;
    cout << "Key does not exist" << endl;
    return;
}

void LSMTree::remove(int key) {
    mergeSort(block, next_empty);
    int index = binarySearch(0, next_empty, &key, block);
    if (index != -1) {
        for (int i = index; i < next_empty; i++) {
            block[i].key = block[i + 1].key;
            block[i].val = block[i + 1].val;
        }
        next_empty--;
        return;
    }

    int size = findFileSize();
    Node* fileData = new Node[size];
    string temp = "temp";
    populateFileData(fileData, temp);
    index = binarySearch(0, size, &key, fileData);

    if (index != -1) {
        for (int i = index; i < next_empty; i++) {
            fileData[i].key = fileData[i + 1].key;
            fileData[i].val = fileData[i + 1].val;
        }
        ofstream file_obj;
        file_obj.open(disk, ios::trunc);
        for (int i = 0; i < size - 1; i++) {
            file_obj.write((char*)&fileData[i], sizeof(fileData[i])); 
        }
        // file_obj.write((char*)&newData, sizeof(newData)); 
        file_obj.close();
        delete[] fileData;
        return;
    }

    delete[] fileData;
    cout << "Key does not exist" << endl;
    return;

}