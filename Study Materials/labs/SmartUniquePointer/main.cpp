#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
    cout << "1. raw_ptr ..." << endl;
    Date *raw_ptr = new Date();
    cout << "*raw_ptr = " << *raw_ptr << endl;

    {
        cout << endl << "ENTERING NEW SCOPE!" << endl;

        cout << endl << "2. uniq_ptr1 and uniq_ptr2 ..." << endl;
        unique_ptr<Date> uniq_ptr1(new Date(2001, 1, 1));
        unique_ptr<Date> uniq_ptr2(nullptr);
        cout << "*uniq_ptr1 = " << *uniq_ptr1 << endl;

        cout << endl << "3. uniq_ptr2 = std::move(uniq_ptr1) ..." << endl;
        uniq_ptr2 = std::move(uniq_ptr1);
        if (uniq_ptr1 == nullptr) cout << "uniq_ptr1 is null" << endl;
        else                      cout << "*uniq_ptr1 = " << *uniq_ptr1 << endl;
        cout << "*uniq_ptr2 = " << *uniq_ptr2 << endl;

        // Automatically delete objects created in this scope.
        cout << endl << "EXITING SCOPE!" << endl;
    }

    function<void (Date *dptr)> delete_date = [] (Date *ptr)
    {
        cout << "Custom deleter " << *ptr << endl;
        delete ptr;
    };

    cout << endl << "4. uniq_ptr3 ..." << endl;
    unique_ptr<Date, decltype(delete_date)>
        uniq_ptr3(new Date(2003, 3, 3), delete_date);
    cout << "*uniq_ptr3 = " << *uniq_ptr3 << endl;

    cout << endl << "5. uniq_ptr4 ..." << endl;
    unique_ptr<Date> uniq_ptr4(nullptr);
    uniq_ptr4.reset(new Date(2004, 4, 4));
    cout << "*uniq_ptr4 = " << *uniq_ptr4 << endl;

    cout << endl << "6. uniq_ptr4.reset ..." << endl;
    uniq_ptr4.reset(new Date(2024, 4, 24));
    cout << "*uniq_ptr4 = " << *uniq_ptr4 << endl;

    cout << endl << "7. Program termination ..." << endl;
    return 0;
}
