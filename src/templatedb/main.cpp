#include "lsm.h"

using namespace std;

int main () {
    size_t n = 500;
    LSMTree test = LSMTree(n);
    for (int i = 0; i < 10; i++) {
        test.put(&i, &i);
    }

    test.printBuffer();
    return 0;
}