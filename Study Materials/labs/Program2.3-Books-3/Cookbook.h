#ifndef COOKBOOK_H_
#define COOKBOOK_H_

#include "Book.h"
#include "CookbookAttrs.h"

using namespace std;

class Cookbook : public Book
{
public:
    Cookbook(CookbookAttrs * const attrs) : Book(attrs) {}
};

#endif /* COOKBOOK_H_ */
