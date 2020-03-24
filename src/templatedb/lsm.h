#ifndef LSM_H
#define LSM_H

#include <iostream>
#include <string>

using namespace std;

typedef struct _node{
  int key;
  int val;
} node;

typedef struct _lsm{
  size_t block_size; // This is the number of nodes each block can hold.
  int k; // The LSM tree grows in dimension k.
  size_t next_empty;
  node *block;
  string disk1;
} lsm;

typedef struct _nodei{
  node *node;
  int index;
} nodei;

lsm* init_new_lsm(size_t bufferSize);

#endif