#include<queue>
#include<vector>
#include<utility>
#include<stdlib.h>
#include<set>
#include<list>
#include<algorithm>
#include<iostream>
#include"cycleBreaking.h"
using namespace std;



Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    h = new list<int>[nodeNum];
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
        visit.push_back(false);

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
            std::cout << "("<< i << "," <<a->nodeKey << "," << a->cost  << ")"<< endl;
            a = a ->next;
        }
        std::cout << endl;
    }

    // h is a vector of vector of nodes
    // for(int i = 0; i < nodeNum; ++i){
    //     for(int j = 0; j < h[i].size(); j++)
    //         std::cout << i << ": " << h[i][j]->nodeKey  << " " << h[i][j]->cost << endl;
    // }
}

// Destructor
Graph::~Graph()
{
    for (int i = 0; i < nodeNum; i++){
        
        delete[] head[i];
    }
    delete[] h;
    delete[] head;
}

// print all neighboring vertices of given vertex
void Graph::printList(int i)
{
    std::cout << "========= (Node i, Neighbor, Cost) of node i =========" << endl;
    std::cout << "i is:" << i << endl;
    //given i and G.head[i]
    Node* ptr = this->head[i];
    
	while (ptr != nullptr){   
		std::cout << "(" << i << ", " << ptr->nodeKey << ", " << ptr->cost << ") ";
		ptr = ptr->next;
	}

    //  h is a vector of vector of nodes
    // for(int k = 0; k < h[i].size(); ++k)
    //     std::cout << h[i][k]->nodeKey << " "<<  h[i][k]->cost << endl;
    std::cout << endl;
    std::cout << endl;
}



void Graph::printDFS()
{
    std::cout << "========= DFS =========" << endl;
	for (int i = 0; i < nodeNum; ++i)
		std::cout << i << ": " <<  "discover time: " << d[i] << ", finish time: " << f[i] << " " << endl;
    std::cout << endl;
}





////////////////Kruskal's////////////////////////////
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


std::vector<Edge> Graph::KruskalMST()
{

    int V = this-> nodeNum;
    int E = this-> edgeNum;

    // vector<Edge> tree(V);
    Edge tree[V]; // store the result MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
 
    std::vector<Edge> sortedEdgeList = this->countingSort(this->edgeList); // sort the edges from largest to smallest 
    std::reverse(sortedEdgeList.begin(),sortedEdgeList.end());

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
        Edge next_edge = sortedEdgeList[i++];
        // cout << "choose" << next_edge.src << " " << next_edge.dest << " " <<next_edge.weight << endl;
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);


        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y) {
            tree[e++] = next_edge;
            // tree.push_back(next_edge);
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the
    // print MST
    std::cout << "========= Kruskal MST =========\n";
    
    int maxCost = 0, origWeight = 0;
    std::vector<std::vector<int> > mst(nodeNum);  // create a new mst 
    // mst.resize(nodeNum);
    for (int i = 0; i < e; ++i) 
    {
        std::cout << tree[i].src << " -- " << tree[i].dest
             << " == " << tree[i].weight<< endl;
        maxCost += tree[i].weight;
        int src = tree[i].src;
        int dest = tree[i].dest;

        mst[src].push_back(dest);  //add the edges to mst
        if (graphType == 'u')
            mst[dest].push_back(src);  //add the edges to mst, in another direction
    }
    // return
    // std::cout << "Maximum Cost: " << maxCost << endl;
    std::vector<Edge> treeVec(tree, tree+V-1);  // used in remove!
    std::vector<Edge> ans = this->KruskalRemoveEdge(mst, treeVec);
    
    return ans;
    // test tree in array
    // for(int i  = 0; i < V-1; i++)
    //     cout << tree[i].src << " " << tree[i].dest << " " << tree[i].weight << endl;
    
    
    // //test tree in vector
    // for(int i  = 0; i < treeVec.size(); i++)
    //     cout << treeVec[i].src << " " << treeVec[i].dest << " " << treeVec[i].weight << endl;
}


std::vector<Edge > Graph::countingSort(std::vector<Edge > list)
{
    // given edgeList, sort the weight, and finish sortedEdgeList
    std::vector<Edge> sortedEdgeList;
    const int n = list.size();
    std::vector<int> temp(201, 0);  // edge weight from 0 to 200, 201 numbers

    for(int i = 0; i < n; ++i){
        temp[list[i].weight]++;
    }
    for(int i = 1; i <= 201; ++i){
        temp[i] += temp[i-1];
    }
    sortedEdgeList.resize(n);
    for(int i = n-1; i >=0; --i){
        sortedEdgeList[temp[list[i].weight] - 1] = list[i];
        --temp[list[i].weight];
    }

    
    for(int i = 0; i < sortedEdgeList.size(); ++i){ 
        sortedEdgeList[i].weight-=100;  // shift back weight to (-100, 100)
        list[i].weight -= 100;
    }
   
    return sortedEdgeList;
}

