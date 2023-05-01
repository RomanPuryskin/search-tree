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
   // isSearchTree();
}

 SearchTree* SearchTreeTester::allocateTree()
{
    return new SearchTree;
}
 
 void SearchTreeTester::deallocateTree(SearchTree * tree)
{
    delete tree;
}

 void SearchTreeTester::addAndCount()
{
  SearchTree* tree = allocateTree();
    check_addAndCount(*tree, 0);
 
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree->addNode(i);
        check_addAndCount(*tree, i + 1);
    }
    deallocateTree(tree);
}
 void SearchTreeTester::check_addAndCount(const SearchTree &tree, const int size)
{
    assert(tree.Count()== size);
}

 void SearchTreeTester::isSearchTree()
{
  SearchTree* tree = allocateTree();
  std::vector<int> nodeKeys = tree->getTreeKeys();
  deallocateTree(tree);
  for (int i = 0; i < nodeKeys.size() - 1; i++)
    {
        assert(nodeKeys[i] <= nodeKeys[i + 1]);
    }
}


 void SearchTreeTester::destructor()
{
    for (int j = 0; j < 1000; ++j)
    {
        SearchTree* tree = allocateTree();
        for (int i = 0; i < m_maxSize; ++i) {
            tree->addNode(i);
        }
        deallocateTree(tree);
    }
}

 void SearchTreeTester::clear()
{
    SearchTree* tree = allocateTree();
    tree->deleteAllTree();
    check_clear(*tree, 0);
    for (int i = 0; i < m_maxSize; i++)
    {
        tree->addNode(i);
    }

    check_clear(*tree, m_maxSize);
    tree->deleteAllTree();
    check_clear(*tree, 0);
    deallocateTree(tree);
}
 void SearchTreeTester::check_clear(const SearchTree& tree, const int size)
{
    assert(tree.Count() == size);
}


 void SearchTreeTester::assign()
{
    SearchTree *tree1 = allocateTree();
    for (int i = 0; i < m_maxSize; ++i) {
        tree1->addNode(i);
    }
 
    SearchTree* tree2 = allocateTree();
    *tree2 = *tree1;
    std::vector<int> tree1keys = tree1->getTreeKeys();
    std::vector<int> tree2keys = tree2->getTreeKeys();
    check_assign(tree1keys, tree2keys);
 
    *tree1 = *tree2; 
    tree1keys = tree1->getTreeKeys();
    tree2keys = tree2->getTreeKeys();
    check_assign(tree1keys, tree2keys);
 
    deallocateTree(tree1);
    deallocateTree(tree2);
}


 void SearchTreeTester::height()
{
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

 void SearchTreeTester::check_height(const SearchTree &tree, const int height)
{
    assert(tree.height() == height);
}

 void SearchTreeTester::height_trivialCases()
{
    SearchTree tree;
    check_height(tree, 0);
    tree.addNode(0);
    check_height(tree, 1);
}
 void SearchTreeTester::height_longOnlyLeftSubtree()
{
    SearchTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->SetLeft(new BinaryTree::Node(i));
        runner = runner->GetLeft();
        check_height(longTree, i + 1);
    }
}
 void SearchTreeTester::height_longOnlyRightSubtree()
{
    SearchTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->SetRight(new BinaryTree::Node(i));
        runner = runner->GetRight();
        check_height(longTree, i + 1);
    }
}
 void SearchTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    SearchTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *leftRunner = longTree.getRoot();
    BinaryTree::Node *rightRunner = longTree.getRoot();
    for (int i = 1; i < m_maxSize/2; ++i) {
        leftRunner->SetLeft(new BinaryTree::Node(i));
        leftRunner = leftRunner->GetLeft();
        check_height(longTree, i + 1);
 
 
        rightRunner->SetRight(new BinaryTree::Node(i));
        rightRunner = rightRunner->GetRight();
        check_height(longTree, i + 1);
    }
}
 void SearchTreeTester::height_longRandomZigzagSubtrees()
{
    SearchTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *leftRunner = longTree.getRoot();
    BinaryTree::Node *rightRunner = longTree.getRoot();
 
    leftRunner->SetLeft(new BinaryTree::Node(1));
    leftRunner = leftRunner->GetLeft();
    rightRunner->SetRight(new BinaryTree::Node(1));
    rightRunner = rightRunner->GetRight();
 
    for (int i = 2; i < m_maxSize/2; ++i) {
        if (rand() % 2 == 0) 
        {
            leftRunner->SetLeft(new BinaryTree::Node(i));
            leftRunner = leftRunner->GetLeft();
        }
        else 
        {
            leftRunner->SetRight(new BinaryTree::Node(i));
            leftRunner = leftRunner->GetRight(); 
        }
        check_height(longTree, i + 1);
 
        if (rand() % 2 == 0)
        {
            rightRunner->SetLeft(new BinaryTree::Node(i));
            rightRunner = rightRunner->GetLeft();
        }
        else 
        {
            rightRunner->SetRight(new BinaryTree::Node(i));
            rightRunner = rightRunner->GetRight(); 
        }
        check_height(longTree, i + 1);
    }
}

 void SearchTreeTester::remove()
{
    int invalidKey = -1;
    std::vector<int> nodeKeys;
    SearchTree* tree = allocateTree();
    tree->deleteNode(invalidKey);
 
    for (int i = 0; i < m_maxSize; ++i) 
    {
        nodeKeys.push_back(i);
        tree->addNode(i);
    }

   while (!nodeKeys.empty()) 
   {

        int removedNodeIndex = rand() % nodeKeys.size(); //3

        tree->deleteNode(invalidKey);
        check_remove(*tree, nodeKeys.size());

        tree->deleteNode(nodeKeys[removedNodeIndex]);
       //std::cout << nodeKeys[removedNodeIndex] << ":\n";
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        check_remove(*tree, nodeKeys.size());

       // std::cout<<tree->Count()<<"\n";
       // std::cout<<nodeKeys.size()<<"\n";
       // tree->PrintTree(2,3);
    }
    tree->deleteNode(invalidKey);
    check_remove(*tree, nodeKeys.size());
    deallocateTree(tree);
}
 
 void SearchTreeTester::check_remove(const SearchTree &tree, const int size)
{
    assert(tree.Count() == size);
}
