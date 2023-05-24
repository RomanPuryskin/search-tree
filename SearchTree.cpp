#include "searchTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

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
  // у узла нет потомков, а потомков много и не нужно
  if (node->GetLeft() == nullptr && node->GetRight() == nullptr)
    replace = nullptr;
    
  // у удаляемого узла только правый потомок, но есть же и левый
  else if (node->GetLeft() == nullptr && node->GetRight() != nullptr)
  {
    replace = node->GetRight();
  }

  // у удаляемого узла только левый потомок, а правый был выше
  else if (node->GetRight() == nullptr && node->GetLeft() != nullptr)
  {
    replace = node->GetLeft();
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

//-----------Построение оптимального дерева поиска------------//
BinaryTree::Node *SearchTree::createOptimalTree(std::vector<int> &keys, std::vector<int> &freq, std::vector<int> &extraFreq)
{
  keys.insert(keys.begin() , 0);
  freq.insert(freq.begin() , 0);
  int treeSize =5;
  
  // создали три матрицы
  int **weight , **costs , **keyNumbers;
  weight = new int* [treeSize];
  for(int i=0; i<treeSize; i++)
    weight[i] = new int [treeSize];
  
  costs = new int* [treeSize];
  for(int i=0; i<treeSize; i++)
    costs[i] = new int [treeSize];
  
 keyNumbers = new int* [treeSize];
  for(int i=0; i<treeSize; i++)
    keyNumbers[i] = new int [treeSize];

  for( int i = 0 ; i<treeSize; i++)
    {
      for ( int j = 0; j<treeSize; j++)
        {
          weight[i][j] = 0;
          costs[i][j] = 0;
          keyNumbers[i][j] = 0;
        }
    }

  
  // заполнили матрицы весов и стоимости по диагонали
  for (int i = 0 ; i<treeSize ; i++)
    {
      weight[i][i] = extraFreq[i];
      costs[i][i] = extraFreq[i];
    }
  // заполнили вторую диагональ у всех матриц
  for(int i = 0; i<treeSize-1; i++)
    {
      int j = i+1;
      weight[i][j] = weight[i][j-1] + freq[j] + extraFreq[j];
      costs[i][j] = weight[i][j] + costs[i][i] + costs[j][j];
      keyNumbers[i][j] = j;
    }
  if ( (treeSize - 1) >=2 )
  {  
  // заполняем оставшиеся части таблиц
    for(int i = 0; i < treeSize ; i++)
      {
        for(int j=i+2 ; j<treeSize ; j++)
          {
            weight[i][j] = weight[i][j-1] + freq[j] + extraFreq[j];
            int minCost;
            int temp;
            for (int k = i+1; k<j ; k++)
              {
                minCost = costs[i][k-1]+costs[k][j];
                temp = k;
                if ( (costs[i][k] + costs[k+1][j]) < minCost)
                {
                  minCost = costs[i][k] + costs [k+1][j];
                  temp = k+1;
                }
              }
            costs[i][j] = weight[i][j] + minCost;
            keyNumbers[i][j] = temp;
          }
      }

  }
   /* 
    for(int i=0; i<treeSize; i++)
    { 
      for(int j=0; j<treeSize; j++) 
        std::cout<<weight[i][j]<<" ";
      std::cout<<std::endl;
    }*/


  m_root = createOptimalTree(keys , keyNumbers , 0 , treeSize-1);

// освободим память
  for(int i=0; i<treeSize; i++)
    {
      delete[] weight[i];
      delete[] costs[i];
      delete[] keyNumbers[i];
    }
  delete[] weight;
  delete[] costs;
  delete[] keyNumbers;

  
  return m_root;
}

BinaryTree::Node *SearchTree::createOptimalTree(std::vector<int> &keys,int** matrix,int i, int j)
{
  Node* root;
  if(i>=j)
    {
      root = nullptr;
      return root;
    }
  else
  {
    int k = matrix[i][j];
    root = new Node(keys[k]);
    root->SetLeft(createOptimalTree(keys,matrix,i, k-1));
    root->SetRight(createOptimalTree(keys,matrix,k,j));
  }
  return root;
}
//----------------------------------------------------------------//