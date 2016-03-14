#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <utility>

#include "graph.hpp"
/**
*   Kuba Kowalski
**/

using namespace std;

void Graph::putEdge(int a, int b, float cost)
{
    if(a==b) return;


    //adding vertices without repetition
    bool v1=true;
    bool v2=true;
    for(auto ver : V)
    {
        if(v1 && ver==a) v1=false;
        if(v2 && ver==b) v2=false;
    }
    if(v1) {V.push_back(a); n++;}
    if(v2) {V.push_back(b); n++;}


    //adding edge without repetition
    if(a>b)
    {
        int c=a;
        a=b;
        b=c;
    }
    bool v=true;
    for(auto ver : E[a])
    {
        if(ver.first==b)
        {
            v = false;
            break;
        }
    }
    if(v)
    {
        E[a].push_back(pair<int, float>(b, cost));
        Ecost[cost].push_back(pair<int, int>(a,b));
        m++;
    }
}


vector<int> Graph::findNeighbors(int ver)
{
    vector<int> ret;
    for(auto edg : E)
    {
        if(edg.first>ver) break;

        if(edg.first==ver)
        {
            for(auto ver2 : edg.second)
            {
                ret.push_back(ver2.first);
            }
            break;
        }

        for(auto ver2 : edg.second)
        {
            if(ver2.first==ver) ret.push_back(edg.first);
        }
    }

    return ret;
}


void Graph::print()
{
    printf("Vertices:\n");
    for(auto ver : V)
    {
        printf("%d ", ver);
    }
    printf("\nLength: %d\n\n", n);

    printf("Edges:\n");
    for(auto edg : E)
    {
        printf("From: %d\n", edg.first);
        for(auto ver : edg.second)
        {
            printf("%d(%.1f) ", ver.first, ver.second);
        }
        printf("\n");
    }
    printf("---------\n");


    for(auto edg : Ecost)
    {
        printf("Cost: %.1f\n", edg.first);
        for(auto ver : edg.second)
        {
            printf("(%d,%d) ", ver.first, ver.second);
        }
        printf("\n");
    }
    printf("Length: %d\n\n", m);
}


Graph Graph::primMST()
{
    map<int, bool> visited;
    Graph ret;
    int a = Ecost.begin()->second[0].first;
    int b = Ecost.begin()->second[0].second;
    float c = Ecost.begin()->first;
    visited[a] = true;
    visited[b] = true;
    ret.putEdge(a,b,c);

    while(visited.size()<n)
    {
        for(auto cost : Ecost)
        {
            bool breakloop = false;
            for(auto edg : cost.second)
            {
                //cost->first   cost
                //edg->first    a
                //edg->second   b
                if( visited[edg.first] != visited[edg.second] )
                {
                    visited[edg.first]=true;
                    visited[edg.second]=true;
                    ret.putEdge(edg.first, edg.second, cost.first);
                    breakloop = true;
                    break;
                }
            }
            if (breakloop) break;
        }
    }
    return ret;
}


int Graph::DFS(int current, map<int, int> *visited, int cun)
{
    vector<int> neighbors = findNeighbors(current);
    (*visited)[current]=cun;
    for(auto ver : neighbors)
    {
        if((*visited)[ver]==0)
        {
            cun = DFS(ver, visited, cun+1);
        }
    }
    return cun;
}


void Graph::sometest(vector<int> *vv, int cun)
{
    vv->push_back(cun);
    if(cun!=0) sometest(vv, cun-1);
}





