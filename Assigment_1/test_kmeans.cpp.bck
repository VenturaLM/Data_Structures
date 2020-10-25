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
            std::cerr << "Usage: test_kmeans dataset" << std::endl;
            return EXIT_FAILURE;
        }

        size_t K = 4;
        std::string filename = argv[1];
        srand(0);

        /*The dataset of patterns.*/
        std::vector<Pattern> dts;
        std::ifstream input(filename);
        load_dataset(input, dts);

        std::vector<Pattern> gt_centroids(4, Pattern(2, -1));
        float data [][4] = { {0.0, 0.0},
                             {0.0, 1.0},
                             {1.0, 0.0},
                             {1.0, 1.0}};

        for (size_t i=0;i<4; ++i)
            gt_centroids[i].set_values(data[i]);

        std::vector<Pattern> computed_centroids;
        size_t iterations = kmeans(dts, K, 1000, computed_centroids);
        //Test the result.
        bool found = false;
        for (size_t i=0; i<gt_centroids.size(); i++)
        {
            found = false;
            for(size_t j=0; j<computed_centroids.size() && !found; j++)
                if (distance(gt_centroids[i], computed_centroids[j]) < 0.1)
                    found = true;
            if (!found)
            {
                std::cout << "Ground truth centroid: " << gt_centroids[i] << " not found.!";
                std::cout << "Your centroids are: " << std::endl;
                for (size_t i = 0; i<computed_centroids.size(); ++i)
                    std::cout << computed_centroids[i];
            }
        }
        if (found)
            std::cout << "Success." << std::endl;
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
