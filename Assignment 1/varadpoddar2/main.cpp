#include <iostream>

#include "Graph.h"

int main()
{
    Graph graph;
    const Graph::LowestCostResult result = graph.find_lowest_cost_paths();

    if (result.paths.empty())
    {
        std::cout << "No path found from "
                  << graph.get_start()->get_name()
                  << " to "
                  << graph.get_destination()->get_name()
                  << ".\n";
        return 0;
    }

    std::cout << "Lowest cost: " << result.cost << '\n';
    for (const auto &path : result.paths)
    {
        std::cout << Graph::format_path(path) << '\n';
    }

    return 0;
}
