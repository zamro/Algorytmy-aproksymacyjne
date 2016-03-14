#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

#include "graph.hpp"

/**
*   Kuba Kowalski
**/


int main()
{
    Graph G;
    /*G.putEdge(1,1, 2.1f);
    G.putEdge(1,2, 2.2f);
    G.putEdge(2,3, 2.3f);
    G.putEdge(4,2, 2.0f);
    G.putEdge(3,4, 2.2f);
    G.putEdge(4,1, 2.1f);
    G.putEdge(3,1, 2.4f);*/
    G.putEdge(1,2, 0.2);
    G.putEdge(3,2, 1.5);
    G.putEdge(1,9, 1.3);
    G.putEdge(1,7, 0.8);
    G.putEdge(9,3, 7.9);
    G.putEdge(4,3, 7.0);
    G.putEdge(4,7, 3.1);
    G.putEdge(4,5, 6.0);
    G.putEdge(5,10, 2.0);
    G.putEdge(9,10, 9.8);
    G.putEdge(6,7, 2.5);
    G.putEdge(8,7, 6.0);

    G.print();
    Graph mst = G.primMST();
    printf("\nMST!!\n");
    mst.print();

    std::map<int, int> dfs;
    mst.DFS(7, &dfs, 1);
    printf("\nDFS!!\n");
    printf("vertex\torder\n");
    for(std::map<int, int>::iterator pr=dfs.begin(); pr!=dfs.end(); pr++)
    {
        printf("%d\t%d\n", pr->first, pr->second);
    }
    printf("\n");
    //std::vector<int> vv;
    //G.sometest(&vv, 5);
    //while(!vv.empty()) {printf("%d\n", vv.back()); vv.pop_back();}
    return 0;
}
