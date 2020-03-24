#include "lsm.h"

using namespace std;
// using namespace templatedb;

int main () {
    // Say HelloWorld five times
    // cout << "here";
    size_t n = 500;
    LSMTree test = LSMTree(n);
    for (int i = 0; i < 10; i++) {
        test.put(i, i + 1);
    }

    test.printBuffer();
    return 0;
}