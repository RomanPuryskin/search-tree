#include "searchTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//--------------------Добавление элемента------------------//
BinaryTree::Node *SearchTree::addNode(Node *root, int key)
{
    if (!root) {
        root = new Node(key);
    } else if (key < root->GetKey()) {
        root->SetLeft(addNode(root->GetLeft(), key));
    } else {
        root->SetRight(addNode(root->GetRight(), key));
    }
 
    return root;
}

BinaryTree::Node *SearchTree::addNode(int key)
{
    m_root = addNode(m_root, key);
    return m_root;
}
//------------------------------------------------------------//

//---------------------Поиск минимального элемента---------------------//
int SearchTree::searchMinKey(Node *root)
{
  if (root->GetLeft() != nullptr)
    return searchMinKey(root->GetLeft());
  else
    return root->GetKey();
}

int SearchTree::searchMinKey()
{
  return searchMinKey(m_root);
}
//----------------------------------------------------------------------//


//---------------------Поиск максимального элемента---------------------//
int SearchTree::searchMaxKey(Node *root)
{
  if (root->GetRight() != nullptr)
    return searchMaxKey(root->GetRight());
  else
    return root->GetKey();
}

int SearchTree::searchMaxKey()
{
  return searchMaxKey(m_root);
}
//----------------------------------------------------------------------//

//----------------------Поиск узла по ключу--------------------------//
BinaryTree::Node *SearchTree::searchNode(Node* root, int key)
{
    if (root == nullptr || root->GetKey() == key)
        return root;
 
    if (root->GetKey() < key)
        return searchNode(root->GetRight(), key);
 
    return searchNode(root->GetLeft(), key);
}

BinaryTree::Node *SearchTree::searchNode(int key)
{
  return searchNode(m_root ,key);
}
//--------------------------------------------------------------------//


//------------------------Удаление узла----------------------//
void SearchTree::deleteNode(Node *node , int key) 
{

  Node *parent = findParent(node, m_root);
  if (parent == nullptr && node != m_root)
  {
    return;
  }
  
  Node *replace = nullptr;
  Node *temp = nullptr;
  // у узла нет потомков
  if (node->GetLeft() == nullptr && node->GetRight() == nullptr)
    replace = nullptr;
    
  // у удаляемого узла только правый потомок
  else if (node->GetLeft() == nullptr && node->GetRight() != nullptr)
  {
    temp = node->GetRight();
    while (temp->GetLeft() != nullptr)
      temp = temp->GetLeft();
    replace = temp;

    Node *tempParent = findParent(temp, m_root);
    if (tempParent != node) 
    {
        tempParent->SetRight(replace->GetLeft());
        replace->SetRight(node->GetRight());
    }
    replace->SetLeft(node->GetLeft());
  }

  // у удаляемого узла только левый потомок
  else if (node->GetRight() == nullptr && node->GetLeft() != nullptr)
  {
    temp = node->GetLeft();
    while (temp->GetRight() != nullptr)
      temp = temp->GetRight();
    replace = temp;

    Node *tempParent = findParent(temp, m_root);
    if (tempParent != node) 
    {
      tempParent->SetRight(replace->GetLeft());
      replace->SetRight(node->GetRight());
    }
    replace->SetLeft(node->GetLeft());
  }
  // у удаляемого узла два потомка
  else
  {
    temp = node->GetRight();
    while (temp->GetLeft() != nullptr)
      temp = temp->GetLeft();
    replace = temp;

    //найдем родителя у узла для замены
    Node *tempParent = findParent(temp, m_root);
    if (tempParent != node) {
      tempParent->SetLeft(replace->GetRight());
      replace->SetRight(node->GetRight());
    }
    replace->SetLeft(node->GetLeft());
  }

  if( parent != nullptr)
  { 
    if (parent->GetLeft() == node)
      parent->SetLeft(replace);
    else
      parent->SetRight(replace);
    delete node;
  }
  else
  {
    delete m_root;
    m_root = replace;
  }

}


bool SearchTree::deleteNode(int key) {
  Node *node = searchNode(key);
  if (!node)
    return false;

  deleteNode(node , key);
  return true;
}
//-----------------------------------------------------------//

//-------------------Получение высоты дерева-------------------//
 int SearchTree::height(Node *root) const
  {
    if(root == nullptr)
      return 0;
    return 1 + std::max( height(root->GetLeft()) , height(root->GetRight()) );
  }

 int SearchTree::height() const
{
  return height(m_root);
}
//-------------------------------------------------------------//


//-----------------Получение уровня вершины-----------------//
 int SearchTree::GetHeightKey(int key)
  {
    Node *temp = searchNode(m_root, key);
    if( temp == nullptr)
      return -1;
    else
      return (height(m_root) - height(temp));
  }
//----------------------------------------------------------//