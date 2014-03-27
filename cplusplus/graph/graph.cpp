// @file  graph.cpp
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#include "graph.h"
#include <algorithm>
#include <iterator>


namespace hl {

    using std::vector;
    using std::map;
    using std::set;
    using std::iterator;
    using std::string;

    int Vertex::in_degree() {
        return _in_edges.size();
    }

    int Vertex::out_degree() {
        return _out_edges.size();
    }

    Edge *Vertex::to_vertex(Vertex *v) {
        for (vector<Edge *>::iterator it = _out_edges.begin(); it != _out_edges.end(); ++it) {
            if ((*it)->_end_vertex == v) {
                return *it;
            }
        }

        return NULL;
    }

    Edge *Vertex::from_vertex(Vertex *v) {
        for (vector<Edge *>::iterator it = _in_edges.begin(); it != _in_edges.end(); ++it) {
            if ((*it)->_end_vertex == v) {
                return *it;
            }
        }

        return NULL;
    }


    Edge::Edge(Vertex *start_vertex, Vertex *to_vertex, uint32_t weight) {
        _start_vertex = start_vertex;
        _end_vertex   = to_vertex;
        _weight       = weight;
    }


    int Graph::addVertex(const string &key) {
        if (_vertexs.find(key) == _vertexs.end()) {
            return -1;
        }

        _vertexs[key] = new Vertex();

        return 0;
    }

    int Graph::addEdge(const string &from, const string &to, uint32_t weight) {
        if (_vertexs.find(from) == _vertexs.end() || _vertexs.find(to) == _vertexs.end()) {
            return -1;
        }

        Edge *edge = _vertexs[from]->to_vertex(_vertexs[to]);
        if (edge != NULL) {
            edge->_weight = weight;
        } else {
            _edges.insert(new Edge(_vertexs[from], _vertexs[to], weight));
        }

        return 0;
    }


    Graph::~Graph() {
        for (map<string, Vertex *>::iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
            delete it->second;
        }
        for (set<Edge *>::iterator it = _edges.begin(); it != _edges.end(); ++it) {
            delete *it;
        }
    }

}   // hl
