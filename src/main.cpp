// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2020 fall Algorithm PA3:Cycle Breaking]
//  Date       2020/12/10
// **************************************************************************

#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<list>
#include<stdlib.h>
#include<stdio.h>
#include"cycleBreaking.h"
using namespace std;


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
    Graph G(edgeNum, nodeNum, graphType); // create a graph
    //Graph g(nodeNum,graphType);
    vector<Edge> edges;
    Edge anEdge;
    for(size_t i = 0; i < edgeNum; ++i){
        fin >> start >> end >> weight;
        Node* v = new Node();
    	v->nodeKey = end;
    	v->cost = weight;
    	v->next = G.head[start];
    	G.head[start] = v;
        anEdge.src = start;
        anEdge.dest = end;
        anEdge.weight = weight;
        edges.push_back(anEdge);

        if(graphType == 'u')
        {
            Node* u = new Node;
            u->nodeKey = start;
            u->cost = weight;
            u->next = G.head[end];
            G.head[end] = u;
        }
    }
    


  

   

    
    //////////// algorithm start ////////////////

    G.printGraph();
    G.DFS();
    G.printDFS();
    G.printList(1);
    G.PrimMST(0);
    G.printPrim();
    G.printRemoveEdge();
    

    //////////// write the output file ///////////
    
    /*
    print out total weight of removed edges to make the input graph acyclic, 
    followed by a list of these removed edges and their weights.
    if the graph has no cycle, print out 0
    */

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
