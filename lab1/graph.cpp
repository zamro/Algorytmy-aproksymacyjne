#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "graph.hpp"
/**
*   Kuba Kowalski
**/

using namespace std;

int Graph::getN()
{
    return V.size();
}

void Graph::putEdge(int a, int b, float cost)
{
    if(a==b) return;

    //adding vertices without repetition
    V.insert(a);
    V.insert(b);

    //adding edge without repetition
    if(a>b)
        std::swap(a,b);

    if(E[a].count({a,b,0})==0)
    {
        m++;
        E[a].insert({a, b, cost});
        E[b].insert({b, a, cost});
        Ecost[cost].push_back({a,b});
    }
}

void Graph::putEdge(Edge e)
{
    putEdge(e.beginVertex, e.endVertex, e.cost);
}

void Graph::putVertex(int v)
{
    V.insert(v);
}

vector<int> Graph::findNeighbors(int ver)
{
    vector<int> ret;
    for(auto edge : E[ver])
    {
        ret.push_back(edge.endVertex);
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
    printf("\nLength: %d\n\n", getN());

    printf("Edges:\n");
    for(auto edg : E)
    {
        printf("From: %d\n", edg.first);
        for(auto ver : edg.second)
        {
            printf("%d(%.1f) ", ver.endVertex, ver.cost);
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

    while(visited.size() < getN())
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

Graph Graph::getOddSubgraph()
{
    Graph ret;
    std::set<int> oddVertices;
    for(auto neighbours : E)
        if(neighbours.second.size() %2)
		{
			ret.putVertex(neighbours.first);
            oddVertices.insert(neighbours.first);
		}
    for(auto vertex : oddVertices)
        for(auto neighbour : E[vertex])
            if(oddVertices.count(neighbour.endVertex))
                ret.putEdge(neighbour);

    return ret;
}

int Graph::DFSRec(int current, map<int, int> &visited, int cun)
{
    vector<int> neighbors = findNeighbors(current);
    visited[current]=cun;
    for(auto ver : neighbors)
    {
        if(visited[ver]==0)
        {
            cun = DFSRec(ver, visited, cun+1);
        }
    }
    return cun;
}


std::map<int, int> Graph::DFS(int root)
{
    std::map<int, int> dfs;
    DFSRec(root, dfs, 1);
    return dfs;
}


void Graph::sometest(vector<int> *vv, int cun)
{
    vv->push_back(cun);
    if(cun!=0) sometest(vv, cun-1);
}
