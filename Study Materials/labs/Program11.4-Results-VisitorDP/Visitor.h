#ifndef VISITOR_H_
#define VISITOR_H_

#include "Enums.h"

using namespace std;

class Intramural;
class Sport;
class Game;
class Hall;

class Visitor
{
public:
    virtual ~Visitor() {}

    virtual void visit_Intramural(Intramural *node) = 0;
    virtual void visit_Sport(Sport *node) = 0;
    virtual void visit_Game(Game *node) = 0;
    virtual void visit_Hall(Hall *node) = 0;
};

class ScoresReportVisitor : public Visitor
{
public:
    void visit_Intramural(Intramural *intramural) override;
    void visit_Sport(Sport *sport) override;
    void visit_Game(Game *game) override;
    void visit_Hall(Hall *hall) override;
};

class ActivitiesReportVisitor : public Visitor
{
public:
    void visit_Intramural(Intramural *intramural) override;
    void visit_Sport(Sport *sport) override;
    void visit_Game(Game *game) override;
    void visit_Hall(Hall *hall) override;
};

class WinningsReportVisitor : public Visitor
{
public:
    void visit_Intramural(Intramural *intramural) override;
    void visit_Sport(Sport *sport) override;
    void visit_Game(Game *game) override;
    void visit_Hall(Hall *hall) override;
};

#endif /* VISITOR_H_ */
