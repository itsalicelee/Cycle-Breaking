#include<iostream>
#include<vector>
#include<utility>
#include"cycleBreaking.h"
using namespace std;

void Graph::initialize()  // initialize d, f, pi, color, array
{
    for(int i = 0; i < nodeNum; i++)
    {
        d[i] = 0;
        f[i] = 0;
        pi[i] = 0;
        color[i] = 'w';
    }
}



Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    head = new Node*[nodeNum];
    this->nodeNum = nodeNum;
    this->graphType = graphType;
    

    // initialize head pointer for all vertices
    for (int i = 0; i < nodeNum; ++i){
        this->head[i] = nullptr;
        pi.push_back(0);
		d.push_back(0);
		f.push_back(0);
        pi.push_back(0);
		color.push_back('w');
    }
    
}


void Graph::printGraph()
{
    // print adjacency list representation of graph
    for (int i = 0; i < nodeNum; ++i)
    {  
        cout << i << ":";
        Node* a = head[i];
        while(a != nullptr)
        {
            cout << a->key << " ";
            a = a ->next;
        }
        cout << endl;
    }
}




// Destructor
Graph::~Graph() {
    for (int i = 0; i < nodeNum; i++)
        delete[] head[i];
    delete[] head;
}

// print all neighboring vertices of given vertex
void Graph::printList(int i)
{
    //given i and G.head[i]
    Node* ptr = this->head[i];

	while (ptr != nullptr)
	{   
		cout << "(" << i << ", " << ptr->key
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;
	}
	cout << endl;
}




void Graph::DFS(){
    
    this->initialize();

    int time = 0;

    for(int i = 0; i < nodeNum; ++i)
    {
        //cout << "i: " << i  << head[i]->val << " "<< head[i]->color << endl;   // 這裡應該是要判斷頭有沒有走過（但頭是ptr怎麼辦）
        if (color[i] == 'w'){
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
        if(color[v->key] == 'w')
        {
            pi[v->key]= u;
            DFS_visit(v->key, time);
        }
        v = v->next;
    }
    this->color[u] = 'b';
    time++;
    this->f[u] = time; 

}

void Graph::printDFS(){
	for (int i = 0; i < nodeNum; ++i){
		cout << i << ": " << d[i] << " " << f[i] << " " << endl;
	}
}

void Graph::PrimMST(int start)
{
   for(int i = 0;i < nodeNum; i++)
   {
      while(head[i] != nullptr)
      {
          head[i]->key = 9999;
          head[i]->pi = nullptr;
          head[i] = head[i]->next;
      }

   }
}