#include "Mammals.h"

using namespace std;

int main()
{
    Human ron(77.11, 1.85, true);
    cout << "Human Ron" << endl;
    cout << "weight: " << ron.get_weight() << " kg" << endl;
    cout << "height: " << ron.get_height() << " m" << endl;
    ron.eat();
    ron.perform();

    cout << endl;

    Cat buddy(5.55, 0.30, 1.25);
    cout << "Cat Buddy" << endl;
    cout << "weight: " << buddy.get_weight() << " kg" << endl;
    cout << "height: " << buddy.get_height() << " m" << endl;
    buddy.eat();
    buddy.perform();

    return 0;
}
