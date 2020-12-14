#include<list>
#include<vector>
#include<iostream>
#include <cstdlib> 
#include <iostream> 


#ifndef _CYCLE_BREAKING_H
#define _CYCLE_BREAKING_H


typedef						std::vector<int> int_arr;
typedef						std::vector<char> char_arr;

const int MAX_WEIGHT = 999;
// Data structure to store Adjacency list nodes
struct Node {
	int nodeKey, cost;
	Node* root;
	//Node* pi = nullptr;
	Node* next;
	char color = 'w';
	int d = 0;  // for DFS
	int f = 0;  // for DFS
};

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
};

// struct First{
// 	Node* head;
// 	Node* tail;
// };

class Graph
{
private:
	
	int edgeNum;
	char graphType;
	char_arr color;
	int_arr d, f, key, pi;
	Node* getAdjListNode(int value, int weight, Node* head);

public:
	int nodeNum;	// number of nodes in the graph
	Node** head;  // An array of pointers to Node to represent adjacency list
	Graph(int nodeNum, char graphType);  // Constructor
	Graph(int edgeNum, int nodeNum, char graphType);  // Constructor
	~Graph();  // Destructor
	void printGraph();
	void printList(int i);  // print (start,end,weight) of a given vertix
	void DFS_visit(int u, int& time);
	void printDFS();
	void DFS();
	void PrimMST(int start);
	void printPrim();
	void initialize();
	
	//std::list<int, int> *adj;

};



// Data structure for Min Heap
struct PriorityQueue 
{
private:
    // vector to store heap elements
    std::vector<int> A;
    int PARENT(int i) { return (i - 1) / 2; }  // don't call this function if i is already a root
    int LEFT(int i) { return (2 * i + 1); }  // return left child of A[i]    
    int RIGHT(int i) { return (2 * i + 2);}  // return right child of A[i] 
 
    // Recursive Heapify-down algorithm
    // the node at index i and its two direct children
    void heapify_down(int i);  // violates the heap property

    void heapify_up(int i);  // Recursive Heapify-up algorithm
    
public:
    unsigned int size(){return A.size();}  // return size of the heap
    bool empty(){return size() == 0;}  // function to check if heap is empty or not
    void push(int key);  // insert key into the heap
    void pop();  // function to remove element with lowest priority (present at root)
    int top();  // function to return element with lowest priority (present at root)
	bool inQueue(int n);
	void printQueue();
};
#endif