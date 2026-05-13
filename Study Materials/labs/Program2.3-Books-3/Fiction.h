#ifndef FICTION_H_
#define FICTION_H_

#include "Book.h"
#include "FictionAttrs.h"

using namespace std;

class Fiction : public Book
{
public:
    Fiction(FictionAttrs * const attrs) : Book(attrs) {}
};

#endif /* FICTION_H_ */
