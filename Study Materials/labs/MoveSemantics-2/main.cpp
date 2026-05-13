#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
    cout << "1. shar_ptr1 and shar_ptr2 ..." << endl;
    shared_ptr<Date> shar_ptr1(new Date(2001, 1, 1));
    shared_ptr<Date> shar_ptr2(shar_ptr1);

    cout << "*shar_ptr1 = " << *shar_ptr1 << endl;
    cout << "*shar_ptr2 = " << *shar_ptr2 << endl;

    {
        cout << endl << "ENTERING NEW SCOPE!" << endl;

        shared_ptr<Date> shar_ptr3(shar_ptr2);
        shared_ptr<Date> shar_ptr4(new Date(2004, 4, 4));

        cout << "*shar_ptr1 = " << *shar_ptr1 << endl;
        cout << "*shar_ptr2 = " << *shar_ptr2 << endl;
        cout << "*shar_ptr3 = " << *shar_ptr3 << endl;
        cout << "*shar_ptr4 = " << *shar_ptr4 << endl;

        // Automatically delete objects created in this scope.
        cout << "EXITING SCOPE!" << endl << endl;
    }

    cout << "*shar_ptr1 = " << *shar_ptr1 << endl;
    cout << "*shar_ptr2 = " << *shar_ptr2 << endl;

    cout << endl << "2. shar_ptr1.reset ..." << endl;
    shar_ptr1.reset(new Date(2011, 11, 11));
    cout << "*shar_ptr1 = " << *shar_ptr1 << endl;
    cout << "*shar_ptr2 = " << *shar_ptr2 << endl;

    cout << endl << "3. shar_ptr2.reset ..." << endl;
    shar_ptr2.reset(new Date(2022, 12, 22));
    cout << "*shar_ptr2 = " << *shar_ptr2 << endl;

    cout << endl << "4. Program termination ..." << endl;
    return 0;
}
