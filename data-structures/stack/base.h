#include <cstdlib>

#include "../single-linked-lists/base.h"

#ifndef STACK_LINKED_LISTS
#define STACK_LINKED_LISTS

// SingleNodePtr Definition
template <class NodeType>
using SingleNodePtr = SingleNode<NodeType> *;

// STACK LINKED LIST CLASS
// LIFO
// Last-in, First-out

template <class NodeType>
class StackLinkedList
{
protected:
  SingleNodePtr<NodeType> head = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  NodeType pop(bool);

public:
  // Constructors
  StackLinkedList(NodeType);
  StackLinkedList(NodeType, NodeType);
  StackLinkedList(NodeType[], int, NodeType);
  StackLinkedList(SingleLinkedList<NodeType>, NodeType);
  ~StackLinkedList();

  // Public Methods
  NodeType getError();
  bool isEmpty();
  void push(NodeType);
  NodeType pop() { return pop(false); };
  NodeType top();
  int getLength();
};

// Stack Constructors

// Create Stack Linked List and Set Error Value
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(NodeType data, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new SingleNode<NodeType>(data);

  // Set Node as Head
  this->head = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes through an Array
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(NodeType data[], int length, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create First Node
  this->head = new SingleNode<NodeType>(data[0]);

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    this->head = new SingleNode<NodeType>(data[i], this->head);

  // Increase Length
  this->increaseLength(length);
}

// Add Head and Multiple Next Nodes through a Single Linked List
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(SingleLinkedList<NodeType> list, NodeType error)
{
  int length = list.getLength();

  // Default Error Value
  this->error = error;

  // Create First Node
  this->head = new SingleNode<NodeType>(list.get(0));

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    this->head = new SingleNode<NodeType>(list.get(i), this->head);

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class NodeType>
StackLinkedList<NodeType>::~StackLinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->pop(true);

  // Remove Head Node
  SingleNodePtr<NodeType> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Get Error Value
template <class NodeType>
NodeType StackLinkedList<NodeType>::getError()
{
  return this->error;
}

// Method to Insert Node Before Head
template <class NodeType>
void StackLinkedList<NodeType>::push(NodeType data)
{
  // Insert Node Before Head
  SingleNodePtr<NodeType> h = new SingleNode<NodeType>(data, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Remove Head Node
template <class NodeType>
NodeType StackLinkedList<NodeType>::pop(bool destructor)
{
  SingleNodePtr<NodeType> m, n;

  if (this->isEmpty())
    return this->error;

  // Get Head Node
  m = this->head;
  NodeType data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Stack
  this->head = n;

  // Deallocate Memory
  if (destructor)
    delete[] m;
  else
    delete m;

  decreaseLength();

  return data;
}

// Method to Get Node Data at Top Position
template <class NodeType>
NodeType StackLinkedList<NodeType>::top()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->head->data;
}

// Method to Check if Stack is Empty
template <class NodeType>
bool StackLinkedList<NodeType>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Stack Length
template <class NodeType>
void StackLinkedList<NodeType>::increaseLength()
{
  this->length += 1;
}

template <class NodeType>
void StackLinkedList<NodeType>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Stack Length
template <class NodeType>
void StackLinkedList<NodeType>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Stack Length
template <class NodeType>
int StackLinkedList<NodeType>::getLength()
{
  return this->length;
}

#endif