#include "Book.h"
#include "Catalogue.h"
#include "Kind.h"

void Catalogue::add(Attributes * const attrs)
{
    booklist.push_back(new Book(attrs));
}

vector<Book *>Catalogue::find(const Attributes& target_attrs)
    const
{
    vector<Book *> matches;

    for (Book *book : booklist)
    {
        Attributes *book_attributes = book->get_attributes();
        if (book_attributes->is_match(target_attrs))
        {
            matches.push_back(book);
        }
    }

    return matches;
}
