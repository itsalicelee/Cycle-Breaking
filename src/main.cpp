// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2020 fall Algorithm PA3:Cycle Breaker]
//  Date       2020/12/10
// **************************************************************************

#include<iostream>
#include<fstream>
#include<utility>
#include<list>
#include"cycleBreaking.h"
using namespace std;

void help_message() {
    cout << "usage: ./bin/cb inputs/<input file> outputs/<output file>" << "\n";
}

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

    char type;  // undirected or directed 
    int node, edge;  // n, m
    fin >> type;
    fin >> node;
    fin >> edge;
    

    /*
   


    for(size_t i = 0; i < n/2 ; ++i)
    {
        fin >> start >> end;
        data[start] = make_pair(start, end);
        data[end] = make_pair(end, start);
    }


    //////////// algorithm start ////////////////

    vector<int> output = findPair(data, n);
    

    //////////// write the output file ///////////

    int cnt = output.front();   // the first element in output is the number of output line
    output.erase(output.begin());  // delete the first element
    for(size_t i = 0; i < output.size(); ++i)
        output[i] = data[output[i]].second;
    sort(output.begin(), output.begin()+cnt);  // sort by the first element
    
    fout << cnt << "\n";  // write in the total chord number

    for (size_t i = 0; i < output.size(); ++i) 
        fout << output[i] << " " << data[output[i]].second << "\n";

    fin.close();
    fout.close();
    */
    return 0;
}
