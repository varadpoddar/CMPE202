#ifndef ISLAND_H_
#define ISLAND_H_

#include <vector>
#include <string>
#include "Bridge.h"

using namespace std;

class Island
{
public:
    Island(const string n) : name(n) {}

    string get_name() const { return name; }

    vector<const Bridge *> get_bridges() const { return bridges; }
    void set_bridges(vector<const Bridge *> brs) { bridges = brs; }

private:
    const string name;
    vector<const Bridge *> bridges;  // outgoing bridges
};

#endif /* ISLAND_H_ */
