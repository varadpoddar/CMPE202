#include <iostream>
#include "ExecutivePass.h"

using namespace std;

// Singleton?
ExecutivePass pass;

int main()
{
    pass.obtain("Ron");
    cout << "obtain: "; pass.print();

    ExecutivePass copy1;        // create with variable declaration
    copy1 = pass;               // copy assignment operator
    cout << "copy 1: "; copy1.print();

    ExecutivePass copy2(pass);  // copy constructor
    copy2.obtain("Sal");
    cout << "copy 2: "; copy2.print();

    return 0;
}
