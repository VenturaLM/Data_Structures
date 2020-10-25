#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#include "graph.hpp"
#include "graph_utils.hpp"
#include "maze_solver.hpp"

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
        int grid_width, grid_height;
        input_file >> grid_width >> grid_height;
        if (!input_file)
        {
            std::cerr << "Error: could not read the grid shape." << std::endl;
            return EXIT_FAILURE;
        }
        auto maze = create_wgraph<int>(input_file);
        if (!maze)
        {
            std::cerr << "Error: could not load a valid wgraph." << std::endl;
            return EXIT_FAILURE;
        }
        int start_label , end_label;
        input_file >> start_label >> end_label;
        if (!input_file)
        {
            std::cerr << "Error: could not read the start and end vertices." << std::endl;
            return EXIT_FAILURE;
        }
        auto start = maze->find(start_label);
        if (!start)
        {
            std::cerr << "Error: do not found  the start vertex '"<< start_label <<"'." << std::endl;
            return EXIT_FAILURE;
        }
        auto end = maze->find(end_label);
        if (!end)
        {
            std::cerr << "Error: do not found the end vertex'"<< end_label <<"'." << std::endl;
            return EXIT_FAILURE;
        }
        std::vector<std::tuple<int, int>> path;
        maze_solver(*maze, start, end, grid_width, path);
        std::cout << "Path size: " << path.size() << std::endl;
        std::cout << "Path: ";
        for(size_t i=0;i<path.size();++i)
            std::cout << '[' << std::get<0>(path[i]) << ',' << std::get<1>(path[i]) << "] ";
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

