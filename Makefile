unitTest: ./src/templatedb/lsm.cpp ./src/templatedb/unitTests.cpp ./src/BloomFilter/murmurhash.cpp ./src/BloomFilter/BloomFilter.cpp
	g++ -std=c++11 -o unitTest.out ./src/templatedb/lsm.cpp ./src/templatedb/unitTests.cpp ./src/BloomFilter/murmurhash.cpp ./src/BloomFilter/BloomFilter.cpp

performanceTest: ./src/templatedb/lsm.cpp ./src/templatedb/performanceTest.cpp ./src/BloomFilter/murmurhash.cpp ./src/BloomFilter/BloomFilter.cpp
	g++ -std=c++11 -o performanceTest.out ./src/templatedb/lsm.cpp ./src/templatedb/performanceTest.cpp ./src/BloomFilter/murmurhash.cpp ./src/BloomFilter/BloomFilter.cpp