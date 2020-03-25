#include "lsm.h"

using namespace std;

int main () {
    size_t n = 10;
    LSMTree test = LSMTree(n);
    for (int i = 10; i > -1; i--) {
        test.put(&i, &i);

    // for (int i = 10; i > -1; i--) {
    //     test.put(&i, &i);
    // }
    
    test.merge();
    test.printBuffer();
    return 0;
}