#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include "graph.hpp"
#include "graph_utils.hpp"
#include "city.hpp"

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
        if (!input_file)
        {
            std::cerr << "Error: could not read the type of the vertex's item." << std::endl;
            return EXIT_FAILURE;
        }
        if (type == "INTEGER")
        {
            auto g = create_wgraph<int>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for integers." << std::endl;
                return EXIT_FAILURE;
            }
            if (!fold_wgraph(std::cout, *g))
            {
                std::cerr << "Error: could not save the graph." << std::endl;
                return  EXIT_FAILURE;
            }

        }
        else if (type == "STRING")
        {
            auto g = create_wgraph<std::string>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for strings." << std::endl;
                return EXIT_FAILURE;
            }
            if (!fold_wgraph(std::cout, *g))
            {
                std::cerr << "Error: could not save the graph." << std::endl;
                return  EXIT_FAILURE;
            }
        }
        else if (type == "CITY")
        {
            auto g = create_wgraph<City>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for cities." << std::endl;
                return EXIT_FAILURE;
            }
            if (!fold_wgraph(std::cout, *g))
            {
                std::cerr << "Error: could not save the graph." << std::endl;
                return  EXIT_FAILURE;
            }
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

