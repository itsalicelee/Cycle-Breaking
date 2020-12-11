
// Data structure to store Adjacency list nodes
struct Node {
	int val, cost;
	Node* next;
};

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
};

class Graph
{
public:
	Node **head;  // An array of pointers to Node to represent adjacency list
	Graph(Edge edges[], int edgeNum, int nodeNum, char graphType);  // Constructor
	~Graph();  // Destructor
    void printList(Node* ptr, int i);
private:
	Node* getAdjListNode(int value, int weight, Node* head);  // Function to allocate new node of Adjacency List
	int nodeNum;	// number of nodes in the graph

};
