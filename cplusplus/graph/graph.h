// @file  graph.h
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#include <vector>
#include <set>
#include <string>

class Vertex;
class Edge;
class Graph;

class Vertex {
public:
    inline int in_degree();
    inline int out_degree();
    inline Edge *to_vertex(const Vertex &v);
    inline Edge *from_vertex(const Vertex &v);
private:
    vector<Edge *> _in_edges;
    vector<Edge *> _out_edges;

    friend class Graph;
    friend class Edge;
}

class Edge {
public:
    Edge(const Vertex &start_vertex, const Vertex &to_vertex, uint32_t weight);
private:
    Vertex *_start_vertex;
    Vertex *_end_vertex;
    uint32_t _weight;

    friend class Graph;
    friend class Vertex;
}

class Graph {
public:
    ~Graph();
    int addVertex(const string &key);
    int addEdge(const string &from, const string &to, uint32_t weight);
private:
    map<string, Vertex> vertexs;
    set<Edge> edges;
}




















