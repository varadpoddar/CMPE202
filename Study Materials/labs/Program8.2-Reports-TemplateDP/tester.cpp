#include <iostream>
#include "VolleyballReport.h"
#include "BaseballReport.h"

using namespace std;

int main(int argc, char *args[])
{
    if (argc < 2)
    {
        cout << "Usage: report -b | -v" << endl;
        return -1;
    }

    if (string(args[1]) == "-b")
    {
        BaseballReport baseball;
        baseball.generate_report();
    }

    if (string(args[1]) == "-v")
    {
        VolleyballReport volleyball;
        volleyball.generate_report();
    }

    return 0;
}
