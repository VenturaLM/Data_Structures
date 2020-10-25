#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

#include "btree.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: test_tree filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file (argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            std::cerr << "Usage: test_tree filename" << std::endl;
            return EXIT_FAILURE;
        }

        BTree<int> tree;
        unfold_btree(input_file, tree);

        if (!input_file)
        {
            std::cerr << "Error: wrong input format." << std::endl;
            return EXIT_FAILURE;
        }

        fold_btree(std::cout, tree);
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

