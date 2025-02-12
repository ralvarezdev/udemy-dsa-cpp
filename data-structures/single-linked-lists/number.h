#include <cstdlib>
#include <iostream>
#include <string>
#include <limits.h>
#include <iomanip>

#include "base.h"

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

#ifndef NUMBER_SINGLE_LINKED_LISTS
#define NUMBER_SINGLE_LINKED_LISTS

// NUMBER SINGLE LINKED LIST NAMESPACE
namespace numberSLL
{
  const int nIndex = 6;
  const int nDigits = 10;
}

// NUMBER SINGLE LINKED LIST CLASS

template <class NodeType>
class NumberSingleLinkedList : public SingleLinkedList<NodeType>
{
protected:
  // Protected Methods
  void print(SingleNodePtr<NodeType>);
  void printReverse(SingleNodePtr<NodeType>);
  NodeType total(SingleNodePtr<NodeType>);
  NodeType max(SingleNodePtr<NodeType>);
  bool linearSearch(SingleNodePtr<NodeType>, NodeType);

public:
  // Inherit Constructors
  using SingleLinkedList<NodeType>::SingleLinkedList;

  // Constructors
  NumberSingleLinkedList() : SingleLinkedList<NodeType>(-1){};

  // Public Methods
  void print() { return print(this->head->next); };                                // Set Head Next Node as p Node
  void printReverse() { return printReverse(this->head->next); };                  // ...
  NodeType total() { return total(this->head->next); };                            // ...
  NodeType max() { return max(this->head->next); };                                // ...
  bool linearSearch(NodeType key) { return linearSearch(this->head->next, key); }; // ...

  void insertionSort(NodeType);
  int compare(int, int);
};

// Method to Insert Node by Insertion Sort
template <class NodeType>
void NumberSingleLinkedList<NodeType>::insertionSort(NodeType data)
{
  SingleNodePtr<NodeType> p, m, n;

  // Insert Node Next to Head
  if (this->isEmpty())
  {
    this->push(data);
    return;
  }

  int pos = 0;
  n = this->head->next;
  p = this->head;

  while (n != NULL)
  {
    if (n->data > data)
    {
      // Insert Node at pos Index
      this->insertAt(data, pos);
      return;
    }

    p = n;
    n = n->next;
    pos++;
  }

  // Insert Node at Tail
  this->pushBack(data);
}

// Method Print Nodes from Head to Tail
template <class NodeType>
void NumberSingleLinkedList<NodeType>::print(SingleNodePtr<NodeType> p)
{
  int n = 0;

  // Prints Header
  cout << left << setw(numberSLL::nIndex) << setfill(' ') << "Index"
       << setw(numberSLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  // Prints from Head to Tail
  while (p != NULL)
  {
    cout << setw(numberSLL::nIndex) << setfill(' ') << n++
         << setw(numberSLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';
    p = p->next;
  }
}

// Print Nodes with a Recursive Method from Tail to Head
template <class NodeType>
void NumberSingleLinkedList<NodeType>::printReverse(SingleNodePtr<NodeType> p)
{
  static int n = this->length - 1;

  // Prints from Tail to Head
  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail
  if (p != NULL) // Same Expression as !p or p==0
  {
    this->printReverse(p->next);
    cout << setw(numberSLL::nIndex) << setfill(' ') << n--
         << setw(numberSLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';

    return;
  }

  // Prints Header
  cout << left << setw(numberSLL::nIndex) << setfill(' ') << "Index"
       << setw(numberSLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';
}

// Method that Returns the Sum of All Node's Data Field
template <class NodeType>
NodeType NumberSingleLinkedList<NodeType>::total(SingleNodePtr<NodeType> p)
{
  NodeType sum = 0;

  while (p != NULL)
  {
    sum += p->data;
    p = p->next;
  }

  return sum;
}

// Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberSingleLinkedList<NodeType>::max(SingleNodePtr<NodeType> p)
{
  static NodeType m = -1;

  while (p != NULL)
  {
    // Node Number Value is Bigger
    if (p->data > m)
      m = p->data;

    p = p->next;
  }

  return m;
}

// Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
bool NumberSingleLinkedList<NodeType>::linearSearch(SingleNodePtr<NodeType> p, NodeType key)
{
  SingleNodePtr<NodeType> q = NULL;

  while (p != NULL)
  {
    if (key == p->data)
    {
      // Set q as Node Tail
      if (p->next == NULL)
        this->tail = q;

      // Move Node whose Key Matched Next to Head in Order to Improve Performance
      if (q != NULL)
        q->next = p->next;

      if (p != this->head->next)
      {
        p->next = this->head->next;
        this->head->next = p;
      }
      return true;
    }

    q = p;
    p = p->next;
  }

  return false;
}

// Method to Compare Two Nodes Values
template <class NodeType>
int NumberSingleLinkedList<NodeType>::compare(int index1, int index2)
{
  /*
  Possible Results:

  -1: One or Both Nodes are NULL
  0: Nodes Data are Equal
  1: Node1 Data is Greater than Node2 Data
  2: Node2 Data is Greater than Node1 Data

  */

  NodeType value1, value2;

  value1 = this->get(index1);
  value2 = this->get(index2);

  if (value1 == this->error || value2 == this->error)
    return this->error; // One or Both Indexes don't Exist

  if (value1 == value2)
    return 0;

  return value1 > value2 ? 1 : 2;
}

/*
// Recursive Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberSingleLinkedList<NodeType>::max()
{
  static NodeType m = -1;
  SingleNodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    SingleLinkedList<NodeType>::setCurrent();

    return -1;
  }

  this->curr = this->curr->next;
  m = this->max();

  return m > p->data ? m : p->data;
}
*/

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
SingleNodePtr<NodeType> NumberSingleLinkedList<NodeType>::linearSearch(NodeType key)
{
  // Get Current Node
  SingleNodePtr<NodeType> p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    SingleLinkedList<NodeType>::setCurrent();
    return NULL;
  }

  if (key == p->data)
    return p;

  this->curr = this->curr->next;
  return this->linearSearch(key);
}
*/

#endif