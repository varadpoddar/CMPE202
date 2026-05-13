#ifndef PROVISIONGROUP_H_
#define PROVISIONGROUP_H_

#include <vector>
#include <algorithm>
#include "ProvisionItem.h"

using namespace std;

class ProvisionGroup
{
public:
    ProvisionGroup(const string& id) : id(id) {}

    ~ProvisionGroup()
    {
        for (ProvisionItem *item : provisions) { delete item; };
    }

    string get_id() const { return id; }

    vector<ProvisionItem *> operator() () const
    {
        return provisions;
    }

    void add(ProvisionItem *item) { provisions.push_back(item); }

    void remove(const ProvisionItem *item)
    {
        auto pos = find(provisions.begin(), provisions.end(), item);
        if (pos != provisions.end()) provisions.erase(pos);
    }

private:
    string id;
    vector<ProvisionItem *> provisions;
};

#endif /* PROVISIONGROUP_H_ */
