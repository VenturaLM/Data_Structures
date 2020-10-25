#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "stack.hpp"

class Bracket
{
public:
    Bracket(char c, size_t pos )
        : _c(c), _pos(pos)
    {
    }

    bool match_with(char o) const
    {
        return ( (_c == '{' && o== '}') ||
                 (_c == '[' && o== ']') ||
                 (_c == '(' && o== ')'));
    }
    size_t pos() const
    {
        return _pos;
    }
protected:
    char _c;
    size_t _pos;
};

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

        Stack<int> stack;

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
                    stack.push(value);
                } else if (operation == 1)
                {
                    stack.pop();
                } else if (operation == 2)
                {
                    std::cout << stack.top() << std::endl;
                } else
                {
                    std::cout << (stack.is_empty() ? "empty" : "not empty") << std::endl;
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

