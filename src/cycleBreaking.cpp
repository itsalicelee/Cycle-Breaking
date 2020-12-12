#include<iostream>
#include<vector>
#include<utility>
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


Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    head = new Node*[nodeNum+1]();
    this->nodeNum = nodeNum;
    this->graphType = graphType;
    //adj = new list<int,int>[nodeNum+1];

    // initialize head pointer for all vertices
    for (int i = 0; i < nodeNum; ++i)
        head[i] = nullptr;
    
}

void Graph::addEdge(Edge anEdge)
{
    // add edges to the directed graph

    int src = anEdge.src;
    int dest = anEdge.dest;
    int weight = anEdge.weight;

    // insert in the beginning
    Node* newNode = getAdjListNode(dest, weight, head[src]);

    // point head pointer to new node
    head[src] = newNode;
    
    //adj[src].insert(adj[src].end(),{dest,weight});

    // for undirected graph
    if (this->graphType == 'u'){
        newNode = getAdjListNode(src, weight, head[dest]);
        // change head pointer to point to the new node
        head[dest] = newNode;


        //adj[dest].insert(adj[dest].end(),{src,weight});
    }
}



// Destructor
Graph::~Graph() {
    for (int i = 0; i < nodeNum; i++)
        delete[] head[i];
    delete[] head;
}

// print all neighboring vertices of given vertex
void Graph::printList(int i, Node* ptr)
{
	while (ptr != nullptr)
	{   
		cout << "(" << i << ", " << ptr->val
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;
	}
	cout << endl;
}

void Graph::DFS(){
    int time = 0;
    
    for(int i = 0; i < nodeNum; i++)
    {
        cout << "i: " << head[i]->val<< endl;   // 這裡應該是要判斷頭有沒有走過（但頭是ptr怎麼辦）
        if (head[i]->color == 'w'){
            Node* u = 
            DFS_visit(head[i], time);

        }
    }

    
}



void Graph::DFS_visit(Node* u, int& time)
{
    //cout << "u" << u->val << ":";
    u->color = 'g';
    Node* v = u->next;
    while(v != nullptr)
    {
        if(v->color == 'w')
        {
            cout << v->val << " -> ";
            v->pi = u;
            DFS_visit(v,time);
        }
        v = v->next;
    }
    u->color = 'b';
    cout << endl;

}


void Graph::PrimMST(int Start)
{
    for(int i = 0 ;i < nodeNum; i++)
        cout << head[i][0].val << " ";
}