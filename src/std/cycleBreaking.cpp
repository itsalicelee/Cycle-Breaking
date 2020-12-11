#include<iostream>
#include<utility>
#include"cycleBreaking.h"
using namespace std;


Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    // head = new N*[nodeNum]();
    this->nodeNum = nodeNum;
    this->graphType = graphType;

    // initialize head  for all vertices
    adj = new vector<int>[nodeNum];
}
	// Destructor
Graph::~Graph() {}


void Graph::addEdge(int start, int end, int weight){
    adj[start].push_back(end);
    adj[start].push_back(weight);
    if (this->graphType == 'u')
    {
    adj[start].push_back(end);
    adj[start].push_back(weight);
    
    
    }


}

// print all neighboring vertices of given vertex
// void Graph::printList(vector<int>* ptr, int i)
// {
// 	while (ptr != nullptr)
// 	{   
// 		cout << "(" << i+1 << ", " << ptr->val + 1
// 			<< ", " << ptr->cost << ") ";

// 		ptr = ptr->next;
// 	}
// 	cout << endl;
// }


/*

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
*/