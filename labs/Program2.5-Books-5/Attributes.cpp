#include <iostream>
#include <string>
#include <set>
#include <variant>
#include <cassert>

#include "Key.h"
#include "Kind.h"
#include "Genre.h"
#include "Region.h"
#include "Subject.h"
#include "Attributes.h"

using namespace std;

// Common book attribute keys.
const KeySet Attributes::COMMON_SET = { Key::KIND,
                                        Key::TITLE,
                                        Key::FIRST,
                                        Key::LAST };

// Attribute keys specific to each kind of book.
const KeySet Attributes::FICTION_SET  = { Key::YEAR,
                                          Key::GENRE };
const KeySet Attributes::COOKBOOK_SET = { Key::REGION };
const KeySet Attributes::HOWTO_SET    = { Key::SUBJECT };

const KeySet Attributes::MAKE_FICTION_KEYS()
{
    KeySet keyset(COMMON_SET);
    keyset.insert(FICTION_SET.begin(), FICTION_SET.end());
    return keyset;
}

const KeySet Attributes::MAKE_COOKBOOK_KEYS()
{
    KeySet keyset(COMMON_SET);
    keyset.insert(COOKBOOK_SET.begin(), COOKBOOK_SET.end());
    return keyset;
}

const KeySet Attributes::MAKE_HOWTO_KEYS()
{
    KeySet keyset(COMMON_SET);
    keyset.insert(HOWTO_SET.begin(), HOWTO_SET.end());
    return keyset;
}

const KeySet Attributes::MAKE_ALL_KEYS()
{
    KeySet keyset(COMMON_SET);
    keyset.insert(FICTION_SET.begin(),  FICTION_SET.end());
    keyset.insert(COOKBOOK_SET.begin(), COOKBOOK_SET.end());
    keyset.insert(HOWTO_SET.begin(),    HOWTO_SET.end());
    return keyset;
}

// All the attribute keys for each kind of books.
const KeySet Attributes::FICTION_KEYS  = MAKE_FICTION_KEYS();
const KeySet Attributes::COOKBOOK_KEYS = MAKE_COOKBOOK_KEYS();
const KeySet Attributes::HOWTO_KEYS    = MAKE_HOWTO_KEYS();

// All the attribute keys for all kinds of books.
const KeySet Attributes::ALL_KEYS = MAKE_ALL_KEYS();

Attributes::Attributes(AttributeMap *pairs)
    : attribute_map(pairs)
{
    // Get the key-value attribute pair with Key::KIND.
    AttributeValue kind_value;
    AttributeMap::iterator kind_it = attribute_map->find(Key::KIND);

    set<Key> valid_keys;

    // Set the valid attribute keys based on the kind of book.
    if (kind_it != attribute_map->end())
    {
        // What kind of book is it?
        Kind kind = get<KIND_INDEX>(kind_it->second);

        // Which set of attribute keys is valid
        // for that kind of book?
        switch (kind)
        {
            case Kind::FICTION:
                valid_keys = FICTION_KEYS;
                break;

            case Kind::COOKBOOK:
                valid_keys= COOKBOOK_KEYS;
                break;

            case Kind::HOWTO:
                valid_keys = HOWTO_KEYS;
                break;
        }
    }
    else
    {
        // Kind of book not specified: Allow all attribute keys.
        valid_keys = ALL_KEYS;
    }

    // Iterate over all the attribute key-value pairs.
    for (AttributeMap::iterator it = pairs->begin();
         it != pairs->end(); it++)
    {
        Key key   = it->first;
        int index = it->second.index();

        // Is this attribute key valid for this kind of book?
        assert(valid_keys.find(key) != valid_keys.end());

        // Is the datatype of the attribute value
        // valid for this attribute key?
        switch (key)
        {
            case Key::YEAR:
                assert(index == INT_INDEX); break;

            case Key::TITLE:
            case Key::LAST:
            case Key::FIRST:
                assert(index == STRING_INDEX); break;

            case Key::KIND:
                assert(index == KIND_INDEX); break;

            case Key::GENRE:
                assert(index == GENRE_INDEX); break;

            case Key::REGION:
                assert(index == REGION_INDEX); break;

            case Key::SUBJECT:
                assert(index == SUBJECT_INDEX); break;
        }
    }
}

bool Attributes::is_match(const Attributes& target_attrs) const
{
    AttributeMap *target_pairs = target_attrs.attribute_map;
    AttributeMap::iterator it;

    for (it = target_pairs->begin(); it != target_pairs->end(); it++)
    {
        Key            target_key   = it->first;
        AttributeValue target_value = it->second;

        if (!is_matching_pair(target_key, target_value))
        {
            return false;
        }
    }

    return true;
}

bool Attributes::is_matching_pair(
                            const Key& target_key,
                            const AttributeValue& target_value) const
{
    if (attribute_map->find(target_key) == attribute_map->end())
    {
        return false;
    }

    if ((*attribute_map)[target_key] == target_value)
    {
        return true;
    }

    if (target_value.index() == STRING_INDEX)
    {
        return equal_ignore_case(
                        get<string>((*attribute_map)[target_key]),
                        get<string>(target_value));
    }

    return false;
}

ostream& operator <<(ostream& ostr, const Attributes& attrs)
{
    AttributeMap *pairs = attrs.attribute_map;
    AttributeMap::iterator it;

    ostr << "{";

    for (it = pairs->begin(); it != pairs->end(); it++)
    {
        Key            key   = it->first;
        AttributeValue value = it->second;

        if (it != pairs->begin()) ostr << ", ";
        ostr << key << ": ";

        switch (key)
        {
            case Key::KIND:   ostr << get<Kind>(value); break;

            case Key::TITLE:
            case Key::LAST:
            case Key::FIRST:  ostr << "'" << get<string>(value)
                                   << "'"; break;

            case Key::GENRE:  ostr << get<Genre>(value);  break;
            case Key::YEAR:   ostr << get<int>(value);    break;

            case Key::REGION:  ostr << get<Region>(value);  break;
            case Key::SUBJECT: ostr << get<Subject>(value); break;

            default: break;
        }
    }

    ostr << "}";
    return ostr;
}
