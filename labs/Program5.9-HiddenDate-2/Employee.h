#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Employee
{
public:
    Employee(long id, string name, Date *bdate)
        : employee_id(id), name(name),
          birthdate(new Date(*bdate)) {}

    long employee_id;
    string name;

    Date *get_birthdate() const { return new Date(*birthdate); }

    friend ostream& operator <<(ostream& os, const Employee& emp);

private:
    Date *birthdate;
};

inline ostream& operator <<(ostream& os, const Employee& emp)
{
    os << "Employee #" <<emp.employee_id << endl;
    os << "  Name: " << emp.name << endl;
    os << "  Birthdate: "; emp.birthdate->print(); os << endl;

    return os;
}

#endif /* EMPLOYEE_H_ */
