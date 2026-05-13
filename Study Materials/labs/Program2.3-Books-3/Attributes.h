#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <string>

using namespace std;

class Attributes
{
public:
    Attributes(const string ttl,
               const string lst, const string fst)
        : title(ttl), last(lst), first(fst) {}

    virtual ~Attributes() {}

    string get_title() const { return title; }
    string get_last()  const { return last; }
    string get_first() const { return first; }

protected:
    bool is_match(const Attributes& target_attrs) const
    {
        return equal_ignore_case(target_attrs.get_title(),  title)
            && equal_ignore_case(target_attrs.get_last(),   last)
            && equal_ignore_case(target_attrs.get_first(), first);
    }

private:
    string title;
    string last;
    string first;

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

#endif /* ATTRIBUTES_H_ */
