/*
Name: Blazej Byczkowski
Matric number: 170019249
Module code: AC21008
 */
#ifndef MY_HASH_NODE
#define MY_HASH_NODE

#include <iostream>

using namespace std;

class HashNode {
  unsigned long key;   // The hash node's key
  unsigned long value; // The key's associated data
  /* extend if necessary */

public:

  // Add constructors, destructor if necessary
  HashNode();
  ~HashNode();
  unsigned long getKey() { return key; }
  unsigned long getValue() { return value; }
  void assign(unsigned long key, unsigned long value);

  // extend if necessary
};

/*
   Implement the assign method
   and any methods that you may additionally need for the HashTable to work.
*/
HashNode::HashNode()
{
    /*
    cout<<"creating node"<<endl;
     */
}

HashNode::~HashNode(){
  /*
  cout<<"deleted"<<endl;
   */
}      // deconstructor

void HashNode::assign(unsigned long key1, unsigned long value1){
  key=key1;
  value=value1;
}

#endif
