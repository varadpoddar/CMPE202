#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message
{
public:
    Message(const string& s) : str(s) {}
    string str;

    friend ostream& operator <<(ostream& outs, const Message& msg)
    {
        outs << msg.str;
        return outs;
    }

    friend Message add(const Message& msg1,
                       const Message& msg2)
    {
        Message concat = Message(msg1.str + " " + msg2.str);
        return concat;  // returns an rvalue
    }

    friend Message operator +(const Message& msg1,
                              const Message& msg2)
    {
        Message concat = Message(msg1.str + " " + msg2.str);
        return concat;  // returns an rvalue
    }
};

#endif //MESSAGE_H