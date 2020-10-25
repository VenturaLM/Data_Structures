#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: test_stack test_case" << std::endl;
            return EXIT_FAILURE;
        }
        std::string filename = argv[1];

        std::ifstream input (argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }

        Queue<int> queue;

        while(input)
        {
            int operation;
            input >> operation;
            if (input)
            {
                if (operation==0)
                {
                    int value;
                    input >> value;
                    queue.enque(value);
                } else if (operation == 1)
                {
                    queue.deque();
                } else if (operation == 2)
                {
                    std::cout << queue.front() << std::endl;
                } else if (operation == 3)
                {
                    std::cout << (queue.is_empty() ? "empty" : "not empty") << std::endl;
                } else
                {
                    std::cout << queue.back() << std::endl;
                }
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
