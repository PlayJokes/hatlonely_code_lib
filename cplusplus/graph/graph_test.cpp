// @file  graph_test.cpp
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#include <gtest/gtest.h>
#include <iostream>
#include "graph.h"

using namespace std;
using namespace hl;

void travel_vertex(Vertex *vertex) {
    cout << vertex->toString() << endl;
}

void travel_edge(Edge *edge) {
    cout << edge->toString() << endl;
}

int main() {
    Graph g;
    g.add_vertex("v1");
    g.add_vertex("v2");
    g.del_vertex("v2");
    string a[] = {"v3", "v4"};
    g.addVertexs(a, a + sizeof(a) / sizeof(a[1]));
    g.add_edge("v1", "v2", 3);
    g.add_edge("v1", "v3", 3);
    g.add_edge("v2", "v4", 3);
    g.add_edge("v1", "v5", 3);
    g.del_edge("v1", "v3");
    /* g.for_each_vertex(travel_vertex); */
    /* g.for_each_edge(travel_edge); */
    cout << g.toString();
    EXPECT_EQ(4, 2);
}
