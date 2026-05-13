#ifndef PROVISIONGROUP_H_
#define PROVISIONGROUP_H_

#include <iostream>
#include <string>
#include <vector>
#include "ProvisionItem.h"

using namespace std;

class ProvisionGroup : public ProvisionItem
{
public:
    ProvisionGroup() : ProvisionItem("PROVISIONS") {}

    ~ProvisionGroup() override
    {
        for (ProvisionItem *item : provisions) { delete item; };
    }

    double get_cost() const override
    {
        double cost = 0;
        for (ProvisionItem *item : provisions)
        {
            cost += item->get_cost();
        }

        return cost;
    }

    virtual void print() const override { print_indented(0); }

    void add(ProvisionItem *item) override
    {
        provisions.push_back(item);
    }

    void remove(ProvisionItem *item) override
    {
        auto pos = find(provisions.begin(), provisions.end(), item);
        if (pos != provisions.end()) provisions.erase(pos);
    }

protected:
    ProvisionGroup(const string& id) : ProvisionItem(id) {}

private:
    vector<ProvisionItem *> provisions;

    virtual void print_indented(const int indentation) const override
    {
        for (int i = 0; i < indentation; i++) cout << "    ";
        cout << get_id() << endl;

        for (ProvisionItem *item : provisions)
        {
            item->print_indented(indentation + 1);
        }

        for (int i = 0; i < indentation; i++) cout << "    ";
        cout << get_id() << " total: $" << get_cost() << endl;
    }
};

#endif /* PROVISIONGROUP_H_ */
