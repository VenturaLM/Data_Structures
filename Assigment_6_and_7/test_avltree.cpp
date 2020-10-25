#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "avltree.hpp"

std::istream&
operator>>(std::istream& in, std::vector<int>& v)
{
    size_t size;
    in >> size;
    if (in)
    {
        v.resize(size);
        for (size_t i=0;i<size && in; ++i)
            in >> v[i];
    }
    return in;
}

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
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }

        std::vector<int> insert_values;
        input_file >> insert_values;
        if (!input_file)
        {
            std::cerr << "Error: wrong input format." << std::endl;
            return EXIT_FAILURE;
        }

        std::vector<int> remove_values;
        input_file >> remove_values;
        if (!input_file)
        {
            std::cerr << "Error: wrong input format." << std::endl;
            return EXIT_FAILURE;
        }

        AVLTree<int> tree;

        for (size_t i=0; i<insert_values.size(); i++)
            tree.insert(insert_values[i]);

        for (size_t i=0; i<remove_values.size(); i++)
        {
            assert(tree.search(remove_values[i]));
            tree.remove();
        }
        std::cout << tree << std::endl;
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

