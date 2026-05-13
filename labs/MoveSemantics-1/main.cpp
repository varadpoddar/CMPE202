#include <iostream>
#include <vector>
#include "Message.h"

using namespace std;

int main()
{
    vector<Message> v;

    Message msg1("Hello");
    Message msg2("World");
    Message msg3("SJSU");
    Message msg4("Spartans");

    cout << "msg1 = \"" << msg1 << "\"" << endl;
    cout << "msg2 = \"" << msg2 << "\"" << endl;
    msg2 = msg1;
    cout << "1. After assigning the lvalue msg1 to msg2:" << endl;
    cout << "msg1 = \"" << msg1 << "\"" << endl;
    cout << "msg2 = \"" << msg2 << "\"" << endl;

    cout << endl;

    cout << "msg3 = \"" << msg3 << "\"" << endl;
    v.push_back(msg3);
    cout << "2. After passing the lvalue msg3 by value:" << endl;
    cout << "msg3 = \"" << msg3 << "\"" << endl;

    cout << endl;

    cout << "msg4 = \"" << msg4 << "\"" << endl;
    Message msg5(msg4);
    cout << "3. After calling the msg5 copy constructor "
         << "with lvalue msg4:" << endl;
    cout << "msg4 = \"" << msg4 << "\"" << endl;
    cout << "msg5 = \"" << msg5 << "\"" << endl;

    cout << endl;

    cout << "msg1 = \"" << msg1 << "\"" << endl;
    cout << "msg3 = \"" << msg3 << "\"" << endl;
    msg3 = std::move(msg1);
    cout << "4. After assigning the rvalue std::move(msg1) to msg3:"
         << endl;
    cout << "msg1 = \"" << msg1 << "\"" << endl;
    cout << "msg3 = \"" << msg3 << "\"" << endl;

    cout << endl;

    cout << "msg3 = \"" << msg3 << "\"" << endl;
    cout << "5. After passing the rvalue std::move(msg3):" << endl;
    v.push_back(std::move(msg3));
    cout << "msg3 = \"" << msg3 << "\"" << endl;

    cout << endl;

    cout << "msg4 = \"" << msg4 << "\"" << endl;
    Message msg6(std::move(msg4));
    cout << "6. After calling the msg6 move constructor "
         << "with rvalue std::move(msg4):" << endl;
    cout << "msg4 = \"" << msg4 << "\"" << endl;
    cout << "msg6 = \"" << msg6 << "\"" << endl;

    cout << endl;

    Message msg7("");
    cout << "msg2 = \"" << msg2 << "\"" << endl;
    cout << "msg6 = \"" << msg6 << "\"" << endl;
    cout << "msg7 = \"" << msg7 << "\"" << endl;
    msg7 = add(msg2, msg6);
    cout << "7. After returning the rvalue add(msg2, msg6):" << endl;
    cout << "msg2 = \"" << msg2 << "\"" << endl;
    cout << "msg6 = \"" << msg6 << "\"" << endl;
    cout << "msg7 = \"" << msg7 << "\"" << endl;

    cout << endl;

    Message msg8("");
    cout << "msg2 = \"" << msg2 << "\"" << endl;
    cout << "msg6 = \"" << msg6 << "\"" << endl;
    cout << "msg8 = \"" << msg8 << "\"" << endl;
    msg8 = msg2 + msg6;
    cout << "8. After assigning the rvalue msg2 + msg6 to msg8:" << endl;
    cout << "msg2 = \"" << msg2 << "\"" << endl;
    cout << "msg6 = \"" << msg6 << "\"" << endl;
    cout << "msg8 = \"" << msg8 << "\"" << endl;

    cout << endl;
    return 0;
}