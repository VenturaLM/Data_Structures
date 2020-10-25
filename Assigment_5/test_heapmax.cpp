#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include "heap.hpp"

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

        std::string command;
        Heap<int, std::greater_equal<int> > heap(100);

        while (input_file >> command)
        {
            if (command == "is_empty")
            {
                std::cout << (heap.is_empty() ? "empty" : "not empty") << std::endl;
            }
            else if (command == "is_full")
            {
                std::cout << (heap.is_full() ? "full" : "not full") << std::endl;
            }
            else if (command == "size")
            {
                std::cout << "size = " << heap.size() << std::endl;
            }
            else if (command == "capacity")
            {
                std::cout << "capacity = " << heap.capacity() << std::endl;
            }
            else if (command == "top")
            {
                std::cout << "top = " << heap.top() << std::endl;
            }
            else if (command == "insert")
            {
                int value;
                input_file >> value;
                input_file.ignore(); //flush the newline.
                heap.insert(value);
            }
            else if (command == "remove")
            {
                heap.remove();
            }
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

