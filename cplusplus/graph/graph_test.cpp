// @file  graph_test.cpp
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#include <iostream>
#include "graph.h"

using namespace std;
using namespace hl;

int main() {
    Graph g;
    g.addVertex("v1");
    g.addVertex("v2");
    g.addEdge("v1", "v2", 3);
    string a[] = {"0", "1"};
    g.addVertexs(a, a+1);

    cout << "hello world" << endl;
}
