#include <iostream>
#include <string>
#include <limits.h>
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

// NODE STRUCT
// Self-Referential Structure

class Node
{
public:
  int num;
  Node *next = NULL;

  // Constructor
  Node();
  Node(int);
};

// Node Class Constructors
Node::Node()
{
  return;
}

Node::Node(int num)
{
  this->num = num;
}

typedef Node *NodePtr;

// LINKED LIST CLASS
class LinkedList
{
private:
  NodePtr head;
  NodePtr tail;
  NodePtr curr;

  int length = 0;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  void setCurrent(NodePtr);

public:
  // Constructors
  LinkedList();
  LinkedList(int);
  LinkedList(int[], int);
  ~LinkedList();

  // Public Methods
  bool isEmpty();
  void insertFirst(int);
  void insert(int);
  void insertAt(int, int);
  int removeFirst();
  void print();
  void printReverse();
  int getLength();
  void setHeadAsCurrent();
  int total();
  int max();
  NodePtr linearSearch(int);
};

// Linked List Constructors

// Add Head with Next Node as NULL
LinkedList::LinkedList()
{
  NodePtr p = new Node();

  // Add Node as Head and Tail
  this->head = this->tail = p;

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Add Head with Only One Next Node
LinkedList::LinkedList(int num)
{
  NodePtr p = new Node();

  // Add Node as Head
  this->head = p;

  // Add Next Node
  p = new Node();
  p->num = num;
  this->head->next = p;

  // Add Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength();

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Add Head and Multiple Next Nodes
LinkedList::LinkedList(int nums[], int length)
{
  NodePtr p = new Node();

  // Add Node to Head
  this->head = p;

  // Set Head as Current Node
  this->curr = this->head;

  // Add Next Nodes
  for (int i = 0; i < length; i++)
  {
    p = new Node();
    p->num = nums[i];

    // Add Node
    this->curr->next = p;

    // Set Current Node
    this->curr = this->curr->next;
  }

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Destructor
LinkedList::~LinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->removeFirst();

  // Remove Head Node
  NodePtr temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Insert Node Next to Head
void LinkedList::insertFirst(int num)
{
  NodePtr n, p;

  // Get Node Next to Head
  n = this->head->next;
  p = new Node(num);
  p->next = n;

  // Set Node Next to Head
  this->head->next = p;

  this->increaseLength();
}

// Method to Insert Node at Given Position
void LinkedList::insertAt(int num, int pos)
{
  if (pos == 0)
  {
    this->insertFirst(num); // Insert Next to Head
    return;
  }

  if (pos < 0)
    pos = this->length + pos + 1; // Get Position

  if (pos >= this->length)
  {
    this->insert(num); // Insert at Tail
    return;
  }

  NodePtr m, q, p;

  // Get Head
  m = this->head;

  // Create New Node
  p = new Node(num);

  // Move to Node at Given Position
  for (int i = 0; i < pos; i++)
    m = m->next;

  // Perform Last Node Move
  q = m;
  m = m->next;

  // Set Node at Given Position
  q->next = p;
  p->next = m;

  this->increaseLength();
}

// Method to Insert Node at Tail
void LinkedList::insert(int num)
{
  NodePtr p = new Node(num);

  // Set Node at Tail
  this->tail->next = p;
  this->tail = p;

  this->increaseLength();
}

// Method to Remove Node Next to Head
int LinkedList::removeFirst()
{
  if (this->isEmpty())
    return -1;

  NodePtr temp = this->head->next;
  int num = temp->num;

  head->next = temp->next;

  delete[] temp;
  decreaseLength();

  return num;
}

// Method to Check if Linked List is Empty
bool LinkedList::isEmpty()
{
  return this->head->next == NULL;
}

// Method to Increase Linked List Length
void LinkedList::increaseLength()
{
  this->length += 1;
}

void LinkedList::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
void LinkedList::decreaseLength()
{
  this->length -= 1;
}

// Method to Set Current Node
void LinkedList::setCurrent(NodePtr p)
{
  this->curr = p;
}

// Method to Set Head Node as Current Node
void LinkedList::setHeadAsCurrent()
{
  this->curr = this->head;
}

// Print Nodes Method
void LinkedList::print()
{
  int n = 0;
  NodePtr p = this->head->next;

  // Prints from Head to Tail
  while (p != NULL)
  {
    cout << setw(6) << left << n++ << "| " << p->num << '\n';
    p = p->next;
  }
}

// Print Nodes with a Recursive Method
void LinkedList::printReverse()
{
  static int n = 0;
  NodePtr p = this->curr;

  // Prints from Tail to Head
  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail

  if (p->next != NULL) // Same Expression as !p or p==0
  {
    p = p->next;
    this->curr = p;
    this->printReverse();
    cout << setw(6) << left << n++ << "| " << p->num << '\n';

    return;
  }

  // Set Head Node as Current Node
  this->setHeadAsCurrent();
}

/*
// Count Nodes with a Recursive Method
int LinkedList::count(NodePtr p)
{
  if (p != NULL)
    return count(p->next) + 1;

  // Set Head Node as Current Node
  this->setHeadAsCurrent();

  return 0;
}
*/

// Method to Get Linked List Length
int LinkedList::getLength()
{
  return this->length;
}

// Method that Returns the Sum of All Node's Data Field
int LinkedList::total()
{
  NodePtr p = this->head->next;
  int sum = 0;

  while (p != NULL)
  {
    sum += p->num;
    p = p->next;
  }

  return sum;
}

// Method that Returns the Highest Number in Linked List
int LinkedList::max()
{
  static int m = INT_MIN;
  NodePtr p = this->head->next;

  while (p != NULL)
  {
    if (p->num > m)
      m = p->num;

    p = p->next;
  }

  return m;
}

/*
// Recursive Method that Returns the Highest Number in Linked List
int LinkedList::max()
{
  static int x = INT_MIN;
  NodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    this->setHeadAsCurrent();

    return INT_MIN;
  }

  this->curr = this->curr->next;
  x = this->max();

  return x > p->num ? x : p->num;
}
*/

// Method that Checks if the Given Number is Inside Linked List
NodePtr LinkedList::linearSearch(int key)
{
  NodePtr q;

  // Get Node Next to Head
  NodePtr p = this->head->next;

  while (p != NULL)
  {
    if (key == p->num)
    {
      // Set p Node as Tail
      if (p->next == NULL)
        this->tail = q;

      // Move Node whose Key Matched Next to Head in Order to Improve Performance
      q->next = p->next;
      p->next = this->head->next;
      this->head->next = p;

      // Set Head Node as Current Node
      this->setHeadAsCurrent();
      return p;
    }
    q = p;
    p = p->next;
  }

  // Set Head Node as Current Node
  this->setHeadAsCurrent();
  return NULL;
}

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
NodePtr LinkedList::linearSearch(int key)
{
  // Get Current Node
  NodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    this->setHeadAsCurrent();
    return NULL;
  }

  if (key == p->num)
    return p;

  this->curr = this->curr->next;
  return this->linearSearch(key);
}
*/

// Function to Check if Key was Found
string isKey(NodePtr p)
{
  return p ? "Key Found" : "Key not Found";
}

// Method to Check if Node is not NULL
string isNull(NodePtr p)
{
  return p ? "Node is NULL" : "Node is not NULL";
}

int main()
{

  // Memory Allocation
  int numbers[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25};

  // LinkedList list = LinkedList();
  // LinkedList list = LinkedList(1);
  LinkedList list = LinkedList(numbers, 11);

  // Check if it's Empty
  string isEmpty = list.isEmpty() ? "True" : "False";
  cout << "Is Empty? " << isEmpty << "\n\n";

  // Check List Length
  int length = list.getLength();
  cout << "List Length: " << length << "\n\n";

  // Get Total
  int total = list.total();
  cout << "List Total: " << total << "\n\n";

  // Print Nodes
  cout << "Nodes:\n";
  list.print();

  cout << "\nFirst Node Removed:\n";
  list.removeFirst();
  list.print();

  cout << "\nNodes (Reverse):\n";
  list.printReverse();

  // Max Number inside Linked List
  cout << "\nMax Number: " << list.max() << '\n';

  // Search for Number in Linked List
  NodePtr nodeFound;
  int key;

  key = 24;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  key = 25;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  key = 6;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  // Print Nodes (Now, Node whose Key was Found is Next to Head)
  cout << "\nNodes after Linear Search:\n";
  list.print();

  // Insert Node
  list.insertFirst(55);   // Next to Head
  list.insertAt(100, 6);  // At Index 6
  list.insert(33);        // At Tail
  list.insertAt(77, -1);  // At Tail
  list.insertAt(400, -2); // Before Tail
  list.insertAt(898, 20); // At Tail
  list.insertAt(999, -1); // At Tail
  list.insertFirst(13);   // Next to Head

  cout << "\nNodes after Insertion:\n";
  list.print();
}