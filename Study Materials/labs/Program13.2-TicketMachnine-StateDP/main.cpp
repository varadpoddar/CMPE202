#include <iostream>
#include "Enums.h"
#include "State.h"
#include "TicketMachine.h"

using namespace std;

int main()
{
    TicketMachine machine(3);
    machine.run();

    return 0;
}
