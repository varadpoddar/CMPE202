#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Quicksort.h"

using namespace std;

int main()
{
    const int SIZE = 1000;
    int data[SIZE];

    srand(time(0));
    for (int i = 0; i < SIZE; i++) data[i] = rand()%1000;

    Quicksort qsorter(data, SIZE);
    cout << "Before:" << qsorter << endl;
    qsorter.sort();
    cout << " After:" << qsorter << endl;

    cout << (qsorter.verify_sorted() ? "SORTED" : "ERROR") << endl;
    return 0;
}
