#ifndef PROVISIONITEM_H_
#define PROVISIONITEM_H_

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class ProvisionItem
{
public:
    ProvisionItem(const string& id, const double c)
        : id(id), cost(c) {}

    string get_id()   const { return id; }
    double get_cost() const { return cost; }

private:
    string id;
    double cost;
};

inline ostream& operator<<(ostream &ostr, const ProvisionItem &pi)
{
    ostr << setw(6) << pi.get_id() << " cost: $"
         << setw(2) << pi.get_cost() << endl;
    return ostr;
}

#endif /* PROVISIONITEM_H_ */