std::vector<Edge> Graph::KruskalRemoveEdge(std::vector<std::vector<int> > mst, std::vector<Edge> treeVec)
{   
    for(size_t i = 0; i < nodeNum; ++i){
        for(size_t j = 0; j < nodeNum; ++j)
            cout << map[i][j] << " ";
        cout << endl;
    }


    std::vector<Edge> removeEdge;
    Edge temp;
    for(int i = 0; i < nodeNum; ++i){
        Node* a = this->head[i];
        while(a!=  nullptr){

            if (!(std::find(mst[i].begin(),mst[i].end(),a->nodeKey) != mst[i].end())){
                // if (std::find(edgeSet[i].begin(),edgeSet[i].end(),a->nodeKey) != edgeSet[i].end())
                if (map[i][a->nodeKey] == true){  // is origin input
                temp.src = i;
                temp.dest = a->nodeKey;
                temp.weight = a->cost;
                removeEdge.push_back(temp);
                }
            }
            a = a->next;
        }
    }


    
    std::cout << "========= Kruskal Remove edges: (start,end,cost) =========" << endl;
    if (removeEdge.size()!= 0)  // has cycle
    {
        for(int i = 0 ; i < removeEdge.size(); ++i){
            std::cout << removeEdge[i].src << " " << removeEdge[i].dest << " " << removeEdge[i].weight << endl;
            cost += removeEdge[i].weight;
        }
        std::cout << "Has Cycle: " << removeEdge.size() << " edges removed!\n" << "Cost: " << cost<< endl;
    
    }
    else  // no cycle
        std::cout << "No remove edges!" << endl;   
    
    std::vector<Edge> ans = removeEdge;
    if (graphType == 'd')
         ans = this->addEdge(treeVec, removeEdge);

    return ans;
    
    // return removeEdge;
}
////////////////////////////////////

std::vector<Edge> Graph::addEdge(std::vector<Edge>& treeVec, std::vector<Edge>& removeEdge)
{
   
    std::cout << "remove Edge function start" << endl;

    // test original remove edge
    // for(int i = 0; i < removeEdge.size(); ++i)
    //     cout << removeEdge[i].src << " " << removeEdge[i].dest << " " << removeEdge[i].weight << endl;

    for(int i = 0; i < removeEdge.size(); ++i)
        removeEdge[i].weight += 100;  // shift the edge so as to do counting sort
    
   

    Graph T(treeVec.size(), treeVec.size() + 1, graphType);

    std::vector<Edge> sortedRemove = this->countingSort(removeEdge);

    cout << "check sorted remove edge " << endl;
    for(int i = 0; i < sortedRemove.size(); ++i)
        std::cout << sortedRemove[i].src << " " << sortedRemove[i].dest << " " << sortedRemove[i].weight << endl;



    // add edges to original mst tree
    for(int i = 0 ; i < treeVec.size(); ++i)
    {
        // cout << treeVec[i].src << " " << treeVec[i].dest << " " << treeVec[i].weight << endl;
        Node* v = new Node();
    	v->nodeKey = treeVec[i].dest;
    	v->cost = treeVec[i].weight ;
    	v->next = T.head[treeVec[i].src];
    	T.head[treeVec[i].src] = v;
        T.h[treeVec[i].src].push_back(treeVec[i].dest);  // for dfs
    }

    
    std::cout << "print T DFS" << endl;

    // T.printGraph();
    // T.DFS();
    // T.printDFS();

    // T.hasCycle = false;
    // T.DFS();
    // T.printDFS();
    
    int i = sortedRemove.size()-1;  // counter varibale; start from the largest edge
    
    while(i >= 0)
    {

    // std::cout << "after adding" << endl; 
    Edge anEdge = sortedRemove[i];
    int start = anEdge.src;
    int dest = anEdge.dest;
    int weight = anEdge.weight;

    if (weight < 0)  // we dont want to add negative weight to mst
        break;
    
    Node* u = new Node();
    u ->nodeKey = dest;
    u->cost = weight ;
    u->next = T.head[start];
    T.head[start] = u;
    T.h[start].push_back(dest);
    
    // cout << "start" << start << " " << dest << " " << weight << endl;
    // cout << "cycle" <<T.isCyclic() << endl;
    // T.printGraph();
    // T.DFS();
    // T.printDFS();

    if (T.hasCycle()){
        // cout << "!!Cycle Detected!!" << endl;
        T.h[start].pop_back(); // cannot put in mst, remove  from adjancency list
    }
    else{  // no cycle 
        cost -= sortedRemove[i].weight;
        sortedRemove[i].weight = -MAX_WEIGHT;  // remove it from sortedRemove
        
    }


    i--;
    // check remove edges in the loop
    // std::cout << "removing" << endl;
    // for(int j = 0; j < sortedRemove.size(); j++){
    //     if(sortedRemove[j].weight != -MAX_WEIGHT)
    //         std::cout << sortedRemove[j].src << " " << sortedRemove[j].dest << " " << sortedRemove[j].weight << endl;
    // }

    }
    
    int finalCost = 0;
    int edgecnt  = 0;
    std::cout << "final solution" << endl;
    std::cout << "--------------" << endl;

    for(int j = 0; j < sortedRemove.size(); j++){
        if(sortedRemove[j].weight != -MAX_WEIGHT){
            finalCost += sortedRemove[j].weight;
            edgecnt += 1;
            std::cout << sortedRemove[j].src << " " << sortedRemove[j].dest << " " << sortedRemove[j].weight << endl;
        }
    }

    cout << "final cost: " << finalCost << ", mst edge cnt: " << edgecnt << endl;
    return sortedRemove;
    
}




