#include "test.h"
int main() 
{
  int pupmin , pupmax;
  SearchTree tree;
  for(int i=10;i>2;i--)
    tree.addNode(i);
 // tree.deleteNode(8);
  tree.PrintTree(2,3);
  
  pupmin = tree.searchMinKey();
  pupmax = tree.searchMaxKey();
  pupmax = tree.GetHeightKey(2);
  //std::cout<<pupmin<<" "<<pupmax;
  SearchTreeTester tester;
    for (int size = 10; size < 50; size += 10) {
        tester.test(size);
    }
}