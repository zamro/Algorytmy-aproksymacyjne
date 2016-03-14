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
    int n,m;
    //vertices
    std::vector<int> V;
    //key   ->  first vertex a
    //value ->  vector of seconds vertices b with proper cost
    //a<b always
    std::map<int, std::vector<std::pair<int, float> > > E;
    //key   ->  cost
    //value ->  vector of edges
    std::map<float, std::vector<std::pair<int, int> > > Ecost;

    std::vector<int> findNeighbors(int ver);
public:
    Graph() {n=0; m=0;};
    void putEdge(int a, int b, float c);
    void print();
    Graph primMST();
    int DFS(int current, std::map<int, int> *visited, int cun);


    void sometest(std::vector<int> *vv, int cun);
};


#endif
