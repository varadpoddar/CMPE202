#include <iostream>
#include "Sport.h"
#include "Sports.h"
#include "AthleticsDept.h"

void AthleticsDept::generate_report(const Type& type)
{
    sport = create_sport(type);

    cout << sport->get_category() << " "
         << sport->get_type() << endl;
    cout << "  players: " << sport->recruit_players() << endl;
    cout << "    venue: " << sport->reserve_venue()   << endl;
    cout << endl;
}

Sport *VarsityDept::create_sport(const Type& type)
{
    switch (type)
    {
        case Type::BASEBALL:   return new VarsityBaseball();
        case Type::FOOTBALL:   return new VarsityFootball();
        case Type::VOLLEYBALL: return nullptr;

        default: return nullptr;
    }
}

Sport *IntramuralDept::create_sport(const Type& type)
{
    switch (type)
    {
        case Type::BASEBALL:   return new IntramuralBaseball();
        case Type::FOOTBALL:   return new IntramuralFootball();
        case Type::VOLLEYBALL: return new IntramuralVolleyball();

        default: return nullptr;
    }
}
