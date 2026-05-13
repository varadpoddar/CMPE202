#ifndef FICTIONATTRS_H_
#define FICTIONATTRS_H_

#include <iostream>
#include <string>
#include "Attributes.h"

using namespace std;

enum class Genre
{
    ADVENTURE, CLASSICS, DETECTIVE, FANTASY, HISTORIC,
    HORROR, ROMANCE, SCIFI, UNSPECIFIED
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

        default: ostr << "unspecified"; break;
    }

    return ostr;
}

class FictionAttrs : public Attributes
{
public:
    FictionAttrs(const string title,
                 const string last, const string first,
                 const int yr, const Genre gen)
        : Attributes(title, last, first),
          year(yr), genre(gen) {}

    int   get_year()  const { return year; }
    Genre get_genre() const { return genre; }

    bool is_match(const FictionAttrs& target_attrs) const
    {
        if (!Attributes::is_match(target_attrs)) return false;

        return (   (target_attrs.get_year()  == 0)
                || (target_attrs.get_year()  == year))
            && (   (target_attrs.get_genre() == Genre::UNSPECIFIED)
                || (target_attrs.get_genre() == genre));
    }

private:
    int   year;
    Genre genre;
};

inline ostream& operator <<(ostream& ostr, const FictionAttrs& attrs)
{
    ostr << "{TITLE: '"   << attrs.get_title()
         << "', LAST: '"  << attrs.get_last()
         << "', FIRST: '" << attrs.get_first()
         << "', YEAR: "   << attrs.get_year()
         << ", GENRE: "   << attrs.get_genre() << "}";

    return ostr;
}

#endif /* FICTIONATTRS_H_ */
