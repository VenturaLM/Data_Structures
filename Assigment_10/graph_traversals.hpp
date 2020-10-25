#ifndef __GRAPH_TRAVERSALS_HPP
#define __GRAPH_TRAVERSALS_HPP

#include <stack>
#include <queue>

#include "graph.hpp"

/**
 * @brief Depth first search from a vertex.
 * The current node will be used as start vertex.
 * @arg g is the graph.
 * @arg p is a functional to process the vertex.
 * @return the last p() return value.
 * @pre g.has_current_node()
 * @warning if p() return false, the search will be finished.
 * @warning only a spanning tree is searched.
 */
template<class T, class Processor>
bool depth_first_search(WGraph<T>& g, Processor& p)
{
    assert(g.has_current_node());
    bool ret_val = true;

    //TODO
    //Do an ITERATIVE implementation.
    typename GraphNode<T>::Ref u, v;
    std::stack<typename GraphNode<T>::Ref> mystack;
    mystack.push(g.current_node());

    while(!mystack.empty())
    {
    	u = mystack.top();
    	mystack.pop();

    	if(!u->is_visited())
    	{
    		u->set_visited(true);

    		if(!p.apply(u))
    		{
    			return false;
    		}

    		g.goto_node(u);

    		while(g.has_current_edge())
    		{
    			v = g.current_edge()->second();

    			if(!v->is_visited())
    			{
    				mystack.push(v);
    			}

    			g.goto_next_edge();
    		}
    	}
    }

    return ret_val;
}

/**
 * @brief breadth first search from a vertex.
 * The current node will be used as start node.
 * @arg g is the graph.
 * @arg p is a functional to process the vertex.
 * @return the last p() return value.
 * @pre g.has_current_node()
 * @warning if p() return false, the search will be finished.
 * @warning only a spanning tree is searched.
 */
template<class T, class Processor>
bool breadth_first_search(WGraph<T>& g, Processor& p)
{
    assert(g.has_current_node());
    bool ret_val = true;

    //TODO
    typename GraphNode<T>::Ref u, v;
    std::queue<typename GraphNode<T>::Ref> myqueue;
    myqueue.push(g.current_node());

    while(!myqueue.empty())
    {
    	u = myqueue.front();
    	myqueue.pop();

    	if(!u->is_visited())
    	{
    		u->set_visited(true);

    		if(!p.apply(u))
    		{
    			return false;
    		}

    		g.goto_node(u);

    		while(g.has_current_edge())
    		{
    			v = g.current_edge()->second();

    			if(!v->is_visited())
    			{
    				myqueue.push(v);
    			}

    			g.goto_next_edge();
    		}
    	}
    }

    return ret_val;
}

#endif // __GRAPH_TRAVERSALS_HPP
