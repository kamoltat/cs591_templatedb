#include "lsm.h"

using namespace std;

int main () {
    size_t n = 10;
    LSMTree test = LSMTree(n);
    for (int i = 14; i > -1; i--) {
        test.put(&i, &i);
    }

    // test.merge();
    cout << "**********************COMPLETED ADDITIONS***************************" << endl;

    test.printBuffer();
    test.readFromDisk();

    Node* testNode = test.get(2);
    if (testNode != NULL) {
        cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    } 
    else {
        cout << "NOT FOUND 1" << endl;
    }

    cout << "FINDING 14 ON DISK" << endl;
    testNode = test.get(2);
    if (testNode != NULL) {
        // cout << "Key: " << testNode->key << " Val: " << testNode->val << endl;
    } 
    else {
        cout << "NOT FOUND 2" << endl;
    }
    return 0;
}