#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include "heap.hpp"
#include "heapsort.hpp"

/** @brief Load a vector of items from input stream.
 * input format:
 * <size> <item0> ... <item_size-1>
 */
template<class T>
std::istream&
load_vector(std::istream& in, std::vector<T>& data)
{
    size_t size;
    in >> size;
    if (in)
    {
        data.resize(size);
        for (size_t i=0; i<size && in; ++i)
            in >> data[i];
    }
    return in;
}

bool is_sorted(std::vector<int> const& data)
{
    bool is_sorted = false;
    if (data.size()>2)
    {
        auto first = data.begin();
        auto second = data.begin()+1;
        while (second != data.end() && (*first <= *second))
        {
            first++;
            second++;
        }
        is_sorted = second==data.end();
    }
    return is_sorted;
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
            return EXIT_FAILURE;
        }

        std::vector<int> values;
        load_vector(input_file,values);
        if (!input_file)
        {
            std::cerr << "Error: could not read the data from filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }


        heapsort(values, std::greater_equal<int>());

        if (is_sorted(values))
            std::cout << "Success." << std::endl;
        else
            return EXIT_FAILURE;
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

