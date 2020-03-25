#include "lsm.h"

using namespace std;

int main () {
    size_t n = 10;
    LSMTree test = LSMTree(n);
    for (int i = 0; i < 11; i++) {
        test.put(&i, &i);

    }
    test.printBuffer();
    return 0;
}