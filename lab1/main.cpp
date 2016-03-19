#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

#include "graph.hpp"

/**
*   Kuba Kowalski
*   Paweł Gumny
**/

void test1()
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

    auto dfs = mst.DFS(7);
    printf("\nDFS!!\n");
    printf("vertex\torder\n");
    for(auto pr : dfs)
    {
        printf("%d\t%d\n", pr.first, pr.second);
    }
    printf("\n");

    std::cout<<"Odd subgraph"<<std::endl;
    G.subgraph(G.oddVertices()).print();
    std::cout<<"Odd subgraph of mst"<<std::endl;
    mst.subgraph(mst.oddVertices()).print();

    std::cout<<"Minimum cost matchng in odd subgraph"<<std::endl;
    G.subgraph(G.oddVertices()).minimumWeightedMatching().print();
}

//test in which graph is a fully connected unit square with points in corners and in the middle
void envelopeTest()
{
    std::cerr<<"-----\nenvelopeTest\n";
    Graph G;
    G.putEdge(1, 2, 1);
    G.putEdge(2, 3, 1);
    G.putEdge(3, 4, 1);
    G.putEdge(4, 1, 1);
    G.putEdge(1, 3, 1.41421356237);
    G.putEdge(2, 4, 1.41421356237);
    G.putEdge(1, 5, 1.41421356237/2);
    G.putEdge(2, 5, 1.41421356237/2);
    G.putEdge(3, 5, 1.41421356237/2);
    G.putEdge(4, 5, 1.41421356237/2);

    auto T = G.primMST();
    auto O = T.oddVertices();
    auto S = G.subgraph(O);
    auto M = S.minimumWeightedMatching();
    auto H = T.graphUnion(M);
    H.print();
    auto eulerianCycle = H.eulerianCycle();
    auto hamiltonianCycle = Graph::makeEulerianCycleHamiltonian(eulerianCycle);
    std::cerr<<"cykl Eulera"<<std::endl;
    for(int v:eulerianCycle)
        std::cerr<<v<<" ";
    std::cerr<<std::endl;
    std::cerr<<"cykl Hamiltona"<<std::endl;
    for(int v:hamiltonianCycle)
        std::cerr<<v<<" ";
    std::cerr<<std::endl;
}

//test in which graph is a fully connected unit square with points in corners and in the middle
void envelopeTest2()
{
    std::cerr<<"-----\nenvelopeTest2\n";
    Graph G;
    G.putEdge(1, 2, 1);
    G.putEdge(2, 3, 1);
    G.putEdge(3, 4, 1);
    G.putEdge(4, 1, 1);
    G.putEdge(1, 3, 1.41421356237);
    G.putEdge(2, 4, 1.41421356237);
    G.putEdge(1, 5, 1.41421356237/2);
    G.putEdge(2, 5, 1.41421356237/2);
    G.putEdge(3, 5, 1.41421356237/2);
    G.putEdge(4, 5, 1.41421356237/2);

    auto hamiltonianCycle = G.christofides();

    std::cerr<<"cykl Hamiltona"<<std::endl;
    for(int v:hamiltonianCycle)
        std::cerr<<v<<" ";
    std::cerr<<std::endl;
}


int main()
{
    envelopeTest();
    envelopeTest2();

    return 0;
}
