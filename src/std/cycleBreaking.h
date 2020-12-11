#include<vector>
#include<list>
// Data structure to store Adjacency list nodes
/*
struct Node {
	int val, cost;
	Node* next;
};

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
};*/

class Graph
{
public:
	vector<int> *adj;  // An array of pointers to Node to represent adjacency list
	Graph(int edgeNum, int nodeNum, char graphType);  // Constructor
	~Graph();  // Destructor
    void printList(vector<int>* adj, int i);
	void addEdge(int start, int end, int weight);
private:
	vector<int>* getAdjListNode(int value, int weight, vector<int>* adj);  // Function to allocate new node of Adjacency List
	int nodeNum;	// number of nodes in the graph
	char graphType;

};
