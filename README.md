# Forked Repo

# CS 591 A1: Data Systems Architecture - LSM Tree Implementation


## About

The log-structured merge-tree (LSM-tree) has become the mainstream core data structure used by key-value stores to ingest and persist data quickly. It has been widely used as a data structure in many of the most popular key-value store DBMS such as RocksDB, Cassandra and Elastic Search. Here is our implementation of an LSM Tree.


## Requirements

You will need the following on your system (or alternatively develop on the
CSA machines)

    1. CMake
    2. C++ Compiler

## Usage

To compile the unit tests, you can simply run:
```
make unitTest
```
in the root directory and a file named ```unitTest.out``` will be produced. You can run the file by running:
```
./unitTest.out
```

To compile the performance tests, you can simply run:
```
make performanceTest
```
in the root directory and a file named ```performaceTest.out``` will be produced. You can run the file by running:
```
./performanceTest.out
```

## Contact

If you have any quetions, feel free to email us as paschali@bu.edu or ksirivad@bu.edu.
