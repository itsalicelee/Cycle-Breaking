#include<list>
#include<vector>
#include<iostream>
#include <cstdlib> 
#include <iostream> 


const int MAX_WEIGHT = 999;

// Data structure to store Adjacency list nodes
struct Node {
	int nodeKey, cost;
	Node* root;
	Node* next;
	char color = 'w';
	int d = 0;  // for DFS
	int f = 0;  // for DFS
	int rank = 0;  // for Kruskal
};

// Data structure to store graph edges
class Edge {
public:
	int src, dest, weight;
};

class subset {
public:
    int parent;
    int rank;
	
};


class Graph
{
private:
	
	int 					cost = 0;
	int 					edgeNum;
	char 					graphType;
    std::vector<char> 		color;
	std::vector<int> 		d, f, pi;
	std::vector<int> 		weight;
	std::vector<bool> 		visit;
	std::list<struct Node> 	remove;
	
	// Node* getAdjListNode(int value, int weight, Node* head);
	

public:
	std::vector<Edge>		edgeList;
	int 					nodeNum;	// number of nodes in the graph
	bool** 					map;
	std::list<int>* 		h;
	Node** 					head;  // An array of pointers to Node to represent adjacency list

	void 				printGraph();
	void 				printList(int i);  // print (start,end,weight) of a given vertix
	int 				find(subset subsets[], int i);
	void 				Union(subset subsets[], int x, int y);
	std::vector<Edge> 	KruskalMST();
	std::vector<Edge> 	KruskalRemoveEdge(std::vector<std::vector<int> > mst, std::vector<Edge> treeVec);
	std::vector<Edge> 	countingSort(std::vector<Edge > edgeList);
	std::vector<Edge> 	addEdge(std::vector<Edge>& tree, std::vector<Edge>& removeEdget);
	bool 				isCycleUtil(int i, bool visited[], bool *recStack);
	bool 				hasCycle();
	int 				getCost(){return cost;};
	Graph(int edgeNum, int nodeNum, char graphType);  // Constructor
	~Graph();  // Destructor
};


// #endif