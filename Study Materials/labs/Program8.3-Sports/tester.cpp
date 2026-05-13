#include <iostream>
#include "Sport.h"
#include "Sports.h"

using namespace std;

void generate_report(const Sport& sport);

int main()
{
    generate_report(Baseball());
    generate_report(Football());
    generate_report(Volleyball());

    return 0;
}

void generate_report(const Sport& sport)
{
    cout << sport.get_type() << endl;
    cout << "  players: " << sport.recruit_players()  << endl;
    cout << "    venue: " << sport.reserve_venue() << endl;

    cout << endl;
}
