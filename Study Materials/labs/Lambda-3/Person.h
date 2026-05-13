#ifndef PERSON_CPP_
#define PERSON_CPP_

#include <string>

using namespace std;

enum class Gender { M, F };

class Person
{
public:
    Person(string f, string l, Gender g)
        : first(f), last(l), gender(g) {}

    virtual ~Person() {}

    string first;
    string last;
    Gender gender;
};

inline ostream& operator <<(ostream& outs, const Person& p)
{
    outs << "  {" << "first=" << p.first << ", last=" << p.last
         << ", gender=" << (p.gender == Gender::F ? "F" : "M") << "}";
    return outs;
}

#endif /* PERSON_CPP_ */
