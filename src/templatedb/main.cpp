#include "lsm.h"
using namespace std;

int main () {
    size_t n = 1;
    size_t j = 3;
    LSMTree test = LSMTree(n, j);

    test.put(1, 1);
    test.put(2, 2);
    test.put(3, 3);

    test.put(4, 4);
    test.put(5, 5);
    test.put(6, 6);

    test.put(7, 7);
    test.put(8, 8);
    test.put(9, 9);
    test.put(10, 10);
    test.put(11, 11);

    // test.put(12, 12);
    // test.put(13, 13);
    // test.put(14, 14);
    // test.put(15, 15);


    test.printBuffer();

    //         // Object to read from file 
    // ifstream ifile_obj; 
  
    // // Opening file in input mode 
    // string temp = "disk0";
    // ifile_obj.open(temp, ios::in); 
  
    // // Object of class Node to input data in file 
    // Node obj; 
  
    // // Reading from file into object "ifile_obj" 
    // cout << "********************************read from disk 0************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();
  
    // // Opening file in input mode 
    // temp = "disk1";
    // ifile_obj.open(temp, ios::in); 
  
    // // Object of class Node to input data in file 
  
    // // Reading from file into object "ifile_obj" 
    // cout << "********************************read from disk 1************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();

  
    // // Opening file in input mode 
    // temp = "disk2";
    // ifile_obj.open(temp, ios::in); 
  
    // // Object of class Node to input data in file 
 
    // // Reading from file into object "ifile_obj" 
    // cout << "********************************read from disk 2************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();
 
    // // Opening file in input mode 
    // temp = "disk3";
    // ifile_obj.open(temp, ios::in); 
  
    // // Object of class Node to input data in file 
  
    // // Reading from file into object "ifile_obj" 
    // cout << "********************************read from disk 3************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();

    // temp = "disk4";
    // ifile_obj.open(temp, ios::in); 

    // cout << "********************************read from disk 4************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();

    // temp = "disk5";
    // ifile_obj.open(temp, ios::in); 

    // cout << "********************************read from disk 5************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();

    // temp = "disk6";
    // ifile_obj.open(temp, ios::in); 

    // cout << "********************************read from disk 6************************************"<< endl;
    // ifile_obj.read((char*)&obj, sizeof(obj));
    // while (!ifile_obj.eof()) { 
    //     // print to see results
    //     cout << "Key: " << obj.key << ", Value: " << obj.val << endl;
    //     // Checking further 
    //     ifile_obj.read((char*)&obj, sizeof(obj)); 
    // }
    // ifile_obj.close();

    test.printFencePointers();
    Node* temp = test.get(10);
    if (temp != NULL) {
        cout << temp->key << ": " << temp->val << endl;
    }
    cout << "***************************DELETE*****************************" << endl;
    test.remove(10);
    temp = test.get(10);
    if (temp != NULL) {
        cout << temp->key << ": " << temp->val << endl;
    }
    cout << "***************************AFTER DELETE*****************************" << endl;
    test.printFencePointers();
    test.put(12, 12);
    test.put(13, 13);
    test.put(14, 14);
    test.put(15, 15);
    cout << "***************************AFTER INSERTING MORE*****************************" << endl;
    test.printBuffer();
    test.printFencePointers();

    // test.checkBloomFilter(0, to_string(10));
    // test.checkBloomFilter(0, to_string(8));
    // test.checkBloomFilter(0, to_string(9));

    // test.checkBloomFilter(1, to_string(1));
    // test.checkBloomFilter(1, to_string(2));
    // test.checkBloomFilter(1, to_string(3));

    // test.checkBloomFilter(1, to_string(7));
    // test.checkBloomFilter(1, to_string(8));
    // test.checkBloomFilter(1, to_string(9));

    // for (int i = 14; i > -1; i--) {
    //     test.put(i, i);
    // }

    // // test.merge();
    // cout << "**********************COMPLETED ADDITIONS***************************" << endl;

    // test.printBuffer();
    // test.readFromDisk();

    // Node* testNode;
    // for (int i = 0; i < 15; i++) {
    //     testNode = test.get(i);
    //     if (testNode != NULL) {
    //     cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    //     } 
    //     else {
    //         cout << "NOT FOUND 1" << endl;
    //     }
    // }

    // test.update(2, 5);
    // test.update(15, 1);

    // testNode = test.get(2);
    // if (testNode != NULL) {
    // cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    // } 
    // else {
    //     cout << "NOT FOUND 1" << endl;
    // }

    // testNode = test.get(14);
    // if (testNode != NULL) {
    // cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    // } 
    // else {
    //     cout << "NOT FOUND 1" << endl;
    // }

    // cout << "*****************REMOVAL********************" << endl;
    // test.remove(2);
    // test.printBuffer();
    // test.remove(15);
    // test.readFromDisk();

    // testNode = test.get(2);
    // if (testNode != NULL) {
    // cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    // } 
    // else {
    //     cout << "NOT FOUND" << endl;
    // }

    // testNode = test.get(14);
    // if (testNode != NULL) {
    // cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    // } 
    // else {
    //     cout << "NOT FOUND" << endl;
    // }

    return 0;
}