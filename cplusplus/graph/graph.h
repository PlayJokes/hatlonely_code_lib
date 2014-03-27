// @file  graph.h
// @desc  图论
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <set>
#include <string>
#include <map>
#include <iterator>
#include <iostream>


namespace hl {

    class Vertex;
    class Edge;
    class Graph;

    class Vertex {
        public:
            Vertex(const std::string &desc);
            inline int in_degree();
            inline int out_degree();
            inline Edge *to_vertex(Vertex *v);
            inline Edge *from_vertex(Vertex *v);
            inline const std::string &get_desc();
            std::string toString();
        private:
            std::set<Edge *> _in_edges;
            std::set<Edge *> _out_edges;
            std::string _desc;
            bool _is_marked;

            friend class Graph;
            friend class Edge;
    };

    class Edge {
        public:
            Edge(Vertex *from_vertex, Vertex *to_vertex, uint32_t weight);
            inline const Vertex *get_from_vertex();
            inline const Vertex *get_to_vertex();
            std::string toString();
        private:
            Vertex *_from_vertex;
            Vertex *_to_vertex;
            uint32_t _weight;

            friend class Graph;
            friend class Vertex;
    };

    class Graph {
        public:
            ~Graph();
            void add_vertex(const std::string &key);
            void add_edge(const std::string &from, const std::string &to, uint32_t weight);
            void del_vertex(const std::string &from);
            void del_edge(const std::string &from, const std::string &to);
            void for_each_vertex(void (* callback)(Vertex *));
            void for_each_edge(void (* callback)(Edge *));
            void for_each_vertex_dfs(void (* callback)(Vertex *));
            void for_each_vertex_bfs(void (* callback)(Vertex *));
            std::string toString();
            template <typename Iterator> void addVertexs(Iterator begin, Iterator end) {
                for (Iterator it = begin; it != end; ++it) {
                    add_vertex(*it);
                }
            }
        private:
            Edge *_find_edge(const std::string &from, const std::string &to);
            void _clear_mark();

            std::map<std::string, Vertex *> _vertexs;
            std::set<Edge *> _edges;
    };

}   // hl

#endif
