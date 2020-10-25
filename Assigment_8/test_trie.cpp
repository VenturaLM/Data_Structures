#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <string>

#include "trie.hpp"


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
        size_t num_claves;
        input_file >> num_claves;
        input_file.ignore(); //clean the newline.
        if (!input_file)
        {
            std::cerr << "Error: worng input format." << std::endl;
            return  EXIT_FAILURE;
        }
        Trie trie;
        for (size_t i=0;i<num_claves && input_file;++i)
        {
            std::string key;
            std::getline(input_file, key);
            trie.insert(key);
        }
        if (!input_file)
        {
            std::cerr << "Error: worng input format." << std::endl;
            return  EXIT_FAILURE;
        }
        std::string command;
        while(input_file >> command)
        {
            if (command=="has")
            {
                std::string key;
                input_file.ignore(); //remove blank.
                std::getline(input_file, key);
                if (!input_file)
                {
                    std::cerr << "Error: worng input format." << std::endl;
                    return  EXIT_FAILURE;
                }
                std::cout << "Has '" << key << "' key?: " << (trie.find(key) ? "yes." : "no.") << std::endl;
            }
            else if (command == "keys")
            {
                std::string prefix;
                input_file >> prefix;
                if (!input_file)
                {
                    std::cerr << "Error: worng input format." << std::endl;
                    return  EXIT_FAILURE;
                }
                std::cout << "Keys with prefix '" << prefix << "' :";
                std::vector<std::string> keys = trie.keys(prefix);
                for(size_t i=0;i<keys.size();++i)
                    std::cout << " '" << keys[i] << "'";
                std::cout << std::endl;
            }
            else
            {
                std::cerr << "Error: command unknown '"<< command << "'." << std::endl;
                return EXIT_FAILURE;
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

