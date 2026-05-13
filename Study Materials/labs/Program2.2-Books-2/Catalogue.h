#ifndef CATALOGUE_H_
#define CATALOGUE_H_

#include <vector>
#include "Book.h"

using namespace std;

class Catalogue
{
public:
    void add(Attributes * const attrs)
    {
        booklist.push_back(new Book(attrs));
    }

    vector<Book *> find(const Attributes& target_attrs) const;

private:
    vector<Book *> booklist;
};

#endif /* CATALOGUE_H_ */
