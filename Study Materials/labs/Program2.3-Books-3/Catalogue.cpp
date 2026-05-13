#include <vector>

#include "Book.h"
#include "Fiction.h"
#include "FictionAttrs.h"
#include "Cookbook.h"
#include "CookbookAttrs.h"
#include "Catalogue.h"

vector<Fiction *>Catalogue::find(const FictionAttrs& target_attrs)
    const
{
    vector<Fiction *> matches;

    for (Book *book : booklist)
    {
        Fiction *fiction = dynamic_cast<Fiction *>(book);

        if (fiction != nullptr)
        {
            FictionAttrs *fiction_attrs =
                    dynamic_cast<FictionAttrs *>(book->get_attributes());
            if (fiction_attrs->is_match(target_attrs))
            {
                matches.push_back(fiction);
            }
        }
    }

    return matches;
}

vector<Cookbook *>Catalogue::find(const CookbookAttrs& target_attrs)
    const
{
    vector<Cookbook *> matches;

    for (Book *book : booklist)
    {
        Cookbook *cookbook = dynamic_cast<Cookbook *>(book);

        if (cookbook != nullptr)
        {
            CookbookAttrs *cookbook_attrs =
                    dynamic_cast<CookbookAttrs *>(book->get_attributes());
            if (cookbook_attrs->is_match(target_attrs))
            {
                matches.push_back(cookbook);
            }
        }
    }

    return matches;
}
