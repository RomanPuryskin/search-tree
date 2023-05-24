#include "test.h"
#include <random>
#include <stdlib.h>

int main() 
{
  
/*  SearchTree tree;
  for(int i=0;i<9;i++)
    {
      tree.addNode(rand() % 99);
    }
  tree.PrintTree(2,3);
*/

 /* SearchTreeTester tester;
    for (int size = 10; size < 50; size += 10) {
        tester.test(size);
    }*/

  std::vector<int> keys = {10,20,30,40};
  std::vector<int> freq = {2,1,1,5};
  std::vector<int> extraFreq = {1,10,1,1,10};

  SearchTree tree;
  tree.createOptimalTree(keys , freq , extraFreq);
  tree.PrintTree(2,3);
}