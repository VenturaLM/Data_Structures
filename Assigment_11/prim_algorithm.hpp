#ifndef __FLOYD_ALGORITHM_HPP__
#define __FLOYD_ALGORITHM_HPP__

#include <exception>
#include <limits>
#include <memory>
#include <valarray>
#include <vector>

#include "graph.hpp"

/**
 * @brief Apply the Prim algorithm to a undirected connected graph to get the minimum spannig tree.
 * The current node of g is used as root.
 * @arg[in] g is the graph.
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weigth of the mininum spanning tree.
 * @pre g is an undirected connected graph.
 * @pre g.hash_current()
 * @warning throw std:runtine_error("It is a non-connected graph.") if a solution could not be computed.
 */
template <class T>
float
prim_algorithm(WGraph<T>& g, std::vector<typename WGraph<T>::EdgeRef>& mst) noexcept(false)
{
    assert(g.has_current_node());

    //TODO: Declare the U, V and C vectors according to the algorithm (see class documentation.)
    std::vector<bool> U(g.size(), 0);
    std::vector<typename GraphNode<T>::Ref> V(g.size());
    std::vector<float> C(g.size(), std::numeric_limits<float>::infinity());

    float total_distance = 0.0;
    auto u = g.current_node();

    //TODO: Add the start node to the Minimum Spanning Tree (mst).
    C[u->label()] = std::numeric_limits<float>::infinity();
    U[u->label()] = true;

    //ITERATE FOR the N-1 edges.
    for (size_t i=1; i<g.size(); ++i)
    {
        //TODO: Update vector of best distances regarding the last vertex added u to the mst.
        for (size_t j = 0; j < g.size(); j++)
        {
            u = g.current_node();

            if(C[j] > g.weight(u, g.node(j)) && (U[j] == false))
            {
                C[j] = g.weight(u, g.node(j));
                V[j] = u;
            }
        }

        //TODO: Find the next vertex to be added to the mst.
        //Remeber: if a tie exists, select the vertex with lesser label.
        //You can use std::numeric_limits<float>::infinity() if it is necessary.
        float lesser_label_vertex = C[0];
        bool found = false;

        for (size_t it = 1; it < C.size(); it++)
        {
            if(lesser_label_vertex > C[it])
            {
                lesser_label_vertex = C[it];
            }
        }

        size_t it;
        for (it = 0; !found && it < C.size(); /*empty_condition*/)
        {
            if(C[it] == lesser_label_vertex)
            {
                found = true;
            }else{
                it++;
            }
        }

        //TODO: check if a valid condition is met for a connected graph.
        //Suggestion: What about the minimum distance found?
        if (C[it] == std::numeric_limits<float>::infinity())
            throw std::runtime_error("It is a non-connected graph.");

        //TODO:Set vertex found as beloning to the mst.
        //  Guardar el coste.
        float spanning = C[it];
        U[it] = true;
        C[it] = std::numeric_limits<float>::infinity();
        g.goto_node(g.node(it));

        //TODO:Add the edge found to the mst vector.
        mst.push_back(g.edge(g.node(it), V[it]));

        //TODO: update the total distance of the mst with the new edge's weight.
        total_distance = total_distance + spanning;
    }

    return total_distance;
}

#endif //__FLOYD_ALGORITHM_HPP__