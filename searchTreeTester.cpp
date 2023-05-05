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

 SearchTree* SearchTreeTester::allocateTree()
{
    return new SearchTree;
}

 void SearchTreeTester::check_addAndCount(const SearchTree &tree, const int size)
{
    BinaryTreeTester::check_addAndCount(tree, size);
    isSearchTree(tree);
}

 void SearchTreeTester::isSearchTree(const BinaryTree &tree)
{
  std::vector<int> nodeKeys = tree.getTreeKeys();
  for (int i = 0; i < nodeKeys.size() - 1; i++)
    {
        assert(nodeKeys[i] <= nodeKeys[i + 1]);
    }
}

 void SearchTreeTester::check_clear(const SearchTree& tree, const int size)
{
  BinaryTreeTester::check_clear(tree , size);
  isSearchTree(tree);
}


 void SearchTreeTester::check_height(const SearchTree &tree, const int height)
{
   BinaryTreeTester::check_height(tree,height);
   isSearchTree(tree);
}

 
 void SearchTreeTester::check_remove(const SearchTree &tree, const int size)
{
  BinaryTreeTester::check_remove(tree,size);
  isSearchTree(tree);
}
