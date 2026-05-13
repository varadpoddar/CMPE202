#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <string>
#include <map>
#include <variant>

#include "Key.h"
#include "Kind.h"
#include "Genre.h"
#include "Region.h"
#include "Subject.h"

using namespace std;

typedef variant<int, string,
               Kind, Genre, Region, Subject> AttributeValue;

typedef map<Key, AttributeValue> AttributeMap;

enum type_indexes
{
    INT_INDEX, STRING_INDEX,
    KIND_INDEX, GENRE_INDEX, REGION_INDEX, SUBJECT_INDEX
};

class Attributes
{
public:
    Attributes(AttributeMap *const pairs);
    ~Attributes() { delete attribute_map; }

    bool is_match(const Attributes& target_attrs);

    friend ostream& operator <<(ostream& ostr,
                                const Attributes& attrs);

private:
    AttributeMap *attribute_map;

    bool is_matching_pair(const Key& target_key,
                          const AttributeValue& target_value);

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
