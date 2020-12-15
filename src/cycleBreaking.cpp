#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<stdlib.h>
#include<set>
#include<algorithm>
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
        weight[i] = -MAX_WEIGHT;
        visited[i] = false;
        visited_weight[i].first = false;
        visited_weight[i].second = -MAX_WEIGHT;
        
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
        weight.push_back(0);
        visited.push_back(false);
        std::pair<bool,int> temp;
        temp.first = false;
        temp.second = 0;
        visited_weight.push_back(temp);
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
    // Create Maximum Spanning Tree, want to remove edges with minimum weight
    this->initialize();  // initialize all arrays
    this->weight[start] = 0;
    this->pi[start] = -MAX_WEIGHT;


    // test min heap
    vector<int> temp = {3, 2 ,1, 6, 4,5};
    BinaryHeap b;
    b.printMinHeap(temp);
    b.HeapSort(temp);
    cout << endl ;
    cout << "=======after======" << endl;
    b.printMinHeap(temp);
    int m = b.ExtractMaxFromHeap(temp);
    cout << "m is: " << m;
    
    
    for (int i = 0; i < nodeNum; ++i)
    {
        int maxVertex = ExtractMax(this->visited, this->weight);

        //////////////////////////////////

        // if(b.heapSize != 0){
        //     int newVertex  = b.ExtractMaxFromHeap(this->weight);
        //     cout <<  " new: " << newVertex << endl;
        // }
        /////////////////////////////////
        visited[maxVertex] = true;
        Node* v = head[maxVertex];

        while(v != nullptr)
        {
            if(!visited[v->nodeKey] && v->cost > weight[v->nodeKey])
            {   
                pi[v->nodeKey] = maxVertex;
                weight[v->nodeKey] = v->cost;
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
		cout <<  "i: " << i << ": " <<  "pi: " << pi[i] << ",   weight: " << weight[i] << " " << endl;
        totalCost += weight[i];

	}
    cout << "Total cost is: " << totalCost << endl;
    cout << endl;
}


int Graph::ExtractMax(bool_arr visited, int_arr weight)
{
    // Given visited array and weight array, find out the largest weight that has not visited
    // function used in PrimMST, faster way?
    // NOTE!!!!!
    // We can make weight and visited into vector of pair, 
    // and sort the entire vecor like this:
    // <(0,20), (0,18), (0,15), (0,14),(1,23),(1,20),(1,15)>
    // which means the nodes that we haven't visited
    //  
    int minVertex = -1;
    for(int i = 0; i < nodeNum; ++i){
        if (!visited[i] && (minVertex == -1 || weight[i] > weight[minVertex])){
            minVertex = i;
        }
    }

    sort(visited_weight.begin(), visited_weight.end());
    



    return minVertex;
}

void Graph::printRemoveEdge()
{
    
    // initially, we add new edges undirected a->b, b->a
    // now we only need to add those is in the input to remove 
    
    for(int i = 0; i < this->nodeNum; i++)
    {
        Node* a = this->head[i];
        
        while(a!=  nullptr)
        {    
            // undirected
            if (  (pi[i] != a->nodeKey && pi[ a->nodeKey]!= i) && weight[i] != a->cost ) // not in MST and not the starting point
            {
                cout << "not in MST" <<  "i: " << i << ", nodeKey" << a->nodeKey <<  ", cost" <<  a->cost <<  endl;;
                if ((std::find(edgeSet[i].begin(),edgeSet[i].end(),a->nodeKey) != edgeSet[i].end())
                  &&(std::find(weightSet[i].begin(),weightSet[i].end(),a->cost) != weightSet[i].end()))  // is origin input
                    {
                        this->removeNode.push_back(std::make_pair(i,a)); 
                        this->removeCost += a->cost;
                    } 
                    // removeNode is a vector of Pairs
                    // <(start1,Node1), (start2,Node2)...>
                    ;
            }
            a = a->next;
        }
        
    }   
    
    cout << "========= Remove edges: (start,end,cost) =========" << endl;
    if (this->removeNode.size()!= 0)  // has cycle
    {
        cout << "Has Cycle!!" << endl;
        cout << this->removeCost << endl;
        for(int i = 0 ; i < this->removeNode.size(); ++i)
            cout << this->removeNode[i].first << " " << this->removeNode[i].second->nodeKey << " " << removeNode[i].second->cost << endl;
    }
    else  // no cycle
        cout << "0";
}

// Heap sort method
void BinaryHeap::HeapSort(std::vector<int>& data) {
    // Build Max-Heap
    BuildMinHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MinHeapify(data,0);
    }
}

void BinaryHeap::printMinHeap(std::vector<int>& data)
{
    for(int i = 0; i < data.size(); i++)
    {
        cout << data[i] << endl;
    }
}

//Max heapify
void BinaryHeap::MinHeapify(std::vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = root * 2 + 1;  // or * 2 + 1
    int right = root * 2 + 2;  // or * 2 + 2
    int smallest;
    if (left < heapSize && data[left] < data[root])
        smallest = left;
    else
        smallest = root;
    if (right < heapSize && data[right] < data[smallest])
        smallest = right;
    if (smallest != root)
    {
        swap(data[smallest], data[root]);
        MinHeapify(data, smallest);
    }
}


//Build max heap
void BinaryHeap::BuildMinHeap(std::vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    for(int i = heapSize/2 - 1; i >= 0; i--)  
        MinHeapify(data, i);
}

int BinaryHeap::ExtractMaxFromHeap(std::vector<int>& data)
{
    //TODO
    int max = data[0];
    data[0] = data[data.back()];
    data.pop_back();
    MinHeapify(data,0);
    return max;
}
