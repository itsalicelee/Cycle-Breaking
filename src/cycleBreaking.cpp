#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<stdlib.h>
#include<set>
#include"cycleBreaking.h"
using namespace std;

void Graph::initialize()  // initialize d, f, pi, color, array
{
    for(int i = 0; i < nodeNum; i++)
    {
        d[i] = 0;
        f[i] = 0;
        pi[i] = -1;
        color[i] = 'w';
        key[i] = -MAX_WEIGHT;
        visited[i] = false;
    }
}

Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    head = new Node*[nodeNum];
    this->nodeNum = nodeNum;
    this->graphType = graphType;
    
    // initialize head pointer for all vertices
    for (int i = 0; i < nodeNum; ++i)
    {
        this->head[i] = nullptr;
        pi.push_back(0);
		d.push_back(0);
		f.push_back(0);
        pi.push_back(0);
		color.push_back('w');
        key.push_back(0);
        visited.push_back(false);
    }
    
}


void Graph::printGraph()
{
    cout << "========= Graph =========" << endl;
    // print adjacency list representation of graph
    for (int i = 0; i < nodeNum; ++i)
    {  
        cout << "head" << i << ":" << endl;
        Node* a = head[i];
        while(a != nullptr)
        {
            cout << "("<<a->nodeKey << "," << a->cost  << ")"<< endl;
            a = a ->next;
        }
        cout << endl;
    }
}

// Destructor
Graph::~Graph()
{
    for (int i = 0; i < nodeNum; i++)
        delete[] head[i];
    delete[] head;
}

// print all neighboring vertices of given vertex
void Graph::printList(int i)
{
    cout << "========= (Node i, Neighbor, Cost) of node i =========" << endl;
    cout << "i is:" << i << endl;
    //given i and G.head[i]
    Node* ptr = this->head[i];
    
	while (ptr != nullptr)
    {   
		cout << "(" << i << ", " << ptr->nodeKey
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;

	}
    cout << endl;
    cout << endl;
}


void Graph::DFS()
{
    this->initialize();
    int time = 0;

    for(int i = 0; i < nodeNum; ++i)
    {
        if (color[i] == 'w')
        {
            DFS_visit(i, time);
        }
    }
}



void Graph::DFS_visit(int u, int& time)
{
    time++;
    this->d[u] = time;
    this->color[u] = 'g';

    Node* v = head[u];
    while(v != nullptr)
    {
        if(color[v->nodeKey] == 'w')
        {
            pi[v->nodeKey]= u;
            DFS_visit(v->nodeKey, time);
        }
        v = v->next;
    }
    this->color[u] = 'b';
    time++;
    this->f[u] = time; 

}

void Graph::printDFS()
{
    cout << "========= DFS =========" << endl;
	for (int i = 0; i < nodeNum; ++i)
		cout << i << ": " <<  "discover time: " << d[i] << ", finish time: " << f[i] << " " << endl;
    cout << endl;
}

void Graph::PrimMST(int start)
{
    this->initialize();  // initialize all arrays
    this->key[start] = 0;
    this->pi[start] = -1;

    for (int i = 0; i < nodeNum; ++i)
    {
        int maxVertex = ExtractMax(this->visited, this->key);
        visited[maxVertex] = true;
        Node* v = head[maxVertex];

        while(v != nullptr)
        {
            if(!visited[v->nodeKey] && v->cost > key[v->nodeKey])
            {   
                pi[v->nodeKey] = maxVertex;
                key[v->nodeKey] = v->cost;
            }
            v = v ->next;
        }
    }
    
}

void Graph::printPrim()
{
    cout << "========= Prim's Algorithm =========" << endl;
    int totalCost = 0;
	for (int i = 0; i < nodeNum; ++i){
		cout << i << ": " <<  "pi: " << pi[i] << ",   key: " << key[i] << " " << endl;
        totalCost += key[i];
	}
    cout << "Total cost is: " << totalCost << endl;
    cout << endl;
}


int Graph::ExtractMax(bool_arr visited, int_arr weight)
{
    // function which is used in PrimMST
    int minVertex = -1;
    for(int i = 0; i < nodeNum; ++i){
        if (!visited[i] && (minVertex == -1 || key[i] > key[minVertex])){
            minVertex = i;
        }
    }
    return minVertex;
}
