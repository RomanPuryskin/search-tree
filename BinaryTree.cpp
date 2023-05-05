
#include "searchTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


//-----------Деструктор---------------//
 BinaryTree::~BinaryTree()
  {
    DestroyTree(m_root);
  }


 void BinaryTree::DestroyTree(Node *root)
  {
    if(root)
      {
        DestroyTree(root->GetLeft());
        DestroyTree(root->GetRight());
        delete root;
      }
  }

 void BinaryTree::DestroyTree()
{
  DestroyTree(m_root);
}
//------------------------------------//


//---------------Удаление дерева (поддерева)-------------------//

 void BinaryTree::deleteSubTree(Node *root)
  {
    if(root == nullptr)
      return;

    deleteSubTree(root->GetLeft());
    deleteSubTree(root->GetRight());
    root->SetLeft(nullptr);
    root->SetRight(nullptr);
  }

 void BinaryTree::deleteAllTree()
  {
    deleteSubTree(m_root);
    m_root = nullptr;
  }
//-------------------------------------------------------------//

//----------------Конструктор копирования-----------------//
 BinaryTree::BinaryTree(const BinaryTree& copy)
  {
    if((copy.m_root))
      m_root = copyTree(copy.m_root);
    else 
      m_root = nullptr;
  }

//-------------------Копирование поддерева------------------//
 BinaryTree::Node* BinaryTree::copyTree(Node *root )
  {
    Node* root_copy;
    if (root == nullptr) {
        return nullptr;
    }
    root_copy = new Node(*root);
    if(root->GetLeft() != nullptr)
      root_copy->SetLeft(copyTree(root->GetLeft()));
    else root_copy->SetLeft(nullptr);

    if(root->GetRight() != nullptr)
      root_copy->SetRight(copyTree(root->GetRight()));
    else root_copy->SetRight(nullptr);
    return root_copy;
  }
//---------------------------------------------------------//
//------------------Проверка дерева на пустоту------------------//
 bool BinaryTree::isEmpty(Node *root)
  {
    if (root == nullptr)
      return true;
    return false;
  }

 bool BinaryTree::isEmpty()
{
  return isEmpty(m_root);
}
//--------------------------------------------------------------//


//------------Добавление элемента ( перегрузка ) ------//
 BinaryTree::Node* BinaryTree::addNode(Node *root , int key)
  {
    if(!root)
      root = new Node(key);
    else if ( rand() & 2)
      root->SetLeft( addNode(root->GetLeft(),key) );
    else
      root->SetRight( addNode(root->GetRight(),key) );

    return root;
  }


 BinaryTree::Node* BinaryTree::addNode(int key)
  {
    m_root=addNode(m_root ,key);
    return m_root;
  }
//------------------------------------------------------//

//------------Получение корня-------------------//
 BinaryTree::Node* BinaryTree::getRoot()
  {
    return m_root;
  }
//----------------------------------------------//


//----------------Количество узлов дерева------------//
 int BinaryTree::Count(Node *root) const
  {
    if(root == nullptr)
      return 0;
    return Count(root->GetLeft()) + Count(root->GetRight()) + 1;
  }

 int BinaryTree::Count() const
  {
    return Count(m_root);
  }
//---------------------------------------------------//

//----------------------Вывод дерева горизонтально-----------------//
 void BinaryTree::PrintTree(Node *root, int marginLeft, int Space) const
  {
    if(!root)
      return;
    PrintTree(root->GetRight(),marginLeft+Space,Space);
    std::cout<<std::string(marginLeft,' ')<<root->GetKey()<<std::endl;
    PrintTree(root->GetLeft(),marginLeft+Space,Space);
    
  }

 void BinaryTree::PrintTree(int marginLeft , int Space) const
{
  PrintTree(m_root , marginLeft , Space);
}
//-----------------------------------------------------------------//

//------------------Вывод листьев дерева-----------------//
 void BinaryTree::PrintLeaves(Node *root) const
  {
    if(!root)
      return;
    if(root)
    {
      PrintLeaves(root->GetLeft());
      PrintLeaves(root->GetRight());
      if(root->GetLeft() == nullptr && root->GetRight() == nullptr)
        std::cout<<root->GetKey()<<" ";
    }
  }

 void BinaryTree::PrintLeaves()
{
  PrintLeaves(m_root);
}
//-------------------------------------------------------//

//---------------Получение вектора ключей--------------//
 std::vector<int> BinaryTree::getTreeKeys() const
{
  std::vector<int>treeKeys;
  getTreeKeys(m_root,treeKeys);
  return treeKeys;
}

 void BinaryTree::getTreeKeys(Node *root ,std::vector<int> &treeKeys) const
  {
    if(!root)
      return;
    getTreeKeys(root->GetLeft(),treeKeys);
    treeKeys.push_back(root->GetKey());
    getTreeKeys(root->GetRight(),treeKeys);
  }
//-----------------------------------------------------//


