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
    }
    
}


void Graph::printGraph()
{
    std::cout << "========= Graph =========" << endl;
    // print adjacency list representation of graph
    for (size_t i = 0; i < nodeNum; ++i){  
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


Graph::~Graph() // Destructor
{
    for (size_t i = 0; i < nodeNum; ++i){
        
        delete[] head[i];
    }
    delete[] h;
    delete[] head;
}

void Graph::printList(int i)  // print all neighboring vertices of given vertex
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

}


////////////////Kruskal's////////////////////////////
int Graph::find(subset subsets[], int i)
{
    if (i != subsets[i].parent)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}

void Graph::Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else {
        subsets[yroot].parent = xroot;  // If ranks are same, then make one as root and
        subsets[xroot].rank++;  // increment its rank by one
    }
}


std::vector<Edge> Graph::KruskalMST()
{

    Edge tree[nodeNum]; // store the result MST
    
    std::vector<Edge> sortedEdgeList = this->countingSort(this->edgeList); // sort the edges from largest to smallest 
    std::reverse(sortedEdgeList.begin(),sortedEdgeList.end());

    // create V subsets
    subset* subsets = new subset[(nodeNum * sizeof(subset))];
 
    // Create V subsets with single elements
    for (size_t i = 0; i < nodeNum; ++i) {
        subsets[i].rank = 0;
        subsets[i].parent = i;
    }

    int cur = 0; // An index variable, used for ans
    int i = 0; // An index variable, used for sorted edges
    // Number of edges to be taken is equal to V-1
    while (cur < nodeNum - 1 && i < edgeNum) 
    {
        
        Edge largest_edge = sortedEdgeList[i++];  // Pick the largest edge 

        int x = find(subsets, largest_edge.src);
        int y = find(subsets, largest_edge.dest);

        if (x != y) {
            tree[cur++] = largest_edge;  // does't cause cycle, include it in result 
            Union(subsets, x, y);  // check next edge
        }
    }
 

    // std::cout << "========= Kruskal MST =========\n";
    
    int src, dest = 0;
    std::vector<std::vector<int> > mst(nodeNum);  // create a new mst 
    for (size_t i = 0; i < cur; ++i) 
    {
        src = tree[i].src;
        dest = tree[i].dest;

        mst[src].push_back(dest);  //add the edges to mst
        if (graphType == 'u')
            mst[dest].push_back(src);  //add the edges to mst, in another direction
    }

    std::vector<Edge> treeVec(tree, tree+nodeNum-1);  // used in remove!
    std::vector<Edge> ans = this->KruskalRemoveEdge(mst, treeVec);

    delete[] subsets; 

    
    // test tree in array
    // for(int i  = 0; i < V-1; i++)
    //     cout << tree[i].src << " " << tree[i].dest << " " << tree[i].weight << endl;
    
    
    //test tree in vector
    // cout << "size" << treeVec.size() << endl;
    // for(int i  = 0; i < treeVec.size(); i++)
    //     cout << treeVec[i].src << " " << treeVec[i].dest << " " << treeVec[i].weight << endl;
    return ans;
}


