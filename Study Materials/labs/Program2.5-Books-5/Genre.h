#ifndef GENRE_H_
#define GENRE_H_

#include <iostream>

using namespace std;

enum class Genre
{
    ADVENTURE, CLASSICS, DETECTIVE, FANTASY, HISTORIC,
    HORROR, ROMANCE, SCIFI
};

inline ostream& operator <<(ostream& ostr, const Genre& genre)
{
    switch (genre)
    {
        case Genre::ADVENTURE: ostr << "adventure"; break;
        case Genre::CLASSICS:  ostr << "classics";  break;
        case Genre::DETECTIVE: ostr << "detective"; break;
        case Genre::FANTASY:   ostr << "fantasy";   break;
        case Genre::HISTORIC:  ostr << "historic";  break;
        case Genre::HORROR:    ostr << "horror";    break;
        case Genre::ROMANCE:   ostr << "romance";   break;
        case Genre::SCIFI:     ostr << "scifi";     break;
    }

    return ostr;
}

#endif /* GENRE_H_ */
