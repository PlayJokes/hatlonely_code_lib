// @file  graph.h
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <set>
#include <string>
#include <map>
#include <iterator>


namespace hl {

    class Vertex;
    class Edge;
    class Graph;

    class Vertex {
        public:
            inline int in_degree();
            inline int out_degree();
            inline Edge *to_vertex(Vertex *v);
            inline Edge *from_vertex(Vertex *v);
        private:
            std::vector<Edge *> _in_edges;
            std::vector<Edge *> _out_edges;

            friend class Graph;
            friend class Edge;
    };

    class Edge {
        public:
            Edge(Vertex *start_vertex, Vertex *to_vertex, uint32_t weight);
            /* private: */
            Vertex *_start_vertex;
            Vertex *_end_vertex;
            uint32_t _weight;

            friend class Graph;
            friend class Vertex;
    };

    class Graph {
        public:
            ~Graph();
            int addVertex(const std::string &key);
            template <typename Iterator> void addVertexs(Iterator begin, Iterator end) {
                for (Iterator it = begin; it != end; ++it) {
                    addVertex(*it);
                }
            }
            int addEdge(const std::string &from, const std::string &to, uint32_t weight);
            int for_each_vertex(void (*callback)(const string &, Vertex *));
        private:
            std::map<std::string, Vertex *> _vertexs;
            std::set<Edge *> _edges;
    };

}   // hl

#endif
