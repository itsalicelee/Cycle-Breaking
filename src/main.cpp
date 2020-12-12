// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2020 fall Algorithm PA3:Cycle Breaking]
//  Date       2020/12/10
// **************************************************************************

#include<iostream>
#include<fstream>
#include<utility>
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
    Graph g(nodeNum,graphType);
    
    Edge edges;

    for(size_t i = 0; i < edgeNum; ++i){
        fin >> start >> end >> weight;
    edges.src = start;
    edges.dest = end;
    edges.weight = weight;
    G.addEdge(edges);
    }
    
    // print adjacency list representation of graph
    for (int i = 0; i < nodeNum; i++)
    {  
        G.printList(i, G.head[i]);  // print all neighboring vertices of vertex i
    }
    G.DFS();
    G.PrimMST();


    // for (int i = 0; i < nodeNum; i++)
    // {  
    //     cout << G.head[i]->val << ": " << G.head[i]->d << " " <<  G.head[i]->f << endl;  
    // }
    //cout << G.isCycle();
    //////////// algorithm start ////////////////

    

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
