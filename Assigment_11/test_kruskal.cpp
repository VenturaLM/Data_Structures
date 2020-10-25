#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include "city.hpp"
#include "graph.hpp"
#include "kruskal_algorithm.hpp"

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
        std::string type;
        input_file >> type;
        input_file.ignore();
        if (type=="INTEGER")
        {
            auto g = create_wgraph<int>(input_file);
            if (! g)
            {
                std::cerr << "Error: could not load a valid wgraph for integers." << std::endl;
                return EXIT_FAILURE;
            }
            std::vector<WGraph<int>::EdgeRef> minium_spanning_tree;
            float total_weight = kruskal_algorithm(*g, minium_spanning_tree);
            std::cout << "Minimum Spanning tree: ";
            for (size_t i=0; i<minium_spanning_tree.size(); ++i)
                std::cout << '[' << minium_spanning_tree[i]->first()->item() << ','
                          << minium_spanning_tree[i]->second()->item() << "] ";
            std::cout << std::endl;
            std::cout << "Total weight: " << total_weight << std::endl;
        }
        else if(type=="CITY")
        {
            auto g = create_wgraph<City>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for cities." << std::endl;
                return EXIT_FAILURE;
            }
            std::vector<WGraph<City>::EdgeRef> minium_spanning_tree;
            float total_weight = kruskal_algorithm(*g, minium_spanning_tree);
            std::cout << "Minimum Spanning tree: ";
            for (size_t i=0; i<minium_spanning_tree.size(); ++i)
                std::cout << '[' << minium_spanning_tree[i]->first()->item().name << ','
                          << minium_spanning_tree[i]->second()->item().name << "] ";
            std::cout << std::endl;
            std::cout << "Total weight: " << total_weight << std::endl;
        }
        else
        {
            std::cerr << "Error: unknown graph type." << std::endl;
            return EXIT_FAILURE;
        }
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

