// @file  graph.cpp
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#include "graph.h"
#include <algorithm>
#include <iterator>
#include <sstream>


namespace hl {

    using std::map;
    using std::set;
    using std::iterator;
    using std::string;
    using std::ostringstream;
    using std::endl;

    // class Vertex
    Vertex::Vertex(const string &desc): _desc(desc) {
        _is_marked = false;
    }

    int Vertex::in_degree() {
        return _in_edges.size();
    }

    int Vertex::out_degree() {
        return _out_edges.size();
    }

    const string &Vertex::get_desc() {
        return _desc;
    }

    Edge *Vertex::to_vertex(Vertex *v) {
        for (set<Edge *>::iterator it = _out_edges.begin(); it != _out_edges.end(); ++it) {
            if ((*it)->_to_vertex == v) {
                return *it;
            }
        }

        return NULL;
    }

    Edge *Vertex::from_vertex(Vertex *v) {
        for (set<Edge *>::iterator it = _in_edges.begin(); it != _in_edges.end(); ++it) {
            if ((*it)->_to_vertex == v) {
                return *it;
            }
        }

        return NULL;
    }

    string Vertex::toString() {
        return _desc;
    }

    // class Edge
    Edge::Edge(Vertex *from_vertex, Vertex *to_vertex, uint32_t weight) {
        _from_vertex = from_vertex;
        _to_vertex = to_vertex;
        _weight = weight;
    }

    const Vertex *Edge::get_from_vertex() {
        return _from_vertex;
    }

    const Vertex *Edge::get_to_vertex() {
        return _to_vertex;
    }

    string Edge::toString() {
        ostringstream oss;
        oss << _from_vertex->_desc << "->" << _to_vertex->_desc << ": " << _weight;
        return oss.str();
    }

    // class Graph
    void Graph::add_vertex(const string &key) {
        if (_vertexs.find(key) != _vertexs.end()) {
            return;
        }

        _vertexs[key] = new Vertex(key);
    }

    void Graph::add_edge(const string &from, const string &to, uint32_t weight) {
        if (_vertexs.find(from) == _vertexs.end()) {
            _vertexs[from] = new Vertex(from);
        }
        if (_vertexs.find(to) == _vertexs.end()) {
            _vertexs[to] = new Vertex(to);
        }

        Edge *edge = _vertexs[from]->to_vertex(_vertexs[to]);
        if (edge != NULL) {
            edge->_weight = weight;
        } else {
            edge = new Edge(_vertexs[from], _vertexs[to], weight);
            _edges.insert(edge);
            _vertexs[from]->_out_edges.insert(edge);
            _vertexs[to]->_in_edges.insert(edge);
        }
    }

    void Graph::del_vertex(const std::string &desc) {
        set<Edge *> in_edges = _vertexs[desc]->_in_edges;
        set<Edge *> out_edges = _vertexs[desc]->_out_edges;

        for (set<Edge *>::iterator it = in_edges.begin(); it != in_edges.end(); ++it) {
            (*it)->_from_vertex->_out_edges.erase(*it);
            _edges.erase(*it);
            delete *it;
        }
        for (set<Edge *>::iterator it = out_edges.begin(); it != out_edges.end(); ++it) {
            (*it)->_to_vertex->_in_edges.erase(*it);
            _edges.erase(*it);
            delete *it;
        }
        delete _vertexs[desc];
        _vertexs.erase(desc);
    }

    void Graph::del_edge(const std::string &from, const std::string &to) {
       Edge *edge = _find_edge(from, to);
       _vertexs[from]->_out_edges.erase(edge);
       _vertexs[to]->_in_edges.erase(edge);
       _edges.erase(edge);
       delete edge;
    }

    void Graph::for_each_vertex(void (* callback)(Vertex *vertex)) {
        for (map<string, Vertex *>::iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
            callback(it->second);
        }
    }

    void Graph::for_each_edge(void (* callback)(Edge *edge)) {
        for (set<Edge *>::iterator it = _edges.begin(); it != _edges.end(); ++it) {
            callback(*it);
        }
    }

    void Graph::for_each_vertex_dfs(void (* callback)(Vertex *vertex)) {
        map<string, Vertex *>::iterator vertex_it = _vertexs.begin();
        for (; vertex_it != _vertexs.end(); ++vertex_it) {
            if (!vertex_it->second->_is_marked) {
                // TODO
            }
        }
    }

    void Graph::for_each_vertex_bfs(void (* callback)(Vertex *vertex)) {
        // TODO
    }

    string Graph::toString() {
        ostringstream oss;
        for (map<string, Vertex *>::iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
            oss << it->second->toString() << " ";
        }
        oss << endl;
        for (set<Edge *>::iterator it = _edges.begin(); it != _edges.end(); ++it) {
            oss << (*it)->toString() << endl;
        }

        return oss.str();
    }

    Graph::~Graph() {
        for (map<string, Vertex *>::iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
            delete it->second;
        }
        for (set<Edge *>::iterator it = _edges.begin(); it != _edges.end(); ++it) {
            delete *it;
        }
    }

    Edge *Graph::_find_edge(const std::string &from, const std::string &to) {
        set<Edge *> edges = _vertexs[from]->_out_edges;
        for (set<Edge *>::iterator it = edges.begin(); it != edges.end(); ++it) {
            if ((*it)->_to_vertex->_desc == to) {
                return *it;
            }
        }

        return NULL;
    }

    void Graph::_clear_mark() {
        for (map<string, Vertex *>::iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
            it->second->_is_marked = false;
        }
    }

}   // hl
