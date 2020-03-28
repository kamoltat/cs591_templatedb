#include "lsm.h"

using namespace std;

int main () {
    size_t n = 10;
    LSMTree test = LSMTree(n);
    for (int i = 14; i > -1; i--) {
        test.put(i, i);
    }

    // test.merge();
    cout << "**********************COMPLETED ADDITIONS***************************" << endl;

    test.printBuffer();
    test.readFromDisk();

    Node* testNode;
    for (int i = 0; i < 15; i++) {
        testNode = test.get(i);
        if (testNode != NULL) {
        cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
        } 
        else {
            cout << "NOT FOUND 1" << endl;
        }
    }

    test.update(2, 5);
    test.update(15, 1);

    testNode = test.get(2);
    if (testNode != NULL) {
    cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    } 
    else {
        cout << "NOT FOUND 1" << endl;
    }

    testNode = test.get(14);
    if (testNode != NULL) {
    cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    } 
    else {
        cout << "NOT FOUND 1" << endl;
    }

    cout << "*****************REMOVAL********************" << endl;
    test.remove(2);
    test.printBuffer();
    test.remove(15);
    test.readFromDisk();

    testNode = test.get(2);
    if (testNode != NULL) {
    cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    } 
    else {
        cout << "NOT FOUND" << endl;
    }

    testNode = test.get(14);
    if (testNode != NULL) {
    cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    } 
    else {
        cout << "NOT FOUND" << endl;
    }

    return 0;
}