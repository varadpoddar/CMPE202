#include "Intramural.h"
#include "Sport.h"
#include "Game.h"
#include "Hall.h"
#include "Visitor.h"

using namespace std;

Intramural *build_tree();

int main()
{
    Intramural *intramural_node = build_tree();

    ScoresReportVisitor     scores_report_visitor;
    ActivitiesReportVisitor activities_report_visitor;
    WinningsReportVisitor   winnings_report_visitor;

    intramural_node->accept(scores_report_visitor);
    intramural_node->accept(activities_report_visitor);
    intramural_node->accept(winnings_report_visitor);

    delete intramural_node;
    return 0;
}

Intramural *build_tree()
{
    Intramural *intramural_node = new Intramural();

    Sport *baseball   = new Sport(SportType::BASEBALL);
    Sport *football   = new Sport(SportType::FOOTBALL);
    Sport *volleyball = new Sport(SportType::VOLLEYBALL);

    intramural_node->add_sport(baseball);
    intramural_node->add_sport(football);
    intramural_node->add_sport(volleyball);

    Hall *north = new Hall(HallName::NORTH);
    Hall *south = new Hall(HallName::SOUTH);
    Hall *east  = new Hall(HallName::EAST);
    Hall *west  = new Hall(HallName::WEST);

    intramural_node->add_hall(north);
    intramural_node->add_hall(south);
    intramural_node->add_hall(  east);
    intramural_node->add_hall( west);

    baseball->add_game(new Game(west, 5, east,  3));
    baseball->add_game(new Game(east, 3, south, 0));

    football->add_game(new Game(north, 27, west, 21));

    volleyball->add_game(new Game(west,  15, south, 10));
    volleyball->add_game(new Game(north, 15, south, 13));
    volleyball->add_game(new Game(south, 15, west,  14));

    return intramural_node;
}
