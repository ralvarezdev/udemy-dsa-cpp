#include "../single-linked-lists/number.h"
#include "../nodes/undirNode.h"
#include "../edges/weightedEdges.h"

#include <iostream>
using std::cout;

#ifndef UNDIR_GRAPHS
#define UNDIR_GRAPHS

// UNDIRECTED GRAPHS CLASS

template <class NodeType>
class UndirGraph
{
protected:
  SingleLinkedList<UndirNodePtr<NodeType>> *nodes = NULL;
  int currNodeId;

  // Protected Methods
  SingleLinkedList<UndirNodePtr<NodeType>> *getNodes() { return this->nodes; };

public:
  // Constructors
  UndirGraph(int);

  // Destructor
  virtual ~UndirGraph()
  {
    for (int nodesLength = this->nodes->getLength(); nodesLength > 0; nodesLength--)
      delete this->nodes->remove();
  }

  // Public Methods
  NumberSingleLinkedList<int> *addNodes(QueueLinkedList<NodeType> *);
  void addEdges(SingleLinkedList<Edges> *);
};

// UndirGraphPtr Definition
template <class NodeType>
using UndirGraphPtr = UndirGraph<NodeType> *;

// Undirected Graph Constructors
template <class NodeType>
UndirGraph<NodeType>::UndirGraph(int firstNodeId)
{
  // Set First Node ID
  this->currNodeId = firstNodeId;

  // Initialize Nodes Single Linked List
  this->nodes = new SingleLinkedList<UndirNodePtr<NodeType>>(NULL);
}

// Method to Add Nodes to the Given Graph
template <class NodeType>
NumberSingleLinkedList<int> *UndirGraph<NodeType>::addNodes(QueueLinkedList<NodeType> *nodesData)
{
  NodeType nodeData;
  NumberSingleLinkedList<int> *nodesIndexes = new NumberSingleLinkedList<int>(-1);

  // Add Nodes
  for (int nodesDataLength = nodesData->getLength(); nodesDataLength > 0; nodesDataLength--)
  {
    // Get Node's Data and Push it Back
    nodeData = nodesData->removeBack();

    // Store Node ID
    nodesIndexes->pushBack(this->currNodeId);

    // Allocate Memory for the New Node and Insert It to the Graph
    this->nodes->push(new UndirNode<NodeType>(this->currNodeId++, nodeData));
  }

  return nodesIndexes;
}

// Method to Add Edges to a Given Node
template <class NodeType>
void UndirGraph<NodeType>::addEdges(SingleLinkedList<Edges> *edges)
{
  UndirNodePtr<NodeType> node;
  Edges nodeEdges;
  int srcId;

  // Add Undirected Edges
  for (int edgesLength = edges->getLength(); edgesLength > 0; edgesLength--)
  {
    // Get Node Edges and Source Node ID
    nodeEdges = edges->removeBack();
    srcId = nodeEdges->getSrcId();

    // Get Node at the Given Index
    node = this->nodes->get(srcId);

    // Insert Edges to the Node
    node->addEdges(nodeEdges->getEdges());
  }
}

#endif