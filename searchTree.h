#pragma once
#include <iostream>
#include <vector>

class BinaryTree {
public:
  class Node {
  private:
    int m_key;
    Node *m_left;
    Node *m_right;

  public:
    ~Node() = default;

    Node() {
      m_key = 0;
      m_left = nullptr;
      m_right = nullptr;
    }

    Node(int key) {
      m_key = key;
      m_left = nullptr;
      m_right = nullptr;
    }

    int GetKey() { return m_key; }

    void SetKey(int key) { m_key = key; }

    Node *GetLeft() { return m_left; }

    Node *GetRight() { return m_right; }

    void SetLeft(Node *left) { m_left = left; }

    void SetRight(Node *right) { m_right = right; }

    int ChildAmount() {
      int amount = 0;
      if (GetLeft() != nullptr)
        amount++;
      if (GetRight() != nullptr)
        amount++;

      return amount;
    }
  };
  BinaryTree() { m_root = nullptr; }
  virtual ~BinaryTree();
  void DestroyTree(Node *root);
  void DestroyTree();
  void deleteSubTree(Node *root);
  void deleteAllTree();
  BinaryTree(const BinaryTree &copy);
  Node *copyTree(Node *root);
  bool isEmpty(Node *root);
  bool isEmpty();
  virtual Node *addNode(Node *root, int key);
  virtual Node *addNode(int key);
  Node *getRoot();
  int Count(Node *root) const;
  int Count() const;
  void PrintTree(Node *root, int marginLeft, int Space) const;
  void PrintTree(int marginLeft, int Space) const;
  void PrintLeaves(Node *root) const;
  void PrintLeaves();
  std::vector<int> getTreeKeys() const;
  void getTreeKeys(Node *root, std::vector<int> &treeKeys) const;
  virtual int searchMinKey();
  virtual int searchMaxKey();
  virtual int height(Node *root) const;
  virtual int height() const;
  int sumKeys(Node *root);
  int sumKeys();
  virtual Node *searchNode(Node *root, int key);
  virtual int GetHeightKey(int key);
  BinaryTree &operator=(const BinaryTree &other);
  bool balancedTree(Node *root);
  bool balancedTree();
  Node *findParent(Node *node, Node *temp);
  void deleteNode(Node *node);
  virtual bool deleteNode(int key);

protected:
  Node *m_root = nullptr;
};

class SearchTree : public BinaryTree {
public:
  SearchTree() { m_root = nullptr; }
  ~SearchTree() override = default;
  using BinaryTree::Node;
  Node *addNode(Node *root, int key) override;
  Node *addNode(int key) override;
  int searchMinKey(Node *root);
  int searchMinKey() override;
  int searchMaxKey(Node *root);
  int searchMaxKey() override;
  int height(Node *root) const override;
  int height() const override;
  Node *searchNode(Node *root, int key) override;
  Node *searchNode(int key);
  int GetHeightKey(int key) override;
  void deleteNode(Node *node, int key);
  bool deleteNode(int key) override;
  Node *minNode(Node *root);
  Node* createOptimalTree(std::vector<int> &keys, std::vector<int> &freq, std::vector<int> &extraFreq);
  Node *createOptimalTree(std::vector<int> &keys,int** matrix,int i , int j);
};