#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include "graph.hpp"
#include "graph_utils.hpp"
#include "graph_traversals.hpp"

/** @brief Example of functional to process a node. */
template<class T>
struct NodeProcessor
{
    std::ostream& out;
    NodeProcessor(std::ostream& out_)
        : out(out_)
    {}

    bool apply(typename GraphNode<T>::Ref& node)
    {
        out << node->item() << ' ';
        if (out)
            return true;
        else
            return false;
    }
};



int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file (argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }
        auto g = create_wgraph<int>(input_file);
        if (!g)
        {
            std::cerr << "Error: could not load a valid wgraph." << std::endl;
            return EXIT_FAILURE;
        }
        int start_node;
        input_file >> start_node;
        NodeProcessor<int> p(std::cout);
        if (!g->find(start_node))
        {
            std::cerr << "Error: could not find the start node." << std::endl;
            return EXIT_FAILURE;
        }
        if (!depth_first_search(*g, p))
        {
            std::cerr << "Error: could not do a depth first search." << std::endl;
            return  EXIT_FAILURE;
        }
        std::cout << std::endl;
        //Re-start the graph.
        g->find(start_node);
        g->set_visited(false);
        if (!breadth_first_search(*g, p))
        {
            std::cerr << "Error: could wide traverse the graph." << std::endl;
            return  EXIT_FAILURE;
        }
        std::cout << std::endl;
    }
    catch(std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}

