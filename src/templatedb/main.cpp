#include "lsm.h"

using namespace std;

int main () {
    size_t n = 10;
    LSMTree test = LSMTree(n);
    for (int i = 14; i > -1; i--) {
        test.put(&i, &i);
    }

    for (int i = 0; i < 8; i++) {
        test.put(&i, &i);
    }
    // test.merge();
    cout << "**********************COMPLETED ADDITIONS***************************" << endl;
    test.printBuffer();
    test.readFromDisk();
    return 0;
}