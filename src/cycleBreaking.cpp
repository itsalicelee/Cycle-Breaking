#include<iostream>
#include"cycleBreaking.h"
using namespace std;


Node* Graph::getAdjListNode(int value, int weight, Node* head)
{
    Node* newNode = new Node;
    
    newNode->val = value;
    newNode->cost = weight;

    // point new node to current head
    newNode->next = head;

    return newNode;
}


Graph::Graph(Edge edges[], int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    head = new Node*[nodeNum]();
    this->nodeNum = nodeNum;

    // initialize head pointer for all vertices
    for (int i = 0; i < nodeNum; ++i)
        head[i] = nullptr;

    // add edges to the directed graph

    for (unsigned i = 0; i < edgeNum; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;

        // insert in the beginning
        Node* newNode = getAdjListNode(dest, weight, head[src]);

        // point head pointer to new node
        head[src] = newNode;
        
        
        // for undirected graph
        if (graphType == 'u'){
            newNode = getAdjListNode(src, weight, head[dest]);
            // change head pointer to point to the new node
            head[dest] = newNode;
        }
    }

    
}
	// Destructor
Graph::~Graph() {
    for (int i = 0; i < nodeNum; i++)
        delete[] head[i];
    delete[] head;
}

// print all neighboring vertices of given vertex
void Graph::printList(Node* ptr, int i)
{
	while (ptr != nullptr)
	{   
		cout << "(" << i+1 << ", " << ptr->val + 1
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;
	}
	cout << endl;
}
