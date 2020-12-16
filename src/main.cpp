// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2020 fall Algorithm PA3:Cycle Breaking]
//  Date       2020/12/10
// **************************************************************************
/*
TODO
- add positive edges to MST until it has a cycle

*/

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
    
    // allocate memory for edgeSet and weightSet
    G.edgeSet.resize(nodeNum);
    G.weightSet.resize(nodeNum);
 


    for(size_t i = 0; i < edgeNum; ++i){
        fin >> start >> end >> weight;
        Node* v = new Node();
    	v->nodeKey = end;
    	v->cost = weight;
    	v->next = G.head[start];
    	G.head[start] = v;


        // memorize the initial edges
        G.edgeSet[start].push_back(end);
        G.weightSet[start].push_back(weight);

        if(graphType == 'u')
        {
            Node* u = new Node;
            u->nodeKey = start;
            u->cost = weight;
            u->next = G.head[end];
            G.head[end] = u;
            
        }
    }
   

    // test edgeSet and weightSet 
    cout << "========= Original Input =========" << endl;
    for(int i = 0; i < nodeNum; i++)
    {
        for(int j = 0; j < G.edgeSet.size(); j++)
            if (j < G.edgeSet[i].size())
                cout << i << " "<< G.edgeSet[i][j] << " " << G.weightSet[i][j] << endl;
    }

   

    
    //////////// algorithm start ////////////////

    // G.printGraph();
    G.DFS();
    // G.printDFS();
    // G.printList(1);
    G.PrimMST(0);
    G.printPrim();
    G.printRemoveEdge();
    
    if(G.hasCycle == true)
        cout << "This Graph Has Cycle!!!" << endl;
    else
        cout << "This Graph Has No Cycle!!!" << endl;
    
    

    //////////// write the output file ///////////
    
    /*
    print out total weight of removed edges to make the input graph acyclic, 
    followed by a list of these removed edges and their weights.
    if the graph has no cycle, print out 0
    */

    
    if (G.removeNode.size()!= 0)  // has cycle
    {
        fout << G.removeCost << endl;
        for(int i = 0 ; i < G.removeNode.size(); ++i)
            fout << G.removeNode[i].first << " " << G.removeNode[i].second->nodeKey << " " << G.removeNode[i].second->cost << endl;
    }
    else  // no cycle
        fout << "0";

    fin.close();
    fout.close();
    
    return 0;
}
