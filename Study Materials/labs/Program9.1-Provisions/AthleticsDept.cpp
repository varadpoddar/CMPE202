#include <iostream>
#include "Sport.h"
#include "Sports.h"
#include "AthleticsDept.h"

void AthleticsDept::generate_report(const Category& category,
                                    const Type& type)
{
    Sport *sport = nullptr;

    switch (category)
    {
        case Category::VARSITY:
            switch (type)
            {
                case Type::BASEBALL:
                {
                    sport = new VarsityBaseball();
                    break;
                }

                case Type::FOOTBALL:
                {
                    sport = new VarsityFootball();
                    break;
                }

                case Type::VOLLEYBALL:
                {
                    sport = nullptr;
                    break;
                }
            }

            break;

        case Category::INTRAMURAL:
            switch (type)
            {
                case Type::BASEBALL:
                {
                    sport = new IntramuralBaseball();
                    break;
                }

                case Type::FOOTBALL:
                {
                    sport = new IntramuralFootball();
                    break;
                }

                case Type::VOLLEYBALL:
                {
                    sport = new IntramuralVolleyball();
                    break;
                }
            }

            break;
    }

    cout << sport->get_category() << " "
         << sport->get_type() << endl;
    cout << "  players: " << sport->recruit_players() << endl;
    cout << "    venue: " << sport->reserve_venue()   << endl;
    cout << endl;
}
