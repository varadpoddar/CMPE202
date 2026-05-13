#ifndef VENUESTRATEGY_H_
#define VENUESTRATEGY_H_

#include <string>

using namespace std;

class VenueStrategy
{
public:
    virtual ~VenueStrategy() {}

    virtual string strategy() const = 0;
};

class Stadium : public VenueStrategy
{
public:
    string strategy() const override
    {
        return "sports stadium";
    }
};

class OpenField : public VenueStrategy
{
public:
    string strategy() const override
    {
        return "open field";
    }
};

#endif /* VENUESTRATEGY_H_ */
