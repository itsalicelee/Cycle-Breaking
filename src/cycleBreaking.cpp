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
    head = new Node*[nodeNum]();
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

void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
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
    //given i and G.head[i]

	while (ptr != nullptr)
	{   
		cout << "(" << i << ", " << ptr->val
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;
	}
	cout << endl;
}




void Graph::DFS(){
    
    
    for(int i = 0; i < nodeNum; i++)
    {
        //cout << "i: " << i << head[i]<< endl;   // 這裡應該是要判斷頭有沒有走過（但頭是ptr怎麼辦）
        while(head[i] != nullptr){
            head[i]-> color = 'w';
            head[i]-> pi = nullptr;
            head[i] = head[i]->next;
        }
    }

    int time = 0;

    for(int i = 0; i < nodeNum; i++)
    {
        cout << "i: " << i << head[i]->val<< endl;   // 這裡應該是要判斷頭有沒有走過（但頭是ptr怎麼辦）
        while(head[i] != nullptr){

            if (head[i]->color == 'w'){
                DFS_visit(head[i], time);
            }
            head[i] = head[i]->next;
        }
    }


    
}



void Graph::DFS_visit(Node* u, int& time)
{
    //cout << "u" << u->val << ":";
    time++;
    u->d = time;
    u->color = 'g';
    Node* v = u->next;
    while(v != nullptr)
    {
        if(v->color == 'w')
        {
            //cout << v->val << " -> ";
            v->pi = u;
            DFS_visit(v, time);
        }
        v = v->next;
    }
    u->color = 'b';
    time++;
    u->f = time; 
    cout << endl;

}


void Graph::PrimMST(int start)
{
   for(int i = 0;i < nodeNum; i++)
   {
      while(head[i] != nullptr)
      {
          head[i]->val = 9999;
          head[i]->pi = nullptr;

          head[i] = head[i]->next;
      }

   }



}