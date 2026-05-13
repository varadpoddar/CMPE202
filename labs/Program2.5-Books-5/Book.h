#ifndef BOOK_H_
#define BOOK_H_

#include <iostream>
#include <string>

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

inline ostream& operator <<(ostream& ostr, const Book& book)
{
    cout << *book.get_attributes();
    return ostr;
}

#endif /* BOOK_H_ */
