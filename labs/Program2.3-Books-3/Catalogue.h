#ifndef CATALOGUE_H_
#define CATALOGUE_H_

#include <vector>
#include "Book.h"
#include "FictionAttrs.h"
#include "CookbookAttrs.h"
#include "Catalogue.h"

using namespace std;

class Catalogue
{
public:
    Catalogue() {}

    ~Catalogue()
    {
        for (Book *book : booklist) delete book;
    }

    void add(FictionAttrs * const attrs)
    {
        booklist.push_back(new Fiction(attrs));
    }

    void add(CookbookAttrs * const attrs)
    {
        booklist.push_back(new Cookbook(attrs));
    }

    vector<Fiction  *> find(const FictionAttrs&  target_attrs) const;
    vector<Cookbook *> find(const CookbookAttrs& target_attrs) const;

private:
    vector<Book *> booklist;
};

#endif /* CATALOGUE_H_ */
