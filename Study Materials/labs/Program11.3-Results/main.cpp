#include "Enums.h"
#include "Intramural.h"
#include "Sport.h"
#include "Game.h"
#include "Hall.h"

using namespace std;

Intramural *build_tree();

int main()
{
    Intramural *intramural = build_tree();

    intramural->print_scores_report();
    intramural->print_activities_report();
    intramural->print_winnings_report();

    delete intramural;
    return 0;
}

Intramural *build_tree()
{
    Intramural *intramural = new Intramural();

    Sport *baseball   = new Sport(SportType::BASEBALL);
    Sport *football   = new Sport(SportType::FOOTBALL);
    Sport *volleyball = new Sport(SportType::VOLLEYBALL);

    intramural->add_sport(baseball);
    intramural->add_sport(football);
    intramural->add_sport(volleyball);

    Hall *north = new Hall(HallName::NORTH);
    Hall *south = new Hall(HallName::SOUTH);
    Hall *east  = new Hall(HallName::EAST);
    Hall *west  = new Hall(HallName::WEST);

    intramural->add_hall(north);
    intramural->add_hall(south);
    intramural->add_hall( east);
    intramural->add_hall( west);

    baseball->add_game(new Game(west, 5, east,  3));
    baseball->add_game(new Game(east, 3, south, 0));

    football->add_game(new Game(north, 27, west, 21));

    volleyball->add_game(new Game(west,  15, south, 10));
    volleyball->add_game(new Game(north, 15, south, 13));
    volleyball->add_game(new Game(south, 15, west,  14));

    return intramural;
}
