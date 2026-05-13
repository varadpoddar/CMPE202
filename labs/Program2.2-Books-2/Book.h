#ifndef BOOK_H_
#define BOOK_H_

#include "Attributes.h"

using namespace std;

class Book
{
public:
    Book(Attributes * const attrs) : attributes(attrs) {}
    virtual ~Book() { delete attributes; }

    Attributes *get_attributes() const { return attributes; }

private:
    Attributes *attributes;
};

#endif /* BOOK_H_ */