bool Graph::isCyclicUtil(int v, bool visited[], bool *stack)
{
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
	    stack[v] = true;

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for (i = h[v].begin(); i != h[v].end(); ++i){
			if (!visited[*i] && isCyclicUtil(*i, visited, stack))
				return true;
			else if (stack[*i])
				return true;
		}

	}
    stack[v] = false;  // remove the vertex from recursion stack
	return false;
}


bool Graph::hasCycle()
{
    // If the graph contains a cycle, return true, else false.
	
	bool* visited = new bool[nodeNum];
	bool* stack = new bool[nodeNum];
	for (int i = 0; i < nodeNum; ++i){
		visited[i] = false;  // mark all the vertices as not visited 
		stack[i] = false;  // mark the vertices not part of recursion stack
	}

	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for (int i = 0; i < nodeNum; i++)
		if (isCyclicUtil(i, visited, stack))
			return true;

	return false;
}


/*

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
    this->visit[u] = true;
    
    Node* v = head[u];
    while(v != nullptr){
        if(color[v->nodeKey] == 'w'){
            visit[v->nodeKey] = true;
            pi[v->nodeKey]= u;
            DFS_visit(v->nodeKey, time);
        }
        else if (color[v->nodeKey] == 'b'){
            hasCycle = true;  // not sure
        }
        
        v = v->next;
    }
    this->color[u] = 'b';
    time++;
    this->f[u] = time; 

}
void Graph::initialize()  // initialize d, f, pi, color, array
{
    for(int i = 0; i < nodeNum; i++){
        d[i] = 0;
        f[i] = 0;
        pi[i] = -1;
        color[i] = 'w';
        weight[i] = -MAX_WEIGHT;
        visit[i] = false;
        
    }
}
void Graph::PrimMST(int start)
{
    // Create Maximum Spanning Tree, want to remove edges with minimum weight
    this->initialize();  // initialize all arrays
    this->weight[start] = 0;
    this->pi[start] = -MAX_WEIGHT;

    Node* v = head[start];

    
    //test min heap
    // vector<int> temp = {3, 2 ,1, 6, 4,5};
    // BinaryHeap b;
    // b.printMinHeap(temp);
    // b.HeapSort(temp);
    // cout << endl ;
    // cout << "=======after======" << endl;
    // b.printMinHeap(temp);
    // int m = b.ExtractMaxFromHeap(temp);
    // cout << "m is: " << m;

    
    
    for (int i = 0; i < nodeNum; ++i){
        int maxVertex = ExtractMax(this->visit, this->weight);
        // cout << " max vertex" << maxVertex << endl;
        visit[maxVertex] = true;
        Node* v = head[maxVertex];

       
        while(v != nullptr){
            if(!visit[v->nodeKey] && v->cost > weight[v->nodeKey]){   
                pi[v->nodeKey] = maxVertex;
                weight[v->nodeKey] = v->cost;
            }
            v = v ->next;
        }

    }
  
}

void Graph::printPrim()
{
    std::cout << "========= Prim's Algorithm =========" << endl;
    int totalCost = 0;
	for (int i = 0; i < nodeNum; ++i){
		std::cout <<  "i: " << i << ": " <<  "pi: " << pi[i] << ",   weight: " << weight[i] << " " << endl;
        totalCost += weight[i];

	}
    std::cout << "Total cost is: " << totalCost << endl;
    std::cout << endl;
}


int Graph::ExtractMax(bool_arr visited, int_arr weight)
{
    int minVertex = -1;
    for(int i = 0; i < nodeNum; ++i){
        if (!visited[i] && (minVertex == -1 || weight[i] > weight[minVertex])){
            minVertex = i;
        }
    }
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

    std::cout << "========= Prim Remove edges: (start,end,cost) =========" << endl;
    if (removeNode.size()!= 0)  // has cycle
    {
        for(int i = 0 ; i < removeNode.size(); ++i)
            std::cout << removeNode[i].first << " " << removeNode[i].second->nodeKey << " " << removeNode[i].second->cost << endl;
        std::cout << "Has Cycle: " << removeNode.size() << " edges removed!\n" << "Cost: " << removeCost << endl;
    
    }
    else  // no cycle
        std::cout << "No remove edges!" << endl;   
    
    
}


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
        std::cout << data[i] << endl;
    }
}

//Max heapify
void BinaryHeap::MinHeapify(std::vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    //  : Please complete max-heapify code here
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

    int max = data[0];
    data[0] = data[data.back()];
    data.pop_back();
    MinHeapify(data,0);
    return max;
}
*/