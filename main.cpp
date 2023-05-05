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
  tree.deleteNode(70);
  tree.PrintTree(2,3);*/

  //std::cout<<pupmin<<" "<<pupmax;
  SearchTreeTester tester;
    for (int size = 10; size < 50; size += 10) {
        tester.test(size);
    }
}