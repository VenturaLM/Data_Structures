#include <cmath>
#include "city.hpp"

/** @brief convert from degrees to radians. */
inline static
double
to_rad(const double a)
{
    return M_PI/180.0 * a;
}

double
distance(const City& s, const City& d)
{
    const double EARTH_RADIX = 6378.0; //Km.
    const double dif_latitude = to_rad(d.latitude - s.latitude);
    const double dif_longitude = to_rad(d.longitude - s.longitude);

    const double a = std::pow(std::sin(dif_latitude/2.0), 2.0) +
              std::cos(to_rad(s.latitude))*
              std::cos(to_rad(d.latitude))*
              std::pow(std::sin(dif_longitude/2.0),2.0);
    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0-a));
    return c*EARTH_RADIX;
}

/**
 * @brief unfold a city from an input stream.
 */
std::istream&
operator>>(std::istream& in, City& c)
{
    in >> c.name >> c.latitude >> c.longitude;
    return in;
}

/**
 * @brief fold a City to an output stream.
 */
std::ostream&
operator<<(std::ostream& out, City const& c)
{
    out << c.name << ' ' << c.latitude << ' ' << c.longitude;
    return out;
}

/**
 * @brief Template specialization for City.
 */
template<>
std::shared_ptr<WGraph<City>> create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    std::shared_ptr<WGraph<City>> graph;

    //TODO
    //Remenber: to save space, for the edges it is only used the name of de
    //city and not the whole city data.
    double latitude, longitude, distance;
    std::string graph_type, name, x, y;
    bool directed_graph;
    size_t nodes, edges;

//------------------------------------
    in >> graph_type;

    if(graph_type == "DIRECTED")
    {
        directed_graph = true;
    }else if(graph_type == "NON_DIRECTED"){
        directed_graph = false;
    }
//------------------------------------
    in >> nodes;

    if(!in)
    {
        return nullptr;
    }

    graph = std::make_shared<WGraph<City>>(nodes);

    for (size_t i = 0; i < nodes; i++)
    {
        in >> name;
        in >> latitude;
        in >> longitude;

        City node_(name, latitude, longitude);

        if(in)
        {
            graph->add_node(node_);
        }else{
            return nullptr;
        }
    }
//------------------------------------
    in >> edges;

    if(!in)
    {
        return nullptr;
    }

    for (size_t i = 0; i < edges; i++)
    {
        in >> x;
        in >> y;
        in >> distance;

        if(!in)
        {
            return nullptr;
        }

        auto node_x = graph->find(x);
        if(!node_x)
        {
            throw std::runtime_error("Wrong graph");
        }

        auto node_y = graph->find(y);
        if(!node_y)
        {
            throw std::runtime_error("Wrong graph");
        }

        if(directed_graph == true)
        {
        	//Grafo dirigido.
            graph->set_weight(node_x, node_y, distance);
        }else{
        	//Grafo no dirigido: se duplica según las instrucciones.
            graph->set_weight(node_x, node_y, distance);
            graph->set_weight(node_y, node_x, distance);
        }
    }

    return graph;
}

