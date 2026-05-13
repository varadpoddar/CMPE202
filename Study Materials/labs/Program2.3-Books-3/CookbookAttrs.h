#ifndef COOKBOOKATTRS_H_
#define COOKBOOKATTRS_H_

#include <iostream>
#include <string>
#include "Attributes.h"

using namespace std;

enum class Region
{
    CHINA, FRANCE, INDIA, ITALY, MEXICO, PERSIA, US, UNSPECIFIED
};

inline ostream& operator <<(ostream& ostr, const Region& region)
{
    switch (region)
    {
        case Region::CHINA:  ostr << "China";  break;
        case Region::FRANCE: ostr << "France"; break;
        case Region::INDIA:  ostr << "India";  break;
        case Region::ITALY:  ostr << "Italy";  break;
        case Region::MEXICO: ostr << "Mexico"; break;
        case Region::PERSIA: ostr << "Persia"; break;
        case Region::US:     ostr << "US";     break;

        default: ostr << "unspecified"; break;
    }

    return ostr;
}

class CookbookAttrs : public Attributes
{
public:
    CookbookAttrs(const string title,
                  const string last, const string first,
                  const Region reg)
        : Attributes(title, last, first),
          region(reg) {}

    Region get_region() const { return region; }

    bool is_match(const CookbookAttrs& target_attrs) const
    {
        if (!Attributes::is_match(target_attrs)) return false;

        return (target_attrs.get_region() == Region::UNSPECIFIED)
            || (target_attrs.get_region() == region);
    }

private:
    Region region;
};

inline ostream& operator <<(ostream& ostr, const CookbookAttrs& attrs)
{
    ostr << "{TITLE: '"   << attrs.get_title()
         << "', LAST: '"  << attrs.get_last()
         << "', FIRST: '" << attrs.get_first()
         << "', REGION: "  << attrs.get_region() << "}";

    return ostr;
}

#endif /* COOKBOOKATTRS_H_ */
