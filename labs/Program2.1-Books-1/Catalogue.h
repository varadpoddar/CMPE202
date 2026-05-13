#ifndef CATALOGUE_H_
#define CATALOGUE_H_

#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class Catalogue
{
public:
    void add(const string title,
             const string last,
             const string first)
    {
        booklist.push_back(new Book(title, last, first));
    }

    vector<Book *> find(const Book& target) const;

private:
    vector<Book *> booklist;

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

#endif /* CATALOGUE_H_ */
