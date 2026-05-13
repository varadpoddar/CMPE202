#include <iostream>
#include "Sport.h"
#include "Sports.h"
#include "AthleticsDept.h"
#include "ProvisionsFactory.h"

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
    VarsityFactory varsity_factory;

    switch (type)
    {
        case Type::BASEBALL:
            return new VarsityBaseball(varsity_factory);
        case Type::FOOTBALL:
            return new VarsityFootball(varsity_factory);
        case Type::VOLLEYBALL:
            return nullptr;

        default: return nullptr;
    }
}

Sport *IntramuralDept::create_sport(const Type& type)
{
    IntramuralFactory intramural_factory;

    switch (type)
    {
        case Type::BASEBALL:
            return new IntramuralBaseball(intramural_factory);
        case Type::FOOTBALL:
            return new IntramuralFootball(intramural_factory);
        case Type::VOLLEYBALL:
            return new IntramuralVolleyball(intramural_factory);

        default: return nullptr;
    }
}
