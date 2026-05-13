#ifndef BOOK_H_
#define BOOK_H_

#include <iostream>
#include <string>

using namespace std;

class Book
{
public:
    Book(const string ttl, const string lst, const string fst)
        : title(ttl), last(lst), first(fst) {}

    string get_title() const { return title; }
    string get_last()  const { return last; }
    string get_first() const { return first; }

private:
    string title;
    string last;
    string first;
};

inline ostream& operator <<(ostream& ostr, const Book& book)
{
    ostr << "{TITLE: '"   << book.get_title()
         << "', LAST: '"  << book.get_last()
         << "', FIRST: '" << book.get_first() << "'}";

    return ostr;
}

#endif /* BOOK_H_ */
