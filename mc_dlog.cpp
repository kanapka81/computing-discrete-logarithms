/*
Name: Blazej Byczkowski
Matric number: 170019249
Module code: AC21008
 */
#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <list>
#include <vector>
#include <cmath>
#include "HashTable.h"

using namespace std;
/* Implement mc_dlog in this file */

/*
given the numbers
g, a, n, outputs with high probability the correct solution x
to the equation
g^x = a mod n.
*/

/*
a^b %n
Primality Testing method via https://www.topcoder.com/community/competitive-programming/tutorials/primality-testing-non-deterministic-algorithms/
 */
int modulo(int a, int b, int n){
    ulint x=1, y=a;
    while (b > 0) {
        if (b%2 == 1) {
            x = (x*y) % n; // multiplying with base
        }
        y = (y*y) % n; // squaring the base
        b /= 2;
    }
    return x % n;
}

int main(int argc, char const *argv[]) {

  //check if user provided 3 numbers as input
  if(argc!=4){
    cerr<<"Please provide 3 numbers as input. Wrong input error";
    return -1;
  }
  /*
  convert command-line arguments to ints
  input validation included
   */
  ulint g,a,n,r,y,order=0;
  stringstream value1, value2, value3;
  value1 << argv[1];
  if (!(value1 >> g)) {
    std::cerr << "Invalid number: " << argv[1] << '\n';
    return -1;
  } else if (!value1.eof()) {
    std::cerr << "Trailing characters after number: " << argv[1] << '\n';
    return -1;
  }
  value2 << argv[2];
  if (!(value2 >> a)) {
    std::cerr << "Invalid number: " << argv[2] << '\n';
    return -1;
  } else if (!value2.eof()) {
    std::cerr << "Trailing characters after number: " << argv[2] << '\n';
    return -1;
  }
  value3 << argv[3];
  if (!(value3 >> n)) {
    std::cerr << "Invalid number: " << argv[3] << '\n';
    return -1;
  } else if (!value3.eof()) {
    std::cerr << "Trailing characters after number: " << argv[3] << '\n';
    return -1;
  }

  //initialise HashTable Ord
  HashTable Ord;

  /*
  Part 1
  calculate the order of g
  */
  // construct a trivial random generator engine from a time-based seed:
 unsigned seed = time(NULL);
 default_random_engine generator (seed);
 uniform_int_distribution<int> distribution(0,n-1);
 ulint i=1;

  for (i=0; i<sqrt(n); i++){
    //pick r randomly from 0 to n-1
    r = distribution(generator);
    //calculate y=g^r %n
    y=modulo(g,r,n);
    if(Ord.isKey(y)){
      /*
      careful, unsigned long int can't be negative
       */
      if(r>Ord.getValue(y)){
        order = r-Ord.getValue(y);
        break;
      }else if(Ord.getValue(y)>r){
        order = Ord.getValue(y)-r;
        break;
      }
    }else{
      Ord.insert(y,r);
    }
  }
  if(order==0){
    order=n-1;
  }
    /*
    END OF PART 1
    order of g calculated as /int order/
    */
    /*
    Part 2
    Finding the discrete algorithm
    */
    //initialise two HashTables, A and B
    HashTable A;
    HashTable B;
    ulint log = 0;
    /*
    cout<<"------PART2--------"<<endl;
     */
    // construct a trivial random generator engine from a time-based seed:
   unsigned seeds = time(NULL);
   default_random_engine generators (seeds);
   uniform_int_distribution<int> distributions(0,n-1);
   ulint z=1;
    for (z=0; z<sqrt(n); z++){
      //pick r randomly from 0 to n-1
      r = distribution(generator);
      //calculate y=g^r %n
      y=modulo(g,r,n);
      y=y*a%n;
      if(B.isKey(y)){
        if(B.getValue(y)>r){
          log = B.getValue(y)-r;
          break;
        }else{
          log = order+B.getValue(y)-r;
          break;
        }
      }else{
        A.insert(y,r);
      }
      /*
      cout<<"------PART2 of PART2--------"<<endl;
       */
      //pick r randomly from 0 to n-1
      r = distribution(generator);

      //calculate y=g^r %n
      y=modulo(g,r,n);
      if(A.isKey(y)){
        if(r>A.getValue(y)){
          log = r-A.getValue(y);
          break;
        }else{
          log = order+r-A.getValue(y);
          break;
        }
      }else{
        B.insert(y,r);
      }
    }

      cout<<log%order<<endl;

  return 0;
}
