#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <set>
#include <map>
/**
*   Kuba Kowalski
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

    std::map<int, std::set<Edge> > E;
    //key   ->  cost
    //value ->  vector of edges
    std::map<float, std::vector<std::pair<int, int> > > Ecost;

    int getN();
    int DFSRec(int current, std::map<int, int> &visited, int cun);
    std::vector<int> findNeighbors(int ver);
public:
    void putEdge(int a, int b, float c);
    void putEdge(Edge e);
    void putVertex(int v);
    void print();
    Graph primMST();
    std::map<int, int> DFS(int root);
    Graph getOddSubgraph();


    void sometest(std::vector<int> *vv, int cun);
};


#endif
