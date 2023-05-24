#include "test.h"
#include <assert.h>
#include <algorithm>
#include <vector>
#include <random>

 void SearchTreeTester::test(const int size)
{
    m_maxSize = size;
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();
}

BinaryTree* SearchTreeTester::allocateTree()
{
    return new SearchTree;
}

void SearchTreeTester::check_addAndCount(const BinaryTree &tree, const int size)
{
    BinaryTreeTester::check_addAndCount(tree, size);
    isSearchTree(tree);
}

void SearchTreeTester::isSearchTree(const BinaryTree &tree)
{
  std::vector<int> nodeKeys = tree.getTreeKeys();
  if ( nodeKeys.size() == 0)
    return;
  else
  {
      for (int i = 0; i < nodeKeys.size() - 1; i++)
      {
        assert(nodeKeys[i] <= nodeKeys[i + 1]);
      }
  }

}

void SearchTreeTester::check_clear(const BinaryTree& tree, const int size)
{
  BinaryTreeTester::check_clear(tree , size);
  isSearchTree(tree);
}

void SearchTreeTester::check_height(const BinaryTree &tree, const int height)
{
   BinaryTreeTester::check_height(tree,height);
}

 
void SearchTreeTester::check_remove(const BinaryTree &tree, const int size)
{
  BinaryTreeTester::check_remove(tree,size);
  isSearchTree(tree);
}
