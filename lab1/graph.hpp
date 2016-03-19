#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
/**
*   Kuba Kowalski
**/

class Graph
{
private:
    int n = 0, m = 0;
    //vertices
    std::vector<int> V;
    //key   ->  first vertex a
    //value ->  vector of seconds vertices b with proper cost
    //a<b always
    std::map<int, std::vector<std::pair<int, float> > > E;
    //key   ->  cost
    //value ->  vector of edges
    std::map<float, std::vector<std::pair<int, int> > > Ecost;

    int DFSRec(int current, std::map<int, int> &visited, int cun);
    std::vector<int> findNeighbors(int ver);
public:
    void putEdge(int a, int b, float c);
    void print();
    Graph primMST();
    std::map<int, int> DFS(int root);
    Graph getOddSubgraph();


    void sometest(std::vector<int> *vv, int cun);
};


#endif