//-------------Получение минимального элемента------------//
 int BinaryTree::searchMinKey()
{
  std::vector<int> treeKeys = getTreeKeys();
  if(treeKeys.empty())
    return -1;
  auto minKey = std::min_element(treeKeys.begin(),treeKeys.end());
  return *minKey;
}
//-----------------------------------------------------//

//-----------Получение максимального элемента----------//
 int BinaryTree::searchMaxKey()
{
  std::vector<int> treeKeys = getTreeKeys();
  if(treeKeys.empty())
    return -1;
  auto maxKey = std::max_element(treeKeys.begin(),treeKeys.end());
  return *maxKey;
}
//-----------------------------------------------------//


//-------------------Получение высоты дерева-------------------//
 int BinaryTree::height(Node *root) const
  {
    if(root == nullptr)
      return 0;
    return 1 + std::max( height(root->GetLeft()) , height(root->GetRight()) );
  }

 int BinaryTree::height() const
{
  return height(m_root);
}
//-------------------------------------------------------------//


//-----------------Сумма всех ключей дерева--------------------//

 int BinaryTree::sumKeys(Node *root)
  {
    if(root == nullptr)
      return 0;
    sumKeys(root->GetLeft()); 
    sumKeys(root->GetRight()); 
    return sumKeys(root->GetLeft()) + sumKeys(root->GetRight()) + root->GetKey();
  }

 int BinaryTree::sumKeys()
{
  return sumKeys(m_root);
}
//-------------------------------------------------------------//


//------------Получение уровня вершины по ключу ---------------//

 BinaryTree::Node* BinaryTree::searchNode(Node *root , int key)
  {
    if(!root || root->GetKey() == key)
      return root;
    Node *temp = searchNode(root->GetLeft() , key);
    if(!temp)
      temp = searchNode(root->GetRight(), key);
    return temp;
  }

 int BinaryTree::GetHeightKey(int key)
  {
    Node *temp = searchNode(m_root, key);
    if( temp == nullptr)
      return -1;
    else
      return (height(m_root) - height(temp));
  }
//-----------------------------------------------------------//

//-------------------Оператор присваивания-----------------//
 BinaryTree& BinaryTree::operator = (const BinaryTree& other)
  {
    if (this == &other)
      return *this;
    DestroyTree(m_root);
    if((other.m_root))
      m_root = copyTree(other.m_root);
    else 
      m_root = nullptr;

    return *this;
  }
//---------------------------------------------------------//

//----------Проверка на сбалансированность----------//
 bool BinaryTree::balancedTree(Node *root)
  {
    if(root == nullptr)
      return true;
    int leftHeight = height(root->GetLeft());
    int rightHeight = height(root->GetRight());
    if( abs(leftHeight - rightHeight) <=1 && balancedTree(root->GetLeft()) && balancedTree(root->GetRight()))
      return true;
    return false;
  }

 bool BinaryTree::balancedTree()
{
  return balancedTree(m_root);
}
//--------------------------------------------------//

//----------------Нахождение родителя-------------------//
 BinaryTree::Node* BinaryTree::findParent(Node* node, Node* temp) 
{
    if (m_root == node || temp == nullptr)
        return nullptr;
 
    if (temp->GetLeft() == node || temp->GetRight() == node)
        return temp;
 
    Node* parent = findParent(node, temp->GetLeft());
    if (parent != nullptr)
        return parent;
 
    parent = findParent(node, temp->GetRight());
    return parent;
}
//------------------------------------------------------//

//-------------------Удаление узла----------------------//
 void BinaryTree::deleteNode(Node *node)
{
  //попали корень
  if(node == m_root)
  {
    delete m_root;
    m_root = nullptr;
    return;
  }

  Node* parent = findParent(node,m_root);
  if(parent == nullptr)
    return;

  Node* replace = nullptr;

  if(node->GetLeft() == nullptr && node->GetRight() == nullptr)
    replace = nullptr;
  else if(node->GetLeft() == nullptr && node->GetRight() != nullptr)
    replace = node->GetRight();
  else if(node->GetRight() == nullptr && node->GetLeft()!=nullptr)
    replace = node->GetLeft();

  else
  {
    Node* minTemp = node->GetRight();
    while(minTemp->GetLeft() != nullptr)
      minTemp = minTemp->GetLeft();
    replace = minTemp;

    //найдем родителя у узла для замены
    Node* minParent = findParent(minTemp,m_root);
    if(minParent != node)
    {
      minParent->SetLeft(replace->GetRight());
      replace->SetRight(node->GetRight());
    }
    replace->SetLeft(node->GetLeft());
  }
    //на место удаляемого узла вставляем replace узел
  if(parent->GetLeft() == node)
      parent->SetLeft(replace);
  else if (parent->GetRight() == node)
      parent->SetRight(replace);
  delete node;
}

 bool BinaryTree::deleteNode(int key)
{
  Node* node = searchNode(m_root,key);
  if(!node)
    return false;

  deleteNode(node);
  return true;
}
//--------------------------------------------------//