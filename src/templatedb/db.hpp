#ifndef _TEMPLATEDB_DB_H_
#define _TEMPLATEDB_DB_H_

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "./operation.hpp"

namespace templatedb
{

typedef enum _status_code
{
    OPEN = 0,
    CLOSED = 1,
    ERROR_OPEN = 100,
} db_status;

typedef struct _node{
  int key;
  int val;
} node;

typedef struct _lsm{
  size_t block_size; // This is the number of nodes each block can hold.
  int k; // The LSM tree grows in dimension k.
  int node_size;
  size_t next_empty;
  node *block;
  char* disk1;
//   bool sorted;

} lsm;

typedef struct _nodei{
  node *node;
  int index;
} nodei;

class Value
{
public:
    std::vector<int> items;
    bool visible = true;

    Value() {}
    Value(bool _visible) {visible = _visible;}
    Value(std::vector<int> _items) { items = _items;}

    bool operator ==(Value const & other) const
    {
        return (visible == other.visible) && (items == other.items);
    }
};


class DB
{

public:
    db_status status;

    DB() {};
    ~DB() {close();};

    void init_new_lsm(size_t buffer_size);

    Value get(int key);
    void put(int key, Value val);
    std::vector<Value> scan();
    std::vector<Value> scan(int min_key, int max_key);
    void del(int key);
    size_t size();
    
    db_status open(std::string & fname);
    bool close();

    bool load_data_file(std::string & fname);

    std::vector<Value> execute_op(Operation op);

private:
    std::fstream file;
    std::unordered_map<int, Value> table;
    lsm* tree;
    size_t value_dimensions = 0;

    bool write_to_file();
};

}   // namespace templatedb

#endif /* _TEMPLATEDB_DB_H_ */