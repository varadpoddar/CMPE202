#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int N = 4;

int counter = 0;

void solve(const int  n,
           const char source,
           const char temporary,
           const char destination);

int main()
{
    solve(N, 'L', 'M', 'R');

    return 0;
}

void solve(const int  n,
           const char source,
           const char temporary,
           const char destination)
{
    if (n == 1)
    {
        // Base case: Move a single disk.
        cout << setw(3) << ++counter
             << ": Move " << source << " ==> " << destination << endl;
    }
    else
    {
        // Solve for 1 fewer disk: n - 1
        solve(n - 1, source,    destination, temporary);
        solve(1,     source,    temporary,   destination);
        solve(n - 1, temporary, source,      destination);
    }
}