std::vector<Edge> Graph::countingSort(std::vector<Edge > list)
{
    // given edgeList, sort the weight, and finish sortedEdgeList
    std::vector<Edge> sortedEdgeList;
    const int n = list.size();
    sortedEdgeList.resize(n);
    std::vector<int> temp(201, 0);  // edge weight from 0 to 200, 201 numbers

    for(size_t i = 0; i < n; ++i){
        temp[list[i].weight]++;
    }
    for(int i = 1; i <= 201; ++i){
        temp[i] += temp[i-1];
    }
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
    // test map, which records the neighboring vertex of one to another
    // for(size_t i = 0; i < nodeNum; ++i){
    //     for(size_t j = 0; j < nodeNum; ++j)
    //         cout << map[i][j] << " ";
    //     cout << endl;
    // }

    std::vector<Edge> removeEdge;
    Edge temp;
    for(size_t i = 0; i < nodeNum; ++i){
        Node* a = this->head[i];
        while(a!=  nullptr){

            if ((std::find(mst[i].begin(),mst[i].end(),a->nodeKey) == mst[i].end()) // not in mst
                    && map[i][a->nodeKey] == true)  // is orig input
            {
                temp.src = i;
                temp.dest = a->nodeKey;
                temp.weight = a->cost;
                removeEdge.push_back(temp);
            }
            a = a->next;
        }
    }

    for(int i = 0 ; i < removeEdge.size(); ++i){
        cost += removeEdge[i].weight;
    }

    // uncomment to print
    // int origCost = 0;
    // std::cout << "========= Kruskal Remove edges: (start,end,cost) =========" << endl;
    // if (removeEdge.size()!= 0)  // has cycle
    // {
    //     for(int i = 0 ; i < removeEdge.size(); ++i){
    //         std::cout << removeEdge[i].src << " " << removeEdge[i].dest << " " << removeEdge[i].weight << endl;
    //         origCost += removeEdge[i].weight;
    //     }
    //    std::cout << "Has Cycle: " << removeEdge.size() << " edges removed!\n" << "origCost: " << origCost<< endl;
    // }
    // else  // no cycle
    //     std::cout << "No remove edges!" << endl;   

    std::vector<Edge> ans = removeEdge;

    if (graphType == 'd')
        ans = this->addEdge(treeVec, removeEdge);

    return ans;
}


std::vector<Edge> Graph::addEdge(std::vector<Edge>& treeVec, std::vector<Edge>& removeEdge)
{
    for(int i = 0; i < removeEdge.size(); ++i)
        removeEdge[i].weight += 100;  // shift the edge so as to do counting sort
    
    std::vector<Edge> sortedRemove = this->countingSort(removeEdge);
    Graph T(treeVec.size(), treeVec.size() + 1, graphType); // treeVec is a vector of edges

    // add edges to original mst tree
    for(size_t i = 0 ; i < treeVec.size(); ++i)
    {
        // cout << treeVec[i].src << " " << treeVec[i].dest << " " << treeVec[i].weight << endl;
        Node* v = new Node;
    	v->nodeKey = treeVec[i].dest;
    	v->cost = treeVec[i].weight ;
    	v->next = T.head[treeVec[i].src];
    	T.head[treeVec[i].src] = v;
        T.h[treeVec[i].src].push_back(treeVec[i].dest);  // for dfs
    }

    
    int i = sortedRemove.size()-1;  // counter varibale; start from the largest edge

    int start, dest, weight = 0;
    while(i >= 0)
    {
        Edge anEdge = sortedRemove[i];
        start = anEdge.src;
        dest = anEdge.dest;
        weight = anEdge.weight;

        if (weight < 0)  // we dont want to add negative weight to mst
            break;
        
        Node* u = new Node;
        u ->nodeKey = dest;
        u->cost = weight ;
        u->next = T.head[start];
        T.head[start] = u;
        T.h[start].push_back(dest);

        if (T.hasCycle()){
            T.h[start].pop_back(); // cannot put in mst, remove  from adjancency list
            // cout << "cycle!!" << endl;
        }
        else{  // no cycle 
            cost -= sortedRemove[i].weight;
            sortedRemove[i].weight = MAX_WEIGHT;  // remove it from sortedRemove
        }
        i--;
    }
    
    return sortedRemove;
}


bool Graph::isCycleUtil(int i, bool visited[], bool *stack)
{
	if (visited[i] == false)
	{
		visited[i] = true;  // mark current node as visited 
	    stack[i] = true;  // mark current node part of recursion stack

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator j;
		for (j = h[i].begin(); j != h[i].end(); ++j){
			if (!visited[*j] && isCycleUtil(*j, visited, stack))
				return true;
			else if (stack[*j])
				return true;
		}
	}
    stack[i] = false;  // remove the vertex from recursion stack
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

	for (int i = 0; i < nodeNum; ++i)  // recursive to  to detect cycle in different DFS trees
		if (isCycleUtil(i, visited, stack))
			return true;
    delete[] visited;
    delete[] stack;
	return false;
}
