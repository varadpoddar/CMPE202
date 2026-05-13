#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <iostream>

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

class Attributes
{
public:
    Attributes(const string ttl,
               const string lst, const string fst,
               const int yr, const Genre gen)
        : title(ttl), last(lst), first(fst),
          year(yr), genre(gen) {}

    string get_title() const { return title; }
    string get_last()  const { return last; }
    string get_first() const { return first; }
    int    get_year()  const { return year; }
    Genre  get_genre() const { return genre; }

    bool is_match(const Attributes& target_attrs) const
    {
        return equal_ignore_case(target_attrs.get_title(), title)
            && equal_ignore_case(target_attrs.get_last(),  last)
            && equal_ignore_case(target_attrs.get_first(), first)
            && (    (target_attrs.get_year()  == 0)
                ||  (target_attrs.get_year()  == year))
            && (    (target_attrs.get_genre() == Genre::UNSPECIFIED)
                ||  (target_attrs.get_genre() == genre));
    }

private:
    string title;
    string last;
    string first;
    int    year;
    Genre  genre;

    static bool equal_ignore_case(const string string1,
                                  const string string2)
    {
        for (int i = 0; i < string1.length(); i++)
        {
            if (tolower(string1[i]) != tolower(string2[i]))
            {
                return false;
            }
        }

        return true;
    }
};

inline ostream& operator <<(ostream& ostr, const Attributes& attrs)
{
    ostr << "{TITLE: '"   << attrs.get_title()
         << "', LAST: '"  << attrs.get_last()
         << "', FIRST: '" << attrs.get_first()
         << "', YEAR: "   << attrs.get_year()
         << ", GENRE: "   << attrs.get_genre() << "}";

    return ostr;
}

#endif /* ATTRIBUTES_H_ */
