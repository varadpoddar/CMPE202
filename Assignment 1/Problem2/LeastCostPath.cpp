/**
 * Least Cost Path using Recursion and Backtracking
 *
 * This program finds all lowest-cost paths from Island 1 to Island 6
 * using a brute-force recursive approach with backtracking.
 *
 * Base cases:
 *   1. The current island IS the destination (Island 6).
 *      - A valid path has been found. Compare its cost to the best cost so far.
 *      - If the cost is lower, clear all previous best paths and save this one.
 *      - If the cost is equal, add this path as another tied best path.
 *
 *   2. The current island has NO outgoing bridges (dead end, e.g., Island 5 or 8).
 *      - There is nothing to explore, so the function simply returns.
 *      - This causes backtracking to the previous island to try other bridges.
 *
 * Recursive (simpler) case:
 *   - For each outgoing bridge from the current island, cross the bridge by:
 *     adding the next island to the path and adding the toll to the cost.
 *   - Then recursively search from that next island (a simpler case because
 *     we are one bridge closer to the destination or a dead end).
 *
 * Backtracking:
 *   - After the recursive call returns (whether it found a path or hit a dead end),
 *     remove the last island from the path (undo the step).
 *   - This allows the loop to continue and try the NEXT bridge from the same island.
 *   - Backtracking ensures we explore ALL possible paths, not just the first one,
 *     so we can find every path tied for the lowest cost.
 */

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include "Graph.h"

using namespace std;

/**
 * Recursively find all least-cost paths from 'current' island to 'destination'.
 *
 * @param current     - the island we are currently on
 * @param destination - the target island (Island 6)
 * @param path        - the current path being explored (island names)
 * @param cost        - the total toll accumulated so far
 * @param bestPaths   - all paths tied for the lowest cost (updated as we find better/equal paths)
 * @param bestCost    - the lowest cost found so far (updated when a cheaper path is found)
 */
void findPaths(const Island *current, const Island *destination,
               vector<string> &path, int cost,
               vector<vector<string>> &bestPaths, int &bestCost)
{
    // Base case 1: Reached the destination (Island 6)
    if (current == destination) {
        if (cost < bestCost) {
            // Found a cheaper path — clear previous best and save this one
            bestCost = cost;
            bestPaths.clear();
            bestPaths.push_back(path);
        } else if (cost == bestCost) {
            // Found a path tied for the best — add it
            bestPaths.push_back(path);
        }
        return;
    }

    // Base case 2: No outgoing bridges (dead end) — implicitly handled
    // because the loop below simply won't execute, and the function returns.

    // Recursive case: Try each outgoing bridge from the current island
    vector<const Bridge *> bridges = current->get_bridges();
    for (const Bridge *bridge : bridges) {
        const Island *next = bridge->get_endpoint();
        int toll = bridge->get_toll();

        // Cross the bridge: add the next island to path and add toll to cost
        path.push_back(next->get_name());

        // Recurse: explore paths from the next island
        findPaths(next, destination, path, cost + toll, bestPaths, bestCost);

        // Backtrack: remove the last island from the path so we can
        // try the next bridge from the current island
        path.pop_back();
    }
}

int main()
{
    Graph graph;
    const Island *start = graph.get_start();
    const Island *destination = graph.get_destination();

    // Initialize the path with the starting island
    vector<string> path;
    path.push_back(start->get_name());

    // Track best paths and best cost
    vector<vector<string>> bestPaths;
    int bestCost = INT_MAX;

    // Find all least-cost paths
    findPaths(start, destination, path, 0, bestPaths, bestCost);

    // Print results
    cout << "Least cost: " << bestCost << endl;
    cout << "Number of paths with least cost: " << bestPaths.size() << endl;
    cout << endl;

    for (const vector<string> &p : bestPaths) {
        for (int i = 0; i < p.size(); i++) {
            cout << p[i];
            if (i < p.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}
