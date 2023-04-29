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

//-------------------Удаление узла--------------------//
BinaryTree::Node *SearchTree::minNode(Node* root)
{
    BinaryTree::Node* temp = root;
    while (temp && temp->GetLeft() != nullptr)
        temp = temp->GetLeft();
    return temp;
}

BinaryTree::Node *SearchTree::deleteNode(Node* root, int key)
{
    if (root == nullptr)
        return root;
    if (key < root->GetKey())
        //root->GetLeft() = deleteNode(root->GetLeft(), key);
        root->SetLeft(deleteNode(root->GetLeft(), key));
    else if (key > root->GetKey())
       // root->GetRight() = deleteNode(root->GetRight(), key);
        root->SetRight(deleteNode(root->GetRight(), key));
    else {

        if (root->GetLeft() == nullptr and root->GetRight() == nullptr)
            return nullptr;
      
        else if (root->GetLeft() == nullptr) 
        {
            BinaryTree::Node* temp = root->GetRight();
            delete root;
            return temp;
        }
        else if (root->GetRight() == nullptr) {
            BinaryTree::Node* temp = root->GetLeft();
            delete root;
            return temp;
        }
 
        BinaryTree::Node* temp = minNode(root->GetRight());

       // root->GetKey() = temp->GetKey();
        root->SetKey(temp->GetKey());
        //root->GetRight() = deleteNode(root->GetRight(), temp->GetKey());
        root->SetRight(deleteNode(root->GetRight(), temp->GetKey()));
    }
    return root;
}

 bool SearchTree::deleteNode(int key)
{
  Node* node = searchNode(m_root,key);
  if(!node)
    return false;

  deleteNode(node,key);
  return true;
}
/*void SearchTree::deleteNode(Node* root, int key)
{
    // базовый случай: ключ не найден в дереве
    if (root == nullptr) {
        return;
    }
 
    // если заданный ключ меньше корневого узла, повторить для левого поддерева
    if (key < root->GetKey()) {
        deleteNode(root->GetLeft(), key);
    }
 
    // если данный ключ больше, чем корневой узел, повторить для правого поддерева
    else if (key > root->GetKey()) {
        deleteNode(root->GetRight(), key);
    }
 
    // ключ найден
    else {
        // Случай 1: удаляемый узел не имеет потомков (это листовой узел)
        if (root->GetLeft() == nullptr && root->GetRight() == nullptr)
        {
            // освобождаем память и обновляем root до null
            delete root;
            root = nullptr;
        }
 
        // Случай 2: удаляемый узел имеет двух потомков
        else if (root->GetLeft() && root->GetRight())
        {
            // найти его неупорядоченный узел-предшественник
            Node* predecessor = minNode(root->GetLeft());
 
            // копируем значение предшественника в текущий узел
            root->SetKey(predecessor->GetKey());
 
            // рекурсивно удаляем предшественника. Обратите внимание, что
            // у предшественника будет не более одного дочернего элемента (левого дочернего элемента)
            deleteNode(root->GetLeft(), predecessor->GetKey());
        }
 
        // Случай 3: удаляемый узел имеет только одного потомка
        else {
            // выбираем дочерний узел
            Node* child = (root->GetLeft())? root->GetLeft(): root->GetRight();
            Node* curr = root;
 
            root = child;
 
            // освобождаем память
            delete curr;
        }
    }
}
*/

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