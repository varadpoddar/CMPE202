#ifndef INTRAMURAL_H_
#define INTRAMURAL_H_

#include <vector>
#include "Node.h"
#include "Sport.h"
#include "Visitor.h"

class Intramural : public Node
{
public:
    ~Intramural()
    {
        for (Sport *sport : sports) delete sport;
        for (Hall  *hall  : halls)  delete hall;
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit_Intramural(this);

        for (Sport *sport : sports) sport->accept(visitor);
        for (Hall  *hall  : halls)   hall->accept(visitor);
    }

    void add_sport(Sport *sport) { sports.push_back(sport); }
    void add_hall(Hall *hall)    { halls.push_back(hall); }

private:
    vector<Sport *> sports;
    vector< Hall *> halls;
};

#endif /* INTRAMURAL_H_ */
