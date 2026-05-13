#include <iostream>
#include "Toy.h"
#include "ToyFactory.h"

using namespace std;

int main()
{
    Kind kind = Kind::AIRPLANE;

    Toy *toy = ToyFactory::make(kind);
    toy->print();

    delete toy;
    return 0;
}
