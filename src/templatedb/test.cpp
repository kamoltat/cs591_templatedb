#include "lsm.h"
#include <chrono> 
using namespace std::chrono; 
using namespace std;

void insert_100(LSMTree tree){
    for(int i=1; i < 101;i++){
        tree.put(i, i);
    }
}

void insert_1000(LSMTree tree){
    for(int i=1; i < 1001;i++){
        tree.put(i, i);
    }
}

void insert_10000(LSMTree tree){
    for(int i=1; i < 100001;i++){
        tree.put(i, i);
    }
}

void get_100(LSMTree tree){
    Node* testNode;
    for(int i=1; i < 101;i++){
        tree.get(i);
    }
}


int main () {
    //Test for Inserts 

    size_t n = 1;
    size_t j = 3;
    LSMTree tiering = LSMTree(n, "T", j);
    LSMTree leveling = LSMTree(n, "L", j);

    insert_100(tiering);
    auto start = high_resolution_clock::now();
    get_100(tiering);
    auto stop = high_resolution_clock::now();
    // Get duration. Substart timepoints to  
    // get durarion. To cast it to proper unit 
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by tiering: "
         << duration.count() << " microseconds" << endl;

    insert_100(leveling);
    auto start2 = high_resolution_clock::now();
    get_100(leveling);
    auto stop2 = high_resolution_clock::now();
    // Get duration. Substart timepoints to  
    // get durarion. To cast it to proper unit 
    // use duration cast method
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << "Time taken by level: "
         << duration2.count() << " microseconds" << endl;


    return 0;
}