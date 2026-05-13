#ifndef NODE_H_
#define NODE_H_

#include "Visitor.h"

using namespace std;

class Node
{
public:
    virtual ~Node() {}

    virtual void accept(Visitor& visitor) = 0;
};

#endif /* NODE_H_ */
