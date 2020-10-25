#include "a_star_algorithm.hpp"
#include "maze_solver.hpp"

#include <stack>
#include <cmath>

/**
 * @brief Convert from vertex label to x,y coordinates.
 * @param v is the vertex label.
 * @param grid_width is the width of the grid.
 * @return a tuple <x,y>.
 */
static inline std::tuple<int, int>
label_to_grid_coord(size_t v, int grid_width)
{
    //TODO
    return std::make_tuple(0, 0);
}

/**
 * @brief Functional to compute the euclidean distance between graph vertices.
 */
struct Distance
{
    Distance(/* arguments? */)
    {
        //TODO
    }

    float operator()(const WGraph<int>::NodeRef& a,
                     const WGraph<int>::NodeRef& b) const
    {
        //TODO
        return 0.0f;
    }
};

void
maze_solver(WGraph<int>& maze,
            WGraph<int>::NodeRef& start,
            WGraph<int>::NodeRef& end,
            const int grid_width,
            std::vector<std::tuple<int, int> > &path)
{
    std::vector<size_t> predecesors;
    std::vector<float> distances;

    //TODO
    //Call to a*  with the proper arguments.


    //
    path.resize(0);

    if (false /*replace with a comparison to see if a route was found.*/)
    {
        //If there is a path, save it into path vector.
        //Remenber: the result will be tuples <x,y> for the all the points in the path from start point to end point.

        //TODO
    }
}
