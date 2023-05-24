#pragma once
#include "searchTree.h"

class BinaryTreeTester
{
public:
    BinaryTreeTester() = default;
    virtual ~BinaryTreeTester() = default;
 
    virtual void test(const int size);

protected:

    virtual BinaryTree* allocateTree();
    void deallocateTree(BinaryTree* tree);
    
    virtual void check_addAndCount(const BinaryTree &tree, const int size);
    virtual void check_remove(const BinaryTree &tree, const int size);
    virtual void check_clear(const BinaryTree &tree, const int size);
    void check_assign(const std::vector<int> lhs, const std::vector<int> rhs);
    virtual void check_height(const BinaryTree &tree, const int size);

    void addAndCount();
    void destructor();
    void remove();
    void clear(); 
    void assign();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();
protected:
    int m_maxSize;
};

class SearchTreeTester : public BinaryTreeTester
{
public:
    SearchTreeTester() = default;
    ~SearchTreeTester() override  = default;
    void test(const int size) override;
    BinaryTree* allocateTree() override;
    void isSearchTree(const BinaryTree &tree);
    void check_addAndCount(const BinaryTree &tree, const int size) override;
    void check_remove(const BinaryTree &tree, const int size) override;
    void check_clear(const BinaryTree &tree, const int size) override;
    void check_height(const BinaryTree &tree, const int size) override;
};