#pragma once
#include "searchTree.h"
class BinaryTreeTester
{
public:
    BinaryTreeTester() = default;
    virtual ~BinaryTreeTester() = default;
 
    virtual void test(const int size);

    BinaryTree* allocateTree();
    void deallocateTree(BinaryTree* tree);
    
    void check_addAndCount(const BinaryTree &tree, const int size);
    void check_remove(const BinaryTree &tree, const int size);
    void check_clear(const BinaryTree &tree, const int size);
    void check_assign(const std::vector<int> lhs, const std::vector<int> rhs);
    void check_height(const BinaryTree &tree, const int size);

    virtual void addAndCount();
    virtual void destructor();
    virtual void remove();
    virtual void clear(); 
    virtual void assign();
    virtual void height();
    virtual void height_trivialCases();
    virtual void height_longOnlyLeftSubtree();
    virtual void height_longOnlyRightSubtree();
    virtual void height_longOnlyLeftAndRightSubtrees();
    virtual void height_longRandomZigzagSubtrees();
protected:
    int m_maxSize;
};

class SearchTreeTester : public BinaryTreeTester
{
public:
    SearchTreeTester() = default;
    ~SearchTreeTester() override  = default;
    void test(const int size) override;
    SearchTree* allocateTree();
    void addAndCount() override;
    void destructor() override;
    void clear() override;
    void assign() override;
    void height() override;
    void remove() override;
    void height_trivialCases() override;
    void height_longOnlyLeftSubtree() override;
    void height_longOnlyRightSubtree() override;
    void height_longOnlyLeftAndRightSubtrees() override;
    void height_longRandomZigzagSubtrees() override;
    void deallocateTree(SearchTree* tree);
    void isSearchTree();
    void check_addAndCount(const SearchTree &tree, const int size);
    void check_remove(const SearchTree &tree, const int size);
    void check_clear(const SearchTree &tree, const int size);
    void check_height(const SearchTree &tree, const int size);
};