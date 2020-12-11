// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2020 fall Algorithm PA3:Cycle Breaker]
//  Date       2020/12/10
// **************************************************************************

#include<iostream>
#include<fstream>
#include<utility>
#include<list>
#include<stdlib.h>
#include <stdio.h>
#include"cycleBreaking.h"
#include"fileio.cpp"
using namespace std;

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
	// Function to allocate new node of Adjacency List
	Node* getAdjListNode(int value, int weight, Node* head)
	{
		Node* newNode = new Node;
		newNode->val = value;
		newNode->cost = weight;

		// point new node to current head
		newNode->next = head;

		return newNode;
	}

	int nodeNum;	// number of nodes in the graph

public:

	// An array of pointers to Node to represent
	// adjacency list
	Node **head;

	// Constructor
	Graph(Edge edges[], int edgeNum, int nodeNum, char graphType)
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
	~Graph() {
		for (int i = 0; i < nodeNum; i++)
			delete[] head[i];
		delete[] head;
	}
};

// print all neighboring vertices of given vertex
void printList(Node* ptr, int i)
{
	while (ptr != nullptr)
	{   
		cout << "(" << i+1 << ", " << ptr->val + 1
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;
	}
	cout << endl;
}

void help_message() {cout << "usage: ./bin/cb inputs/<input file> outputs/<output file>" << "\n";}
int main(int argc, char* argv[])
{
    if (argc != 3){
        help_message(); 
        return 0;
    }
    //////////// read the input file /////////////
    

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    // error message
    if (!fin){ cout << "cannot read file" << "\n";}
    if (!fout){ cout << "cannot write file" << "\n";}

    char graphType;  // undirected or directed 
    int nodeNum, edgeNum;  // n, m
    fin >> graphType;
    fin >> nodeNum;
    fin >> edgeNum;
    
    int start, end, weight;
    Edge edges[edgeNum];
    
    for(size_t i = 0; i < edgeNum; ++i){
        fin >> start >> end >> weight;
    edges[i].src = start-1;
    edges[i].dest = end-1;
    edges[i].weight = weight;
    }
    Graph G(edges,edgeNum, nodeNum, graphType); // create a graph
    
    // print adjacency list representation of graph
    for (int i = 0; i < nodeNum; i++)
    {
        printList(G.head[i], i);  // print all neighboring vertices of vertex i
    }

    //////////// algorithm start ////////////////

    
    

    //////////// write the output file ///////////

    int minWeight;
    int cnt;
    fout << minWeight << "\n";
    
    Edge output[3] = {{0,1},{1,2},{3,4}};
    if(cnt != 0){
        for (size_t i = 0; i < 3; ++i) 
            fout << output[i].src << " " << output[i].dest << "\n";
    }
    fin.close();
    fout.close();
    
    return 0;
}
