#include "test.h"
#include <assert.h>
#include <algorithm>
#include <vector>
#include <random>

void BinaryTreeTester::test(const int size)
{
    m_maxSize = size;
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();
}

BinaryTree* BinaryTreeTester::allocateTree()
{
    return new BinaryTree;
}
 
void BinaryTreeTester::deallocateTree(BinaryTree * tree)
{
    delete tree;
}

void BinaryTreeTester::addAndCount()
{
  BinaryTree* tree = allocateTree();
    check_addAndCount(*tree, 0);
 
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree->addNode(i);
        check_addAndCount(*tree, i + 1);
    }
    deallocateTree(tree);
}
void BinaryTreeTester::check_addAndCount(const BinaryTree &tree, const int size)
{
    assert(tree.Count()== size);
}


void BinaryTreeTester::destructor()
{
    for (int j = 0; j < 1000; ++j)
    {
        BinaryTree* tree = allocateTree();
        for (int i = 0; i < m_maxSize; ++i) {
            tree->addNode(i);
        }
        deallocateTree(tree);
    }
}

void BinaryTreeTester::clear()
{
    BinaryTree* tree = allocateTree();
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
void BinaryTreeTester::check_clear(const BinaryTree& tree, const int size)
{
    assert(tree.Count() == size);
}


void BinaryTreeTester::assign()
{
    BinaryTree *tree1 = allocateTree();
    for (int i = 0; i < m_maxSize; ++i) {
        tree1->addNode(i);
    }
 
    BinaryTree* tree2 = allocateTree();
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

void BinaryTreeTester::check_assign(const std::vector<int> keys1, const std::vector<int> keys2)
{
    assert(keys1.size() == keys2.size());
    for (unsigned int i = 0; i < keys1.size(); i++)
    {
        assert(keys1[i] == keys2[i]);
    }
}

void BinaryTreeTester::height()
{
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTester::check_height(const BinaryTree &tree, const int height)
{
    assert(tree.height() == height);
}

void BinaryTreeTester::height_trivialCases()
{
    BinaryTree tree;
    check_height(tree, 0);
    tree.addNode(0);
    check_height(tree, 1);
}
void BinaryTreeTester::height_longOnlyLeftSubtree()
{
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->SetLeft(new BinaryTree::Node(i));
        runner = runner->GetLeft();
        check_height(longTree, i + 1);
    }
}
void BinaryTreeTester::height_longOnlyRightSubtree()
{
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->SetRight(new BinaryTree::Node(i));
        runner = runner->GetRight();
        check_height(longTree, i + 1);
    }
}
void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    BinaryTree longTree;
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
void BinaryTreeTester::height_longRandomZigzagSubtrees()
{
    BinaryTree longTree;
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

void BinaryTreeTester::remove()
{
    int invalidKey = -1;
    std::vector<int> nodeKeys;
    BinaryTree* tree = allocateTree();
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
    //   std::cout << nodeKeys[removedNodeIndex] << ":\n";
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        check_remove(*tree, nodeKeys.size());

     //   std::cout<<tree->Count()<<"\n";
     //   std::cout<<nodeKeys.size()<<"\n";
      //  tree->PrintTree(2,3);
    }
    tree->deleteNode(invalidKey);
    check_remove(*tree, nodeKeys.size());
    deallocateTree(tree);
}
 
void BinaryTreeTester::check_remove(const BinaryTree &tree, const int size)
{
    assert(tree.Count() == size);
}