#ifndef ISLAND_H_
#define ISLAND_H_

#include <string>
#include <utility>
#include <vector>

class Bridge;

class Island
{
public:
    explicit Island(std::string n) : name(std::move(n)) {}

    const std::string &get_name() const { return name; }

    const std::vector<const Bridge *> &get_bridges() const { return bridges; }
    void set_bridges(const std::vector<const Bridge *> &brs) { bridges = brs; }

private:
    std::string name;
    std::vector<const Bridge *> bridges;  // outgoing bridges
};

#endif /* ISLAND_H_ */
