#ifndef GRAPH_H_
#define GRAPH_H_

#include <limits>
#include <string>
#include <vector>

#include "Island.h"
#include "Bridge.h"

class Graph
{
private:
    Island is1, is2, is3, is4, is5, is6, is7, is8;

    Bridge br12, br13, br14;
    Bridge br24, br25;
    Bridge br36;
    Bridge br43, br45, br46, br47;
    Bridge br68;
    Bridge br75, br76, br78;

    // Recursively explore all outgoing bridges from an island.
    void find_lowest_cost_paths_rec(
        const Island *current,
        const Island *destination,
        std::vector<const Island *> &current_path,
        int current_cost,
        int &best_cost,
        std::vector<std::vector<const Island *>> &best_paths) const
    {
        // Base case: reached destination; update best paths/cost.
        if (current == destination)
        {
            if (current_cost < best_cost)
            {
                best_cost = current_cost;
                best_paths.clear();
            }
            if (current_cost == best_cost)
            {
                best_paths.push_back(current_path);
            }
            return;
        }

        // Simpler recursive case: try each outgoing bridge.
        for (const Bridge *bridge : current->get_bridges())
        {
            const int next_cost = current_cost + bridge->get_toll();
            if (next_cost > best_cost)
            {
                continue;
            }

            const Island *next_island = bridge->get_endpoint();
            current_path.push_back(next_island);
            find_lowest_cost_paths_rec(
                next_island, destination, current_path, next_cost, best_cost, best_paths);
            current_path.pop_back();  // backtrack to try the next bridge.
        }
    }

public:
    struct LowestCostResult
    {
        int cost;
        std::vector<std::vector<const Island *>> paths;
    };

    /**
     * Constructor: Build the graph of islands and bridges.
     */
    Graph() : is1(Island("Island 1")),
              is2(Island("Island 2")),
              is3(Island("Island 3")),
              is4(Island("Island 4")),
              is5(Island("Island 5")),
              is6(Island("Island 6")),
              is7(Island("Island 7")),
              is8(Island("Island 8")),

              br12(Bridge(&is2, 2)),
              br13(Bridge(&is3, 3)),
              br14(Bridge(&is4, 2)),

              br24(Bridge(&is4, 3)),
              br25(Bridge(&is5, 1)),

              br36(Bridge(&is6, 3)),

              br43(Bridge(&is3, 3)),
              br45(Bridge(&is5, 2)),
              br46(Bridge(&is6, 4)),
              br47(Bridge(&is7, 3)),

              br68(Bridge(&is8, 2)),

              br75(Bridge(&is5, 3)),
              br76(Bridge(&is6, 1)),
              br78(Bridge(&is8, 4))
    {
        is1.set_bridges(std::vector<const Bridge *> { &br12, &br13, &br14 });
        is2.set_bridges(std::vector<const Bridge *> { &br24, &br25 });
        is3.set_bridges(std::vector<const Bridge *> { &br36 });
        is4.set_bridges(std::vector<const Bridge *> { &br43, &br45, &br46, &br47 });
        is6.set_bridges(std::vector<const Bridge *> { &br68 });
        is7.set_bridges(std::vector<const Bridge *> { &br75, &br76, &br78 });
    }

    const Island *get_start() const { return &is1; }
    const Island *get_destination() const { return &is6; }

    LowestCostResult find_lowest_cost_paths() const
    {
        std::vector<const Island *> current_path { get_start() };
        std::vector<std::vector<const Island *>> best_paths;
        int best_cost = std::numeric_limits<int>::max();

        find_lowest_cost_paths_rec(
            get_start(), get_destination(), current_path, 0, best_cost, best_paths);

        return LowestCostResult { best_cost, best_paths };
    }

    static std::string format_path(const std::vector<const Island *> &path)
    {
        std::string formatted;
        for (size_t i = 0; i < path.size(); ++i)
        {
            if (i > 0)
            {
                formatted += " -> ";
            }
            formatted += path[i]->get_name();
        }
        return formatted;
    }
};



#endif /* GRAPH_H_ */
