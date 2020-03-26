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
    
    return 0;
}