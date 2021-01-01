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
    
   
    G.map = new bool* [nodeNum];  // bool table for memorize initial input
    for(size_t i = 0; i < nodeNum; ++i)
        G.map[i] = new bool [nodeNum];
    
    for(size_t i = 0; i < nodeNum; ++i){
        for(size_t j = 0; j < nodeNum; ++j)
            G.map[i][j] = false;
    }

    // allocate memory for edgeSet and weightSet
    // G.edgeSet.resize(nodeNum);
    // G.weightSet.resize(nodeNum);
    Edge anEdge;
    for(size_t i = 0; i < edgeNum; ++i){
        fin >> start >> end >> weight;
        Node* v = new Node;
    	v->nodeKey = end;
    	v->cost = weight;
    	v->next = G.head[start];
    	G.head[start] = v;
        anEdge.src = start;
        anEdge.dest = end;
        anEdge.weight = weight+100;
        G.h[start].push_back(end);
        
        
        G.map[start][end] = true;  // map records the initial input
    
        G.edgeList.push_back(anEdge);  // used for counting sort
        

        // memorize the initial edges
        // G.edgeSet[start].push_back(end);
        // G.weightSet[start].push_back(weight);
       

        if(graphType == 'u')
        {
            Node* u = new Node;
            u->nodeKey = start;
            u->cost = weight;
            u->next = G.head[end];
            G.head[end] = u;

            anEdge.src = start;
            anEdge.dest =  end;
            anEdge.weight = weight+100;
            G.h[end].push_back(start);

        }
    }
        
    //////////// algorithm start ////////////////

    std::vector<Edge> final = G.KruskalMST();
    int cost = G.getCost();

    
    // release memory
    for(size_t i = 0; i < nodeNum; ++i)
        delete[] G.map[i];
    delete[] G.map;

    


    //////////// write the output file ///////////
    
    /*
    print out total weight of removed edges to make the input graph acyclic, 
    followed by a list of these removed edges and their weights.
    if the graph has no cycle, print out 0
    */

    
    if (final.size()!= 0)  // has cycle
    {
        fout << cost << endl;
        for(int i = 0 ; i < final.size(); ++i){
            if(final[i].weight != MAX_WEIGHT)
                fout << final[i].src << " " << final[i].dest << " " << final[i].weight << endl;
        }
    }
    else  // no cycle
        fout << "0";

    fin.close();
    fout.close();
    
    return 0;
}
