#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 3);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(5, 4);
    g.addEdge(5, 7);
    g.addEdge(7, 6);
    //即使重复代码,也不会添加到图中
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 3);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(5, 4);
    g.addEdge(5, 7);
    g.addEdge(7, 6);
    cout << "Node Number: " << g.getNodeNum() << ", " << "Edge Number: " << g.getEdgeNum() << endl;
    g.topsortPrint();
    return 0;
}