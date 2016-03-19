#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <set>
#include <map>
#include <list>
/**
*   Kuba Kowalski
*   Paweł Gumny
**/

struct Edge
{
    int beginVertex;
    int endVertex;
    float cost;

    bool operator<(const Edge& e) const
    {
        return beginVertex<e.beginVertex || (!(beginVertex<e.beginVertex ) && endVertex<e.endVertex);
    }
};

class Graph
{
private:
    int m = 0;
    //vertices
    std::set<int> V;
    //key   ->  first vertex a
    //value ->  vector of seconds vertices b with proper cost
    //a<b always

    std::map<int, std::multiset<Edge> > E;
    //key   ->  cost
    //value ->  vector of edges
    std::map<float, std::vector<std::pair<int, int> > > Ecost;

    int getN();
    int DFSRec(int current, std::map<int, int> &visited, int cun);
    std::vector<int> findNeighbors(int ver);
    std::list<int> cycle(int beginVertex);
public:
    void putEdge(int a, int b, float c);
    void putEdge(const Edge &e);
    void putVertex(int v);
    void print();
    Graph primMST();
    std::map<int, int> DFS(int root);
    std::set<int> oddVertices();
    Graph subgraph(std::set<int> vertices);
    Graph minimumWeightedMatching();
    Graph graphUnion(Graph G);
    std::list<int> eulerianCycle();
    static std::list<int> makeEulerianCycleHamiltonian(const std::list<int>& eulerianCycle);
    std::list<int> christofides();
};


#endif
