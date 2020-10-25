#ifndef __GRAPH_UTILS_HPP__
#define __GRAPH_UTILS_HPP__

#include <iostream>
#include <memory>
#include <string>

#include "graph.hpp"

/**
 * @brief unfold a weighted graph from an input stream.
 * Input format:
 * <capacity>
 * <Nodes>
 * <node item_0>
 * ...
 * <node item_N-1>
 * <Edges>
 * <u_0> <v_0> <weight_0>
 * ...
 * <u_E-1> <v_E-1> <weight_E-1>
 */
template <class T>
bool
unfold_wgraph(std::istream& in, WGraph<T>& g)
{
    size_t capacity;
    in >> capacity;
    if (!in)
        return false;

    g = WGraph<T>(capacity);

    size_t n_nodes;
    in >> n_nodes;
    if (!in)
        return false;

    for(size_t n=0; n<n_nodes; ++n)
    {
        T item;
        in >> item;
        if (!in)
            return false;
        g.add_node(item);
    }
    size_t n_edges;
    in >> n_edges;
    for (size_t e=0;e<n_edges; ++e)
    {
        size_t u, v;
        float w;
        in >> u >> v >> w;
        if (!in || u>=n_nodes || v>=n_nodes)
            return false;
        g.set_weight(g.node(u), g.node(v), w);
    }
    return true;
}

/**
 * @brief Fold a weighted graph to an output stream.
 * Input format:
 * <capacity>
 * <Nodes>
 * <node item_0>
 * ...
 * <node item_N-1>
 * <Edges>
 * <u_0> <v_0> <weight_0>
 * ...
 * <u_E-1> <v_E-1> <weight_E-1>
 */
template <class T>
bool
fold_wgraph(std::ostream& out, WGraph<T> & g)
{
    out << g.capacity() << std::endl;
    out << g.size() << std::endl;
    for (size_t n=0;n<g.size();++n)
        out << g.node(n)->item() << std::endl;
    std::vector< typename WGraph<T>::EdgeRef > edges;
    g.goto_first_node();
    while(g.has_current_node())
    {
        g.goto_first_edge();
        while(g.has_current_edge())
        {
            edges.push_back(g.current_edge());
            g.goto_next_edge();
        }
        g.goto_next_node();
    }
    out << edges.size() << std::endl;
    for(size_t e=0;e<edges.size();++e)
        out << edges[e]->first()->label() << ' '
            << edges[e]->second()->label() << ' '
            << edges[e]->item() << std::endl;
    if (out)
        return true;
    else
        return false;
}

/**
 * @brief Create a Graph from txt representation.
 * If the graph is non directed, only one input u-v edge is needed but
 * it will be duplicated as u->v and v->u.
 *
 * Input Format:
 *
 * [DIRECTED|NON_DIRECTED]
 * <NUM-VERTICES>
 * <ITEM_1>
 * <ITEM_2>
 * ...
 * <ITEM_N>
 * <NUM-EDGES>
 * <ITEM_U> <ITEM_V> <WEIGTH>
 * ...
 *
 * @arg[in,out] in is the input stream.
 * @return a reference to the graph or nullptr if input error.
 * @warning std::runtime_error("Wrong graph") is throw if bad input format.
 */
template<class T>
std::shared_ptr<WGraph<T>> create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);    
    std::shared_ptr<WGraph<T>> graph;

    //TODO
    //Renember if the graph is non directed, each edge u--v generate two
    //directed edges u-->v and v-->u.
    //If the input format is wrong, the throw std::runtime_error("Wrong graph").
    std::string graph_type;
    bool directed_graph;
    int weight;
    size_t nodes, edges;
    T x, y, graph_type2;

//------------------------------------
    in >> graph_type;

    if(graph_type == "DIRECTED")
    {
        directed_graph = true;
    }else if(graph_type == "NON_DIRECTED"){
        directed_graph = false;
    }
//------------------------------------
    in >> nodes;

    if(!in)
    {
        return nullptr;
    }

    graph = std::make_shared<WGraph<T>>(nodes);

    for (size_t i = 0; i < nodes; i++)
    {
        in >> graph_type2;

        if(in)
        {
            graph->add_node(graph_type2);
        }else{
            return nullptr;
        }
    }
//------------------------------------
    in >> edges;

    if(!in)
    {
        return nullptr;
    }

    for (size_t i = 0; i < edges; i++)
    {
        in >> x;
        in >> y;
        in >> weight;

        if(!in)
        {
            return nullptr;
        }

        auto node_x = graph->find(x);
        if(!node_x)
        {
            throw std::runtime_error("Wrong graph");
        }

        auto node_y = graph->find(y);
        if(!node_y)
        {
            throw std::runtime_error("Wrong graph");
        }

        if(directed_graph == true)
        {
            //Grafo dirigido.
            graph->set_weight(node_x, node_y, weight);
        }else{
            //Grafo no dirigido: se duplica según las instrucciones.
            graph->set_weight(node_x, node_y, weight);
            graph->set_weight(node_y, node_x, weight);
        }
    }

    return graph;
}

#endif //__GRAPH_UTILS_HPP__
