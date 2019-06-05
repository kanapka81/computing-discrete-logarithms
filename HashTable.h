/*
Name: Blazej Byczkowski
Matric number: 170019249
Module code: AC21008
 */
#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <list>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

typedef unsigned long ulint;

class HashTable {
  typedef vector <list<HashNode> > Table;
  Table *table; // size of table is stored in the Table data structure
  size_t num;   // number of entries in the HashTable;

public:
  HashTable();       // constructor, initializes table of size 1;
  HashTable(size_t); // constructor, requires size of table as arg
  ~HashTable();      // deconstructor

  size_t size(); // returns size of the hash table (number of buckets)

  size_t hash_function(ulint);  // the table's hash function
  ulint getValue(ulint);    // find and return data associated with key

  void insert(ulint,ulint); // insert data associated with key into table
  void erase(ulint);        // remove key and associated data from table

  size_t getNum();  //return number of entries in the HashTable
  void setNum(size_t);  //set number of entries in the HashTable
  void rehash(size_t); // sets a new size for the hash table, rehashes the hash table
  // extend if necessary

  bool isKey(ulint); //look for a key in HasTable; if found, return true; else false
};

/* Implement the
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods
*/
/* implementing hash table functions */
HashTable::HashTable()
{
    table=new vector <list<HashNode> >;
    table->resize(11*sizeof(HashNode));
    setNum(0);
    /*
    cout<<"resizing"<<endl;
     */
}

HashTable::HashTable(size_t b)
{
    table=new vector <list<HashNode> >(b);
    table->resize(b*sizeof(HashNode));
    setNum(0);
    /*
    cout<<"resizing2"<<endl;
     */
}
HashTable::~HashTable(){
  /*
  cout<<"deleted"<<endl;
   */
}      // deconstructor

// returns size of the hash table (number of buckets)
size_t HashTable::size(){
  return table->size()/sizeof(HashNode);
}

// the table's hash function
size_t HashTable::hash_function(ulint input){
  size_t output=input%size();
  /*
  cout<<size()<<" size hash func"<<endl;
   */
  /*
  cout<<output<<" output of hash func"<<endl;
   */
  return output;
}
//return number of entries in the HashTable
size_t HashTable::getNum(){
  return num;
}
//set number of entries in the HashTable
void HashTable::setNum(size_t newNum){
  num=newNum;
}
// insert data associated with key into table
void HashTable::insert(ulint key,ulint data){
  int index = hash_function(key);
  /*
  cout<<index<<" output of hash func in insert"<<endl;
   */
  /* Creating an item to insert in the List */
	//HashNode *item = (HashNode*) malloc(sizeof(HashNode));
  HashNode* item = new HashNode;
  //HashNode *item;
  //Table entry = table[index];
  //Table sentry = table.at(index);
  list<HashNode> test = table->at(index);
  if (test.empty()){
    	/* Absence of Linked List at a given Index of Hash Table */
      /*
      cout<<"insert to empty LL"<<endl;
       */
      item->assign(key,data);
      table->at(index).push_back(*item); //!!!!!! important! dont use test, assigning to wrong table all the time
      test.front().assign(key,data);
      /*
      cout<<"inputted key "<<test.back().getKey()<<endl;
      cout<<"inputted value "<<test.back().getValue()<<endl;
      cout<<"does it work? size "<<test.size()<<endl;
      */
      setNum(getNum()+1);
    }
  else{
  	/* Linked List at a given Index of Hash Table exists*/
    /*
    *item=table->at(index).front();
    while(item->getKey()!=0){
      next(item);
    }
    item->assign(key,data);
    table->at(index).back().push_back(*item);
    */
    item->assign(key,data);
    table->at(index).push_back(*item);
    setNum(getNum()+1);
  }
  if(getNum()/size()>0.89){
    rehash(size()*2);
  }
}
// find and return data associated with key
ulint HashTable::getValue(ulint key){
  int index = hash_function(key);
  list<HashNode> test = table->at(index);
  /*
  cout<<"index in getvalue is "<<index<<endl;
  cout<<"size of LL on this index is "<<table->at(index).size()<<endl;
  */
  for (std::list<HashNode>::iterator it=test.begin(); it != test.end(); ++it){
    /*
    cout<<"it->getKey() is "<<it->getKey()<<endl;
     */
    if (it->getKey() == key) {
        /*
        cout<<"found key"<<endl;
         */
        return it->getValue();
    }
  }
  return KEY_NOT_FOUND;
}
void HashTable::erase(ulint key){
  int index = hash_function(key);
  /*
  cout<<"index in erase is "<<index<<endl;
  cout<<"size of LL on this index is "<<table->at(index).size()<<endl;
  */
  for (std::list<HashNode>::iterator it=table->at(index).begin(); it != table->at(index).end(); ++it){
    if (it->getKey() == key) {
        table->at(index).erase(it);
        /*
        cout<<"found key and erased: "<<it->getKey()<<endl;
         */
        setNum(getNum()-1);
        break;
    }
  }
}
// sets a new size for the hash table, rehashes the hash table
void HashTable::rehash(size_t size){
  //create new hashtable of new size given
  HashTable *table1 = new HashTable;
  table1->table->resize(size*sizeof(HashNode));
  /*
  cout<<"#{#{#{#{#{#{#{#{#{#{REHASHING}}}}}}}}}}"<<endl;
   */

  //iterate through vector
  for (size_t i = 0; i < table->size(); i++) {
    //iterate through List (no iterations if empty
    for (std::list<HashNode>::iterator it=table->at(i).begin(); it != table->at(i).end(); ++it){
      //
      ulint index = it->getKey();
      ulint data = it->getValue();
      table1->insert(index, data);
      //table1->setNum(getNum()+1);
    }
  }
  table1->table->swap(*table);
}
//look for a key in HasTable; if found, return true; else false
bool HashTable::isKey(ulint key){
    int index = hash_function(key);
    list<HashNode> test = table->at(index);
    /*
    cout<<"index in getvalue is "<<index<<endl;
    cout<<"size of LL on this index is "<<table->at(index).size()<<endl;
    */
    for (std::list<HashNode>::iterator it=test.begin(); it != test.end(); ++it){
      /*
      cout<<"it->getKey() is "<<it->getKey()<<endl;
       */
      if (it->getKey() == key) {
          /*
          cout<<"found key"<<endl;
           */
          return true;
      }
  }
  return false;
}

#endif
