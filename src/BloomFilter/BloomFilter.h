#include <vector>
#include <string>
#include <math.h>

using namespace std;

class BloomFilter {
public:
	BloomFilter();
	BloomFilter( int numElement_, int bitsPerElement_ );
	int numElement;
	int bitsPerElement;

	void program(string key);
	bool query(string key);

	int getIndexNum();
	int getSize();
	vector<bool> getVec();
	void setVec(vector<bool> newBF);
	void reset();
private:
	int numIndex;
	int size;
	vector< bool > bf_vec;

	void makeBloomFilter();
	void getIndex( string key, vector<int>* index );
};

