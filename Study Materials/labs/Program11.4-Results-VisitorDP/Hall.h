#ifndef HALL_H_
#define HALL_H_

#include "Enums.h"
#include "Node.h"
#include "Visitor.h"

class Hall : public Node
{
public:
    Hall(const HallName name) : name(name), win_count(0) {}

    void accept(Visitor& visitor) override
    {
        visitor.visit_Hall(this);
    }

    HallName get_name() const { return name; }

    int get_win_count() const  { return win_count; }
    void increment_win_count() { win_count++; }

private:
    HallName name;
    int win_count;
};

#endif /* HALL_H_ */
