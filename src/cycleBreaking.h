#include<list>
#include<vector>
#include<iostream>
#include <cstdlib> 
#include <iostream> 


#ifndef _CYCLE_BREAKING_H
#define _CYCLE_BREAKING_H


typedef						std::vector<int> int_arr;
typedef						std::vector<char> char_arr;


// Data structure to store Adjacency list nodes
struct Node {
	int key, cost;
	Node* root;
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
	void initialize();
	
	//std::list<int, int> *adj;

};

// data structure for fib heap
struct node { 
    node* parent; 
    node* child; 
    node* left; 
    node* right; 
    int key; 
}; 


class FibHeap
{
public:
	FibHeap(int n);
	~FibHeap();
	struct node* mini;  // Creating min pointer as "mini" 
	int no_of_nodes;  // Declare an integer for number of nodes in the heap 
	void insertion(int val);  // Function to insert a node in heap 
	void displayFib(struct node* mini);  // Function to display the heap
	int find_min(struct node* mini);  // Function to find min node in the heap 
};
#endif