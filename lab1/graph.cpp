#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "graph.hpp"
/**
*   Kuba Kowalski
*   Paweł Gumny
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

    // if(E[a].count({a,b})==0)
    {
        m++;
        E[a].insert({a, b, cost});
        E[b].insert({b, a, cost});
        Ecost[cost].push_back({a,b});
    }
}

void Graph::putEdge(const Edge& e)
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

std::set<int> Graph::oddVertices()
{
    std::set<int> oddVertices;
    for(auto neighbours : E)
        if(neighbours.second.size() %2)
        {
            oddVertices.insert(neighbours.first);
        }
    return oddVertices;
}

Graph Graph::subgraph(std::set<int> vertices)
{
    Graph ret;
    for(auto vertex : V)
        if(vertices.count(vertex))
            for(auto neighbour : E[vertex])
                if(vertices.count(neighbour.endVertex) &&
                        neighbour.beginVertex < neighbour.endVertex)
                    ret.putEdge(neighbour);

    return ret;
}

Graph Graph::minimumWeightedMatching()
{
    Graph out;
    std::set<int> unmatched = V;
    for(auto edgesWithCost : Ecost)
    {
        int cost = edgesWithCost.first;
        for(auto edgePoints : edgesWithCost.second)
            if(unmatched.count(edgePoints.first)&& unmatched.count(edgePoints.second))
            {
                out.putEdge(edgePoints.first, edgePoints.second, cost);
                unmatched.erase(edgePoints.first);
                unmatched.erase(edgePoints.second);
                if(unmatched.size() == 0)
                    break;
            }

        if(unmatched.size() == 0)
            break;
    }
    return out;
}

Graph Graph::graphUnion(Graph G)
{
    for(auto v : V)
        for(auto e : E[v])
            if(e.beginVertex < e.endVertex)
                G.putEdge(e);
    return G;
}

std::list<int> Graph::cycle(int beginVertex)
{
    std::list<int> out;
    out.push_back(beginVertex);
    int v = beginVertex;
    while(E[v].size())
    {
        int w = E[v].begin()->endVertex;
        E[v].erase(E[v].begin());
        E[w].erase({w,v});
        out.push_back(w);
        v = w;
    }
    return out;
}

std::list<int> Graph::eulerianCycle()
{
    Graph G = *this;
    std::list<int> out;
    out.push_back(*V.begin());
    auto insertionPoint = out.begin();
    while(insertionPoint != out.end())
    {
        std::list<int> list = G.cycle(*insertionPoint);
        auto oldInsertionPoint = insertionPoint;
        oldInsertionPoint--;
        out.insert(insertionPoint, list.begin(), --list.end());
        insertionPoint = oldInsertionPoint;
        insertionPoint++;
        while(insertionPoint != out.end() && G.E[*insertionPoint].size() == 0)
            insertionPoint++;
    }
    return out;
}

std::list<int> Graph::makeEulerianCycleHamiltonian(const std::list<int>& eulerianCycle)
{
    std::set<int> visited;
    std::list<int> out;
    for(int point:eulerianCycle)
    {
        if(visited.count(point) == 0)
            out.push_back(point);
        visited.insert(point);
    }
    out.push_back(out.front());
    return out;
}

std::list<int> Graph::christofides()
{
    auto T = primMST();
    return makeEulerianCycleHamiltonian(T.graphUnion(subgraph(T.oddVertices()).minimumWeightedMatching()).eulerianCycle());
}
