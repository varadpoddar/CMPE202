#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int SIZE = 5;

void reverse(vector<int>& v);

int main()
{
    vector<int> data;

    for (int i = 1; i <= SIZE; i++) data.push_back(10*i);

    cout << "Reverse of";
    for (int d : data) cout << setw(3) << d;
    cout << endl;

    reverse(data);

    cout << "        is";
    for (int d : data) cout << setw(3) << d;
    cout << endl;

    return 0;
}

void reverse(vector<int>& v)
{
    // Base case.
    if (v.size() == 1) return;

    // Remove and save first value.
    int first_value = v[0];
    v.erase(v.begin());

    // Recursive call on the shorter vector:
    // Reverse the rest of the vector.
    reverse(v);

    // Append the saved value to the end
    // of the reversed vector.
    v.push_back(first_value);
}
