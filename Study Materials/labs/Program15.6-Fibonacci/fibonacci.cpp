#include <iostream>
#include <iomanip>

long f(const int n);

using namespace std;

int main()
{
    cout << "  n        f[n]" << endl;
    cout << "---------------" << endl;

    for (int n = 0; n < 50; n++)
    {
        cout << setw(3) << n << setw(12) << f(n) << endl;
    }

    return 0;
}

long f(const int n)
{
    if      (n == 0) return 0;
    else if (n == 1) return 1;
    else             return f(n-2) + f(n-1);
}
