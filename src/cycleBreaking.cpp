#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<stdlib.h>
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
        key.push_back(999);
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
		cout << i << ": " <<  "discover time: " << d[i] << ", finish time: " << f[i] << " " << endl;
	}
}

void Graph::PrimMST(int start)
{
    this->initialize();
    this->key[start] = 0;
    int n = this->nodeNum;

    // create queue
    FibHeap Q(n);
    for(int i = 0; i < nodeNum; i++)
    {
        Q.insertion(i);
    }


    while(Q.no_of_nodes != 0)
    {
        int u = Q.find_min(Q.mini);
        for(int i = 0; i < nodeNum; i++)
        {
            Node* a = head[i];
            while(a != nullptr)
            {
                //TODO




            }


        }

    }
}

FibHeap::FibHeap(int n)
{
    this->no_of_nodes = n;
    struct node* mini = NULL;
}
FibHeap::~FibHeap()
{
    delete[] this->mini;
};

void FibHeap::insertion(int val) 
{ 
    struct node* new_node = (struct node*)malloc(sizeof(struct node)); 
    new_node->key = val; 
    new_node->parent = NULL; 
    new_node->child = NULL; 
    new_node->left = new_node; 
    new_node->right = new_node; 
    if (this->mini != NULL) { 
        (this->mini->left)->right = new_node; 
        new_node->right = mini; 
        new_node->left = mini->left; 
        this->mini->left = new_node; 
        if (new_node->key < mini->key) 
            this->mini = new_node; 
    } 
    else { 
        this->mini = new_node; 
    } 
} 

void FibHeap::displayFib(struct node* mini) 
{ 
    node* ptr = this->mini; 
    if (ptr == NULL) 
        cout << "The Heap is Empty" << endl; 
  
    else { 
        cout << "The root nodes of Heap are: " << endl; 
        do { 
            cout << ptr->key; 
            ptr = ptr->right; 
            if (ptr != mini) { 
                cout << "-->"; 
            } 
        } while (ptr != this->mini && ptr->right != NULL); 
        cout << endl 
             << "The heap has " << this->no_of_nodes << " nodes" << endl; 
    } 
} 

// Function to find min node in the heap 
int FibHeap::find_min(struct node* mini) 
{ 
    cout << "min of heap is: " << this->mini->key << endl; 
    return this->mini->key;
} 
