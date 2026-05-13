#ifndef SPORT_H_
#define SPORT_H_

#include <iostream>
#include <string>

using namespace std;

enum class Type { BASEBALL, FOOTBALL, VOLLEYBALL };

inline ostream& operator <<(ostream& ostr, const Type& type)
{
    switch (type)
    {
        case Type::BASEBALL   : ostr << "baseball";   break;
        case Type::FOOTBALL   : ostr << "football";   break;
        case Type::VOLLEYBALL : ostr << "volleyball"; break;
    }

    return ostr;
}

class Sport
{
public:
    Sport(const Type t) : type(t) {}
    virtual ~Sport() {}

    Type get_type() const { return type; }

    virtual string recruit_players() const = 0;
    virtual string reserve_venue()   const = 0;

private:
    Type type;
};

#endif /* SPORT_H_ */
