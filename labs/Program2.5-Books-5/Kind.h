#ifndef KIND_H_
#define KIND_H_

#include <iostream>

using namespace std;

enum class Kind
{
    FICTION, COOKBOOK, HOWTO
};

inline ostream& operator <<(ostream& ostr, const Kind& kind)
{
    switch (kind)
    {
        case Kind::FICTION:  ostr << "fiction";  break;
        case Kind::COOKBOOK: ostr << "cookbook"; break;
        case Kind::HOWTO:    ostr << "howto";    break;
    }

    return ostr;
}

#endif /* KIND_H_ */
