#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "pattern.hpp"
#include "kmeans.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: test_pattern tests_case" << std::endl;
            return EXIT_FAILURE;
        }

        std::ifstream input (argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open file '"<<argv[1]<<"'."<<std::endl;
            return EXIT_FAILURE;
        }
        std::string operation;
        input >> operation;
        input.ignore();
        if (!input)
        {
            std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
            return EXIT_FAILURE;
        }
        if (operation=="max")
        {
            Pattern a;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << a.max() << std::endl;
        } else if (operation=="min")
        {
            Pattern a;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << a.min() << std::endl;
        } else if (operation=="sum")
        {
            Pattern a;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << a.sum() << std::endl;
        } else if (operation=="+")
        {
            Pattern a,b;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            input >> b;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << (a+b);
        } else if (operation=="-")
        {
            Pattern a,b;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            input >> b;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << (a-b);
        } else if (operation=="*")
        {
            Pattern a,b;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            input >> b;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << (a*b);
        } else if (operation=="dist")
        {
            Pattern a,b;
            input >> a;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            input >> b;
            if (!input)
            {
                std::cerr << "Error: wrong format in '"<<argv[1]<<"'."<<std::endl;
                return EXIT_FAILURE;
            }
            std::cout << distance(a,b) << std::endl;
        } else {
            std::cerr << "Error: operation unknown!." << std::endl;
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
