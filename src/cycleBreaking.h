#include<list>
#include<vector>
#include<iostream>


#ifndef _CYCLE_BREAKING_H
#define _CYCLE_BREAKING_H

// Data structure to store Adjacency list nodes
struct Node {
	int val, cost;
	int root;
	int key;
	Node* pi = nullptr;
	Node* next;
	char color = 'w';
	int d = 0;  // for DFS
	int f = 0;  // for DFS
};

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
};


class Graph
{
private:
	int nodeNum;	// number of nodes in the graph
	int edgeNum;
	char graphType;
	Node* getAdjListNode(int value, int weight, Node* head);
	//void DFS_visit(Node* u, int& time);

public:
	Node **head;  // An array of pointers to Node to represent adjacency list
	Graph(int nodeNum, char graphType);  // Constructor
	Graph(int edgeNum, int nodeNum, char graphType);  // Constructor
	~Graph();  // Destructor
    void printList(int i, Node* ptr);
	void printGraph(std::vector<int> adj[], int V);
	void addEdge(Edge anEdge);
	void addEdge(std::vector<int> adj[], int u, int v) ;
	void adj(int v);
	void DFS_visit(Node* vertex, int& time);
	void DFS();
	void PrimMST(int start);
	
	//std::list<int, int> *adj;

};

#endif