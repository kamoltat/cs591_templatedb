#include "lsm.h"
using namespace std;

int main () {

    cout << "**********Tiered LSM Tree**********" << endl;
    // Buffer Size
    size_t n = 1;
    // Max number of runs per level
    size_t j = 3;
    // LSMTree test = LSMTree(n, "T", j);
    LSMTree tierTree = LSMTree(n, "T", j);

    tierTree.put(50, 50);
    tierTree.put(25, 25);
    tierTree.put(100, 100);
    tierTree.put(125, 125);
    tierTree.put(3, 3);
    tierTree.printFencePointers();
    tierTree.printBuffer();
    cout << "**********Inserting more elements**********" << endl;
    tierTree.put(23, 23);
    tierTree.put(95, 95);
    tierTree.put(90, 90);
    tierTree.put(101, 101);
    tierTree.put(102, 102);
    tierTree.put(103, 103);
    tierTree.printFencePointers();
    tierTree.printBuffer();
    cout << "**********Searching for 23**********" << endl;
    Node* getNode = tierTree.get(23);
    if (getNode != NULL) {
        cout << "Key: " << getNode->key << " Value: " << getNode->val << " EntryNumber: " << getNode->entryNum << endl;
    }
    cout << "**********Searching for 999**********" << endl;
    getNode = tierTree.get(999);
    if (getNode != NULL) {
        cout << "Key: " << getNode->key << " Value: " << getNode->val << " EntryNumber: " << getNode->entryNum << endl;
    }
    cout << "**********Range Query**********" << endl;
    vector<Node> rangeQueryRes;
    tierTree.rangeScan(3, 99, &rangeQueryRes);
    for (int i = 0; i < rangeQueryRes.size(); i++) {
        cout << "Key: " << rangeQueryRes[i].key << " Value: " << rangeQueryRes[i].val << " EntryNumber: " << rangeQueryRes[i].entryNum << endl;
    }
    cout << "**********Delete node with key 102**********" << endl;
    tierTree.remove(102);
    getNode = tierTree.get(102);
    if (getNode != NULL) {
        cout << "Key: " << getNode->key << " Value: " << getNode->val << " EntryNumber: " << getNode->entryNum << endl;
    }

   // ****************************************** LEVELED LSM TESTING ***************************************************
    cout << endl << "-------------------------------------------------------------------------------------" << endl;
    cout << "**********Leveled LSM Tree**********" << endl;
    LSMTree levelTree = LSMTree(n, "L");
    levelTree.put(50, 50);
    levelTree.put(25, 25);
    levelTree.put(100, 100);
    levelTree.put(125, 125);
    levelTree.put(3, 3);
    levelTree.printFencePointers();
    levelTree.printBuffer();
    cout << "**********Inserting more elements**********" << endl;
    levelTree.put(23, 23);
    levelTree.put(95, 95);
    levelTree.put(102, 102);
    levelTree.printFencePointers();
    levelTree.printBuffer();
    cout << "**********Searching for 23**********" << endl;
    getNode = levelTree.get(23);
    if (getNode != NULL) {
        cout << "Key: " << getNode->key << " Value: " << getNode->val << " EntryNumber: " << getNode->entryNum << endl;
    }
    cout << "**********Searching for 999**********" << endl;
    getNode = levelTree.get(999);
    if (getNode != NULL) {
        cout << "Key: " << getNode->key << " Value: " << getNode->val << " EntryNumber: " << getNode->entryNum << endl;
    }
    cout << "**********Range Query**********" << endl;
    vector<Node> rangeQueryResL;
    levelTree.rangeScan(3, 99, &rangeQueryResL);
    for (int i = 0; i < rangeQueryResL.size(); i++) {
        cout << "Key: " << rangeQueryResL[i].key << " Value: " << rangeQueryResL[i].val << " EntryNumber: " << rangeQueryResL[i].entryNum << endl;
    }
    cout << "**********Delete node with key 102**********" << endl;
    levelTree.remove(102);
    getNode = levelTree.get(102);
    if (getNode != NULL) {
        cout << "Key: " << getNode->key << " Value: " << getNode->val << " EntryNumber: " << getNode->entryNum << endl;
    }

    //         // Object to read from file 
    // ifstream ifile_obj; 
  
    // // Opening file in input mode 
    // string temp = "diskLT6";
    // ifile_obj.open(temp, ios::in); 
  
    // // Object of class Node to input data in file 
    // Node obj; 
  
    // // Reading from file into object "ifile_obj" 
    // cout << "********************************read from disk************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << " EntryNum: " << obj.entryNum << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();


    return 0;
}