#ifndef PROVISIONITEM_H_
#define PROVISIONITEM_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class ProvisionItem
{
public:
    virtual ~ProvisionItem() = default;

    string get_id() const { return id; }

    virtual double get_cost() const { return cost; }

    vector<ProvisionItem *> operator() () const
    {
        throw logic_error(
                    "ProvisionItem::get_provisions(): not implemented");
    }

    virtual void print() const { print_indented(0); }

    virtual void print_indented(const int indentation) const
    {
        for (int i = 0; i < indentation; i++) cout << "    ";

        cout << setw(6) << get_id() << " cost: $"
             << setw(2) << get_cost() << endl;
    }

    virtual void add(ProvisionItem *item)
    {
        throw logic_error("ProvisionItem::add(): not implemented");
    }

    virtual void remove(ProvisionItem *item)
    {
        throw logic_error("ProvisionItem::remove(): not implemented");
    }

protected:
    ProvisionItem(const string& id) : id(id), cost(0) {}

    ProvisionItem(const string& id, const double c)
        : id(id), cost(c) {}

private:
    string id;
    double cost;
};

#endif /* PROVISIONITEM_H_ */
