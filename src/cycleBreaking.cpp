#include<queue>
#include<vector>
#include<utility>
#include<stdlib.h>
#include<set>
#include<algorithm>
#include<iostream>
#include"cycleBreaking.h"
using namespace std;

void Graph::initialize()  // initialize d, f, pi, color, array
{
    for(int i = 0; i < nodeNum; i++){
        d[i] = 0;
        f[i] = 0;
        pi[i] = -1;
        color[i] = 'w';
        weight[i] = -MAX_WEIGHT;
        visited[i] = false;
        // visited_weight[i].first = false;
        // visited_weight[i].second = -MAX_WEIGHT;
        
    }
}

Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    head = new Node*[nodeNum];
    this->nodeNum = nodeNum;
    this->edgeNum = edgeNum;
    this->graphType = graphType;
    
    // initialize head pointer for all vertices
    for (int i = 0; i < nodeNum; ++i){
        this->head[i] = nullptr;
        pi.push_back(0);
		d.push_back(0);
		f.push_back(0);
        pi.push_back(0);
		color.push_back('w');
        weight.push_back(0);
        visited.push_back(false);

    }
    
}


void Graph::printGraph()
{
    std::cout << "========= Graph =========" << endl;
    // print adjacency list representation of graph
    for (int i = 0; i < nodeNum; ++i){  
        std::cout << "head" << i << ":" << endl;
        Node* a = head[i];
        while(a != nullptr){
            std::cout << "("<<a->nodeKey << "," << a->cost  << ")"<< endl;
            a = a ->next;
        }
        std::cout << endl;
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
    
	while (ptr != nullptr){   
		std::cout << "(" << i << ", " << ptr->nodeKey << ", " << ptr->cost << ") ";
		ptr = ptr->next;
	}
    std::cout << endl;
    std::cout << endl;
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



bool Graph::DFS_visit(int u, int& time)
{
    time++;
    this->d[u] = time;
    this->color[u] = 'g';
    this->visited[u] = true;
    
    Node* v = head[u];
    while(v != nullptr){
        if(color[v->nodeKey] == 'w'){
            visited[v->nodeKey] = true;
            pi[v->nodeKey]= u;
            DFS_visit(v->nodeKey, time);
        }
        else if (color[v->nodeKey] == 'b'){
            hasCycle = true;
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

    Node* v = head[start];

    /*
    //test min heap
    vector<int> temp = {3, 2 ,1, 6, 4,5};
    BinaryHeap b;
    b.printMinHeap(temp);
    b.HeapSort(temp);
    cout << endl ;
    cout << "=======after======" << endl;
    b.printMinHeap(temp);
    int m = b.ExtractMaxFromHeap(temp);
    cout << "m is: " << m;
    */
    
    
    for (int i = 0; i < nodeNum; ++i){
        int maxVertex = ExtractMax(this->visited, this->weight);
        // cout << " max vertex" << maxVertex << endl;
        visited[maxVertex] = true;
        Node* v = head[maxVertex];

       
        while(v != nullptr){
            if(!visited[v->nodeKey] && v->cost > weight[v->nodeKey]){   
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
    // sort(visited_weight.begin(), visited_weight.end());
    return minVertex;
}

void Graph::primRemoveEdge()
{
    std::vector< std::pair<int, Node*> > removeNode;
    int removeCost = 0;
    // initially, we add new edges undirected a->b, b->a
    // now we only need to add those is in the input to remove 
    
    for(int i = 0; i < nodeNum; i++){
        Node* a = this->head[i];
        while(a!=  nullptr){    
            // undirected
            if (  (pi[i] != a->nodeKey && pi[ a->nodeKey]!= i) ) // not in MST and not the starting point
            {
                // cout << "not in MST" <<  "i: " << i << ", nodeKey" << a->nodeKey <<  ", cost" <<  a->cost <<  endl;;
                if (std::find(edgeSet[i].begin(),edgeSet[i].end(),a->nodeKey) != edgeSet[i].end())  // is origin input
                    {
                        removeNode.push_back(std::make_pair(i,a)); 
                        removeCost += a->cost;
                    } 
                    // removeNode is a vector of Pairs
                    // <(start1,Node1), (start2,Node2)...>
                    ;
            }
            a = a->next;
        }
    }

    cout << "========= Prim Remove edges: (start,end,cost) =========" << endl;
    if (removeNode.size()!= 0)  // has cycle
    {
        for(int i = 0 ; i < removeNode.size(); ++i)
            cout << removeNode[i].first << " " << removeNode[i].second->nodeKey << " " << removeNode[i].second->cost << endl;
        cout << "Has Cycle: " << removeNode.size() << " edges removed!\n" << "Cost: " << removeCost << endl;
    
    }
    else  // no cycle
        cout << "No remove edges!" << endl;   
    
    
}
/////////////////////////////////////////////////////////////

// Heap sort method
void BinaryHeap::HeapSort(std::vector<int>& data) {
    // Build Max-Heap
    BuildMinHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--){
        swap(data[0],data[i]);
        heapSize--;
        MinHeapify(data,0);
    }
}

void BinaryHeap::printMinHeap(std::vector<int>& data)
{
    for(int i = 0; i < data.size(); i++){
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
    if (smallest != root){
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

////////////////Kruskal's////////////////////////////////////////////
int Graph::find(subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}

void Graph::Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}


void Graph::KruskalMST()
{

    int V = this-> nodeNum;
    int E = this-> edgeNum;


    Edge tree[V]; // Tnis will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
 

    // Allocate memory for creating V subsets
    subset* subsets = new subset[(V * sizeof(subset))];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < E) 
    {
        // Pick the largest edge 
        Edge next_edge = this->sortedEdgeList[i++];
        // cout << "choose" << next_edge.src << " " << next_edge.dest << " " <<next_edge.weight << endl;
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);


        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y) {
            tree[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the
    // built MST
    std::cout << "========= Kruskal MST =========\n";
    
    int maxCost = 0, origWeight = 0;
    std::vector<std::vector<int> > mst(nodeNum);  // create a new mst 
    // mst.resize(nodeNum);
    for (size_t i = 0; i < e; ++i) 
    {
        // std::cout << tree[i].src << " -- " << tree[i].dest
        //      << " == " << tree[i].weight<< endl;
        maxCost += tree[i].weight;
        int src = tree[i].src;
        int dest = tree[i].dest;

        mst[src].push_back(dest);  //add the edges to mst
        if (graphType == 'u')
            mst[dest].push_back(src);  //add the edges to mst, in another direction
    }
    // return;
    std::cout << "Maximum Cost: " << maxCost << endl;
    
    this->KruskalRemoveEdge(mst);

}


void Graph::countingSort()
{
    // given edgeList, sort the weight, and finish sortedEdgeList
    const int n = edgeNum;
    std::vector<int> temp(201, 0);  // edge weight from 0 to 200, 201 numbers

    for(int i = 0; i < n; ++i){
        temp[edgeList[i].weight]++;
    }
    for(int i = 1; i <= 201; ++i){
        temp[i] += temp[i-1];
    }
    sortedEdgeList.resize(n);
    for(int i = n-1; i >=0; --i){
        sortedEdgeList[temp[edgeList[i].weight] - 1] = edgeList[i];
        --temp[edgeList[i].weight];
    }

    std::reverse(sortedEdgeList.begin(),sortedEdgeList.end());
    for(int i = 0; i < sortedEdgeList.size(); ++i){ 
        sortedEdgeList[i].weight-=100;  // shift back weight to (-100, 100)
        edgeList[i].weight -= 100;
    }
    // check counting sort
    // for(int i = 0 ; i < sortedEdgeList.size() ; ++i)
    //     cout << sortedEdgeList[i].src << " " << sortedEdgeList[i].dest << " " << sortedEdgeList[i].weight << endl;

}

void Graph::KruskalRemoveEdge(std::vector<std::vector<int> > mst)
{
    // print out mst
    // for(int i = 0; i < mst.size(); i++){
    //     for(int j = 0; j < mst[i].size(); j++){
    //         if (mst[i].size() != 0)
    //             cout << "MST: " << mst[i][j].src << " " << mst[i][j].dest << " "<< mst[i][j].weight << endl;}
    // }


    std::vector<Edge> removeEdge;
    Edge temp;
    for(int i = 0; i < nodeNum; i++){
        Node* a = this->head[i];
        while(a!=  nullptr){
            
            if (!(std::find(mst[i].begin(),mst[i].end(),a->nodeKey) != mst[i].end())){
                if (std::find(edgeSet[i].begin(),edgeSet[i].end(),a->nodeKey) != edgeSet[i].end()){  // is origin input
                temp.src = i;
                temp.dest = a->nodeKey;
                temp.weight = a->cost;
                removeEdge.push_back(temp);
                }
            }
            a = a->next;
        }
    }


    int costSum = 0;
    std::cout << "========= Kruskal Remove edges: (start,end,cost) =========" << endl;
    if (removeEdge.size()!= 0)  // has cycle
    {
        for(int i = 0 ; i < removeEdge.size(); ++i){
            // cout << removeEdge[i].src << " " << removeEdge[i].dest << " " << removeEdge[i].weight << endl;
            costSum += removeEdge[i].weight;
        }
        cout << "Has Cycle: " << removeEdge.size() << " edges removed!\n" << "Cost: " << costSum << endl;
    
    }
    else  // no cycle
        cout << "No remove edges!" << endl;   
    
}
